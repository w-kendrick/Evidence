// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueTrackerDart.h"
#include "Evidence/Hub/Hub.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"

ATrueTrackerDart::ATrueTrackerDart()
{

}

void ATrueTrackerDart::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
		if (Hub)
		{
			Hub->SubscribeToTrackerDart(this);
		}
	}
}

void ATrueTrackerDart::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	AttachToActor(OtherActor, Rules);

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(BroadcastHandle, this, &ThisClass::BroadcastLocation, BroadcastDelay, true, BroadcastDelay);
	}
}

void ATrueTrackerDart::BroadcastLocation()
{
	if (CurrentBroadcastCount >= MaxBroadcastCount)
	{
		GetWorldTimerManager().ClearTimer(BroadcastHandle);

		Destroy();
	}
	else
	{
		OnTrackDartBroadcast.Broadcast(this, GetActorLocation());

		CurrentBroadcastCount++;
	}
}
