// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientJumpTest.h"

AClientJumpTest::AClientJumpTest()
{

}

void AClientJumpTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(Client1TestInfo.InputSubsystem, JumpAction, FVector(1, 0, 0));
}

void AClientJumpTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientJumpTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient2Passed = true;
		CheckResult();
	}
}