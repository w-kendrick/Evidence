// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientLookLeftTest.h"
#include "Camera/CameraComponent.h"

AClientLookLeftTest::AClientLookLeftTest()
{
}

void AClientLookLeftTest::StartTest()
{
	Super::StartTest();

	StartInjectContinuousInput(Client1TestInfo.InputSubsystem, LookAction, FVector(-1, 0, 0));
}

void AClientLookLeftTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (Check(Client1TestInfo.MyCharacter) &&
			Check(ServerTestInfo.Client1Character) &&
			Check(Client2TestInfo.OtherClientCharacter))
		{
			FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
		}
	}
}

bool AClientLookLeftTest::Check(ABaseCharacter* Character)
{
	bool bResult = false;

	TArray<AActor*> IgnoredActors = { Character };
	const FVector Start = Character->GetCameraComponent()->GetComponentLocation();
	const FVector End = Start + Character->GetCameraComponent()->GetComponentRotation().Vector() * 10000.f;
	FHitResult Hit;

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, Objects, false, IgnoredActors, EDrawDebugTrace::None, Hit, false))
	{
		bResult = true;
	}

	return bResult;
}
