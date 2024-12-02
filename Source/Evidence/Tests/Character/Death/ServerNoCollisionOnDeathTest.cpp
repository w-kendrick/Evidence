// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerNoCollisionOnDeathTest.h"
#include "Components/CapsuleComponent.h"

AServerNoCollisionOnDeathTest::AServerNoCollisionOnDeathTest()
{
}

void AServerNoCollisionOnDeathTest::StartTest()
{
	Super::StartTest();

	UTestFunctionLibrary::StartSetupPeriod(GetWorld());

	if ((ServerTestInfo.MyCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Block) ||
		(Client1TestInfo.ServerCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Block) ||
		(Client2TestInfo.ServerCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Block))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Initial capsule collision response to Pawn is not block"));
	}

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.MyCharacter, KillPlayerEffectClass);

	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &ThisClass::OnDeath, 1.0f, false);
}

void AServerNoCollisionOnDeathTest::OnDeath()
{
	if ((ServerTestInfo.MyCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Ignore) ||
		(Client1TestInfo.ServerCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Ignore) ||
		(Client2TestInfo.ServerCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Ignore))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Death capsule collision response to Pawn is not ignore"));
	}

	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client1Character, KillPlayerEffectClass);
	UTestFunctionLibrary::KillPlayer(ServerTestInfo.Client2Character, KillPlayerEffectClass);

	FTimerHandle DeathHandle;
	GetWorldTimerManager().SetTimer(DeathHandle, this, &ThisClass::OnRespawn, 10.0f, false);
}

void AServerNoCollisionOnDeathTest::OnRespawn()
{
	if ((ServerTestInfo.MyCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECollisionResponse::ECR_Block) &&
		(Client1TestInfo.ServerCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECollisionResponse::ECR_Block) &&
		(Client2TestInfo.ServerCharacter->GetCapsuleComponent()->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) == ECollisionResponse::ECR_Block))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Respawn capsule collision response to Pawn is not block"));
	}
}
