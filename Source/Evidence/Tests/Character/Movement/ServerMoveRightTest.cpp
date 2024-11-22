// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMoveRightTest.h"

AServerMoveRightTest::AServerMoveRightTest()
{

}

void AServerMoveRightTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(1, 0, 0));
}

void AServerMoveRightTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.MyCharacter)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AServerMoveRightTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.ServerCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AServerMoveRightTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.ServerCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}