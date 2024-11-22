// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMoveForwardTest.h"

AServerMoveForwardTest::AServerMoveForwardTest()
{

}

void AServerMoveForwardTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));
}

void AServerMoveForwardTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.MyCharacter)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AServerMoveForwardTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.ServerCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AServerMoveForwardTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.ServerCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}