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

void AClientCrouchTest::OnTrigger1BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient1Passed = true;
		CheckResult();
	}
}

void AClientCrouchTest::OnTrigger2BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	const ABaseCharacter* const Character = Cast<ABaseCharacter>(OtherActor);

	if (Character)
	{
		bClient2Passed = true;
		CheckResult();
	}
}