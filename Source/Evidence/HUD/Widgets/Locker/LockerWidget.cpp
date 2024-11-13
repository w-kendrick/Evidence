// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerWidget.h"
#include "Evidence/Hub/Locker.h"
#include "Kismet/GameplayStatics.h"

void ULockerWidget::LeaveEvent()
{
	ALocker* const Locker = Cast<ALocker>(UGameplayStatics::GetActorOfClass(GetWorld(), ALocker::StaticClass()));

	if (Locker)
	{
		Locker->Relinquish();
	}

	Super::LeaveEvent();
}
