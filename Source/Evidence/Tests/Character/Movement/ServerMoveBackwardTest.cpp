// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMoveBackwardTest.h"

AServerMoveBackwardTest::AServerMoveBackwardTest()
{

}

void AServerMoveBackwardTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(0, -1, 0));
}

void AServerMoveBackwardTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.MyCharacter)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AServerMoveBackwardTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.ServerCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AServerMoveBackwardTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.ServerCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}