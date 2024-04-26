// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueTrackerDart.h"
#include "Evidence/EvidenceGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Items/Hub.h"

ATrueTrackerDart::ATrueTrackerDart()
{

}

void ATrueTrackerDart::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AEvidenceGameState* EGS = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (EGS)
		{
			AHub* Hub = EGS->GetHub();
			if (Hub)
			{
				Hub->SubscribeToTrackerDart(this);
			}
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
	OnTrackDartBroadcast.Broadcast(this, GetActorLocation());
	
	CurrentBroadcastCount++;

	if (CurrentBroadcastCount >= MaxBroadcastCount)
	{
		GetWorldTimerManager().ClearTimer(BroadcastHandle);
	}
}
