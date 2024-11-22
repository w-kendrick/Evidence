// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientMoveRightTest.h"

AClientMoveRightTest::AClientMoveRightTest()
{

}

void AClientMoveRightTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(Client2TestInfo.InputSubsystem, MoveAction, FVector(1, 0, 0));
}

void AClientMoveRightTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.Client2Character)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AClientMoveRightTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.OtherClientCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientMoveRightTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.MyCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}