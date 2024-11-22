// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerCrouchTest.h"

AServerCrouchTest::AServerCrouchTest()
{

}

void AServerCrouchTest::StartTest()
{
	Super::StartTest();

	BindTriggers();

	InjectInput(ServerTestInfo.InputSubsystem, CrouchAction, FVector(1, 0, 0));

	StartInjectContinuousInput(ServerTestInfo.InputSubsystem, MoveAction, FVector(0, 1, 0));
}

void AServerCrouchTest::OnServerTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == ServerTestInfo.MyCharacter)
	{
		bServerPassed = true;
		CheckResult();
	}
}

void AServerCrouchTest::OnClient1TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client1TestInfo.ServerCharacter)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AServerCrouchTest::OnClient2TriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character == Client2TestInfo.ServerCharacter)
	{
		bClient2Passed = true;
		CheckResult();
	}
}