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

void AClientMoveRightTest::OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientMoveRightTest::OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient2Passed = true;
		CheckResult();
	}
}