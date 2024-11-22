// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientMoveBackwardTest.h"

AClientMoveBackwardTest::AClientMoveBackwardTest()
{

}

void AClientMoveBackwardTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(Client2TestInfo.InputSubsystem, MoveAction, FVector(0, -1, 0));
}

void AClientMoveBackwardTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.Client2Character)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AClientMoveBackwardTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.OtherClientCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientMoveBackwardTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.MyCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}