// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerUncrouchBlockedTest.h"

AServerUncrouchBlockedTest::AServerUncrouchBlockedTest()
{
	TimeLimit = 10.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AServerUncrouchBlockedTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(ServerTestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));

	FTimerHandle Step2Handle;
	GetWorldTimerManager().SetTimer(Step2Handle, this, &ThisClass::Step2, 5.0f, false);
}

void AServerUncrouchBlockedTest::Step2()
{
	InjectInput(ServerTestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));
}

void AServerUncrouchBlockedTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}

void AServerUncrouchBlockedTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}

void AServerUncrouchBlockedTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}