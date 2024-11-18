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

void AClientMoveBackwardTest::OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientMoveBackwardTest::OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient2Passed = true;
		CheckResult();
	}
}