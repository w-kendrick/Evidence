// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientCrouchTest.h"

AClientCrouchTest::AClientCrouchTest()
{

}

void AClientCrouchTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(Client2TestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));

	StartInjectContinuousInput(Client2TestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));
}

void AClientCrouchTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.Client2Character)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AClientCrouchTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.OtherClientCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientCrouchTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.MyCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}