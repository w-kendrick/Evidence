// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientNoCollisionOnDeathTest.h"
#include "Components/CapsuleComponent.h"

AClientNoCollisionOnDeathTest::AClientNoCollisionOnDeathTest()
{
}

void AClientNoCollisionOnDeathTest::StartTest()
{
	Super::StartTest();

	UTestFunctionLibrary::StartSetupPeriod(GetWorld());

	if ((ServerTestInfo.Client2Character->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Block) ||
		(Client1TestInfo.OtherClientCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Block) || 
		(Client2TestInfo.MyCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Block))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Initial capsule collision response to Pawn is not block"));
	}

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client2Character, KillPlayerEffectClass);

	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &ThisClass::OnDeath, 1.0f, false);
}

void AClientNoCollisionOnDeathTest::OnDeath()
{
	if ((ServerTestInfo.Client2Character->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Ignore) ||
		(Client1TestInfo.OtherClientCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Ignore) ||
		(Client2TestInfo.MyCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Ignore))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Death capsule collision response to Pawn is not ignore"));
	}

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.MyCharacter, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client1Character, KillPlayerEffectClass);

	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &ThisClass::OnRespawn, 10.0f, false);
}

void AClientNoCollisionOnDeathTest::OnRespawn()
{
	if ((ServerTestInfo.Client2Character->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECollisionResponse::ECR_Block) &&
		(Client1TestInfo.OtherClientCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECollisionResponse::ECR_Block) &&
		(Client2TestInfo.MyCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECollisionResponse::ECR_Block))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Respawn capsule collision response to Pawn is not block"));
	}
}
