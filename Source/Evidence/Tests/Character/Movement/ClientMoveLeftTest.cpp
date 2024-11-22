// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientMoveLeftTest.h"

AClientMoveLeftTest::AClientMoveLeftTest()
{

}

void AClientMoveLeftTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(Client2TestInfo.InputSubsystem, MoveAction, FVector(-1, 0, 0));
}

void AClientMoveLeftTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.Client2Character)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AClientMoveLeftTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.OtherClientCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientMoveLeftTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.MyCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}