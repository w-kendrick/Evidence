// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerUncrouchTest.h"

AServerUncrouchTest::AServerUncrouchTest()
{
	TimeLimit = 10.0f;
}

void AServerUncrouchTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(ServerTestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));

	FTimerHandle Step2Handle;
	GetWorldTimerManager().SetTimer(Step2Handle, this, &ThisClass::Step2, 5.0f, false);
}

void AServerUncrouchTest::Step2()
{
	InjectInput(ServerTestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));
}

void AServerUncrouchTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.MyCharacter)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AServerUncrouchTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.ServerCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AServerUncrouchTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.ServerCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}