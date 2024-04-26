// Fill out your copyright notice in the Description page of Project Settings.


#include "TrueTrackerDart.h"

ATrueTrackerDart::ATrueTrackerDart()
{

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
	OnTrackDartBroadcast.Broadcast(GetActorLocation());
	
	CurrentBroadcastCount++;

	if (CurrentBroadcastCount >= MaxBroadcastCount)
	{
		GetWorldTimerManager().ClearTimer(BroadcastHandle);
	}
}
