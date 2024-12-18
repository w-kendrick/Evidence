// Copyright 2020 Dan Kestranek.


#include "GAT_WaitInteractableTarget.h"
#include "Evidence/Interfaces/Interactable.h"
#include "Evidence/Character/BaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Evidence/Evidence.h"

UGAT_WaitInteractableTarget::UGAT_WaitInteractableTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTraceAffectsAimPitch = true;
}

UGAT_WaitInteractableTarget* UGAT_WaitInteractableTarget::WaitForInteractableTarget(UGameplayAbility* OwningAbility, FName TaskInstanceName, FCollisionProfileName TraceProfile, float MaxRange, float TimerPeriod, bool bShowDebug)
{
	UGAT_WaitInteractableTarget* const MyObj = NewAbilityTask<UGAT_WaitInteractableTarget>(OwningAbility, TaskInstanceName);		//Register for task list here, providing a given FName as a key
	MyObj->TraceProfile = TraceProfile;
	MyObj->MaxRange = MaxRange;
	MyObj->TimerPeriod = TimerPeriod;
	MyObj->bShowDebug = bShowDebug;
	
	ABaseCharacter* const Char = Cast<ABaseCharacter>(OwningAbility->GetCurrentActorInfo()->AvatarActor);

	MyObj->StartLocation = FGameplayAbilityTargetingLocationInfo();
	MyObj->StartLocation.LocationType = EGameplayAbilityTargetingLocationType::ActorTransform;
	MyObj->StartLocation.SourceActor = Char;
	MyObj->StartLocation.SourceAbility = OwningAbility;

	return MyObj;
}

void UGAT_WaitInteractableTarget::Activate()
{
	UWorld* const World = GetWorld();
	World->GetTimerManager().SetTimer(TraceTimerHandle, this, &UGAT_WaitInteractableTarget::PerformTrace, TimerPeriod, true);
}

void UGAT_WaitInteractableTarget::OnDestroy(bool AbilityEnded)
{
	UWorld* const World = GetWorld();
	World->GetTimerManager().ClearTimer(TraceTimerHandle);

	Super::OnDestroy(AbilityEnded);
}

void UGAT_WaitInteractableTarget::LineTrace(FHitResult& OutHitResult, const UWorld* World, const FVector& Start, const FVector& End, FName ProfileName, const FCollisionQueryParams Params, bool bLookForInteractableActor) const
{
	check(World);

	TArray<FHitResult> HitResults;
	World->LineTraceMultiByProfile(HitResults, Start, End, ProfileName, Params);

	OutHitResult.TraceStart = Start;
	OutHitResult.TraceEnd = End;

	for (int32 HitIdx = 0; HitIdx < HitResults.Num(); ++HitIdx)
	{
		const FHitResult& Hit = HitResults[HitIdx];

		if (!Hit.GetActor() || Hit.GetActor() != Ability->GetCurrentActorInfo()->AvatarActor.Get())
		{
			// If bLookForInteractableActor is false, we're looking for an endpoint to trace to
			if (bLookForInteractableActor && Hit.GetActor())
			{
				// bLookForInteractableActor is true, hit component must overlap COLLISION_INTERACTABLE trace channel
				// This is so that a big Actor like a computer can have a small interactable button.
				if (Hit.Component.IsValid() && Hit.Component.Get()->GetCollisionResponseToChannel(COLLISION_INTERACTABLE)
					== ECollisionResponse::ECR_Overlap)
				{
					// Component/Actor must be available to interact
					const bool bIsInteractable = Hit.GetActor()->Implements<UInteractable>();

					if (bIsInteractable && IInteractable::Execute_IsAvailableForInteraction(Hit.GetActor(), Hit.Component.Get(), Ability->GetAvatarActorFromActorInfo()))
					{
						OutHitResult = Hit;
						OutHitResult.bBlockingHit = true; // treat it as a blocking hit
						return;
					}
				}

				OutHitResult.TraceEnd = Hit.Location;
				OutHitResult.bBlockingHit = false; // False means it isn't valid to interact with
				return;
			}

			// This is for the first line trace to get an end point to trace to
			// !Hit.Actor.IsValid() implies we didn't hit anything so return the endpoint as a blocking hit
			// Or if we hit something else
			OutHitResult = Hit;
			OutHitResult.bBlockingHit = true; // treat it as a blocking hit
			return;
		}
	}
}

