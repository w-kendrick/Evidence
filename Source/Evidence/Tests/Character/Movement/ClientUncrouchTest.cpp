// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientUncrouchTest.h"

AClientUncrouchTest::AClientUncrouchTest()
{
	TimeLimit = 10.0f;
}

void AClientUncrouchTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(Client2TestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));

	StartInjectContinuousInput(Client2TestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));

	FTimerHandle Step2Handle;
	GetWorldTimerManager().SetTimer(Step2Handle, this, &ThisClass::Step2, 5.0f, false);
}

void AClientUncrouchTest::Step2()
{
	InjectInput(Client2TestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));
}

void AClientUncrouchTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientUncrouchTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient2Passed = true;
		CheckResult();
	}
}
