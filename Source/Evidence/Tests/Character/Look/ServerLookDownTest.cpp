// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerLookDownTest.h"
#include "Camera/CameraComponent.h"

AServerLookDownTest::AServerLookDownTest()
{
}

void AServerLookDownTest::StartTest()
{
	Super::StartTest();

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, LookAction, FVector(0, 1, 0));
}

void AServerLookDownTest::Tick(float DeltaTime)
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

bool AServerLookDownTest::Check(ABaseCharacter* Character)
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
