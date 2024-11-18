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

void AClientMoveLeftTest::OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientMoveLeftTest::OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient2Passed = true;
		CheckResult();
	}
}