void UGAT_WaitInteractableTarget::AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd, bool bIgnorePitch) const
{
	if (!Ability) // Server and launching client only
	{
		return;
	}

	const APlayerController* const PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	// Default to TraceStart if no PlayerController
	FVector ViewStart = TraceStart;
	FRotator ViewRot(0.0f);
	if (PC)
	{
		PC->GetPlayerViewPoint(ViewStart, ViewRot);
	}

	const FVector ViewDir = ViewRot.Vector();
	FVector ViewEnd = ViewStart + (ViewDir * MaxRange);

	ClipCameraRayToAbilityRange(ViewStart, ViewDir, TraceStart, MaxRange, ViewEnd);

	FHitResult HitResult;
	LineTrace(HitResult, InSourceActor->GetWorld(), ViewStart, ViewEnd, TraceProfile.Name, Params, false);

	const bool bUseTraceResult = HitResult.bBlockingHit && (FVector::DistSquared(TraceStart, HitResult.Location) <= (MaxRange * MaxRange));

	const FVector AdjustedEnd = (bUseTraceResult) ? HitResult.Location : ViewEnd;

	FVector AdjustedAimDir = (AdjustedEnd - TraceStart).GetSafeNormal();
	if (AdjustedAimDir.IsZero())
	{
		AdjustedAimDir = ViewDir;
	}

	if (!bTraceAffectsAimPitch && bUseTraceResult)
	{
		const FVector OriginalAimDir = (ViewEnd - TraceStart).GetSafeNormal();

		if (!OriginalAimDir.IsZero())
		{
			// Convert to angles and use original pitch
			const FRotator OriginalAimRot = OriginalAimDir.Rotation();

			FRotator AdjustedAimRot = AdjustedAimDir.Rotation();
			AdjustedAimRot.Pitch = OriginalAimRot.Pitch;

			AdjustedAimDir = AdjustedAimRot.Vector();
		}
	}

	OutTraceEnd = TraceStart + (AdjustedAimDir * MaxRange);
}

bool UGAT_WaitInteractableTarget::ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition) const
{
	const FVector CameraToCenter = AbilityCenter - CameraLocation;
	const float DotToCenter = FVector::DotProduct(CameraToCenter, CameraDirection);
	if (DotToCenter >= 0)		//If this fails, we're pointed away from the center, but we might be inside the sphere and able to find a good exit point.
	{
		const float DistanceSquared = CameraToCenter.SizeSquared() - (DotToCenter * DotToCenter);
		const float RadiusSquared = (AbilityRange * AbilityRange);
		if (DistanceSquared <= RadiusSquared)
		{
			const float DistanceFromCamera = FMath::Sqrt(RadiusSquared - DistanceSquared);
			const float DistanceAlongRay = DotToCenter + DistanceFromCamera;						//Subtracting instead of adding will get the other intersection point
			ClippedPosition = CameraLocation + (DistanceAlongRay * CameraDirection);		//Cam aim point clipped to range sphere
			return true;
		}
	}
	return false;
}

void UGAT_WaitInteractableTarget::PerformTrace()
{
	const bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	AActor* const SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
	if (!SourceActor)
	{
		// Hero is dead
		//UE_LOG(LogTemp, Error, TEXT("%s %s SourceActor was null"), *FString(__FUNCTION__), *UGSBlueprintFunctionLibrary::GetPlayerEditorWindowRole(GetWorld()));
		return;
	}

	ActorsToIgnore.Add(SourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGameplayAbilityTargetActor_SingleLineTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	// Calculate TraceEnd
	FVector TraceStart = StartLocation.GetTargetingTransform().GetLocation();
	FVector TraceEnd;
	AimWithPlayerController(SourceActor, Params, TraceStart, TraceEnd); //Effective on server and launching client only

	// ------------------------------------------------------

	FHitResult ReturnHitResult;
	LineTrace(ReturnHitResult, GetWorld(), TraceStart, TraceEnd, TraceProfile.Name, Params, true);
	
	// Default to end of trace line if we don't hit a valid, available Interactable Actor
	// bBlockingHit = valid, available Interactable Actor
	if (!ReturnHitResult.bBlockingHit)
	{
		// No valid, available Interactable Actor

		ReturnHitResult.Location = TraceEnd;
		if (TargetData.Num() > 0 && TargetData.Get(0)->GetHitResult()->GetActor())
		{
			// Previous trace had a valid Interactable Actor, now we don't have one
			// Broadcast last valid target
			LostInteractableTarget.Broadcast(TargetData);
		}

		TargetData = MakeTargetData(ReturnHitResult);
	}
	else
	{
		// Valid, available Interactable Actor

		bool bBroadcastNewTarget = true;

		if (TargetData.Num() > 0)
		{
			const AActor* const OldTarget = TargetData.Get(0)->GetHitResult()->GetActor();

			if (OldTarget == ReturnHitResult.GetActor())
			{
				// Old target is the same as the new target, don't broadcast the target
				bBroadcastNewTarget = false;
			}
			else if (OldTarget)
			{
				// Old target exists and is different from the new target
				// Broadcast last valid target
				LostInteractableTarget.Broadcast(TargetData);
			}
		}

		if (bBroadcastNewTarget)
		{
			// Broadcast new valid target
			TargetData = MakeTargetData(ReturnHitResult);
			FoundNewInteractableTarget.Broadcast(TargetData);
		}
	}

#if ENABLE_DRAW_DEBUG
	if (bShowDebug)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, TimerPeriod);
		
		if (ReturnHitResult.bBlockingHit)
		{
			DrawDebugSphere(GetWorld(), ReturnHitResult.Location, 20.0f, 16, FColor::Red, false, TimerPeriod);
		}
		else
		{
			DrawDebugSphere(GetWorld(), ReturnHitResult.TraceEnd, 20.0f, 16, FColor::Green, false, TimerPeriod);
		}
	}
#endif // ENABLE_DRAW_DEBUG
}

FGameplayAbilityTargetDataHandle UGAT_WaitInteractableTarget::MakeTargetData(const FHitResult& HitResult) const
{
	/** Note: This will be cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
	return StartLocation.MakeTargetDataHandleFromHitResult(Ability, HitResult);
}
