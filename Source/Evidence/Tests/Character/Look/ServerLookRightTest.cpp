// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerLookRightTest.h"
#include "Camera/CameraComponent.h"

AServerLookRightTest::AServerLookRightTest()
{
}

void AServerLookRightTest::StartTest()
{
	Super::StartTest();

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, LookAction, FVector(1, 0, 0));
}

void AServerLookRightTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (Check(ServerTestInfo.MyCharacter) &&
			Check(Client1TestInfo.ServerCharacter) &&
			Check(Client2TestInfo.ServerCharacter))
		{
			FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
		}
	}
}

bool AServerLookRightTest::Check(ABaseCharacter* Character)
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
