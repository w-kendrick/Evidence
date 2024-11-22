// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMoveLeftTest.h"

AServerMoveLeftTest::AServerMoveLeftTest()
{

}

void AServerMoveLeftTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(-1, 0, 0));
}

void AServerMoveLeftTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.MyCharacter)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AServerMoveLeftTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.ServerCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AServerMoveLeftTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.ServerCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}