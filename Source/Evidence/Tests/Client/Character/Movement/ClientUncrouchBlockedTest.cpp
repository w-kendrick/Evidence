// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientUncrouchBlockedTest.h"

AClientUncrouchBlockedTest::AClientUncrouchBlockedTest()
{
	TimeLimit = 10.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AClientUncrouchBlockedTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(Client2TestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));

	StartInjectContinuousInput(Client2TestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));

	FTimerHandle Step2Handle;
	GetWorldTimerManager().SetTimer(Step2Handle, this, &ThisClass::Step2, 5.0f, false);
}

void AClientUncrouchBlockedTest::Step2()
{
	InjectInput(Client2TestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));
}

void AClientUncrouchBlockedTest::OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}

void AClientUncrouchBlockedTest::OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}