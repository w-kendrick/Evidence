// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerTorchPowerDrainTest.h"
#include "Evidence/Items/Equipment/Torch.h"

AServerTorchPowerDrainTest::AServerTorchPowerDrainTest()
{
}

void AServerTorchPowerDrainTest::StartTest()
{
	Super::StartTest();

	ServerTorch = Cast<ATorch>(UGameplayStatics::GetActorOfClass(GetWorld(), ATorch::StaticClass()));
	Client1Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 0));
	Client2Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 1));

	if (!ServerTorch || !Client1Torch || !Client2Torch)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch missing from level"));
	}

	ServerTestInfo.MyCharacter->Pickup(ServerTorch);

	FTimerHandle EquipHandle;
	GetWorldTimerManager().SetTimer(EquipHandle, this, &ThisClass::OnEquip, 1.0f, false);
}

void AServerTorchPowerDrainTest::OnEquip()
{
	if ((ServerTestInfo.MyCharacter->GetEquipped() != ServerTorch) ||
		(Client1TestInfo.ServerCharacter->GetEquipped() != Client1Torch) ||
		(Client2TestInfo.ServerCharacter->GetEquipped() != Client2Torch))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to equip"));
	}

	if ((ServerTorch->GetPower() != 100.f) ||
		(Client1Torch->GetPower() != 100.f) ||
		(Client2Torch->GetPower() != 100.f))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch not at 100% power"));
	}

	InjectInput(ServerTestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	FTimerHandle ActivateHandle;
	GetWorldTimerManager().SetTimer(ActivateHandle, this, &ThisClass::OnActivate, 1.0f, false);
}

void AServerTorchPowerDrainTest::OnActivate()
{
	if ((ServerTorch->GetPower() == 100.f) ||
		(Client1Torch->GetPower() == 100.f) ||
		(Client2Torch->GetPower() == 100.f))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch has not drained power since activation"));
	}

	InjectInput(ServerTestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	PowerAtDeactivation = ServerTorch->GetPower();

	FTimerHandle DeactivateHandle;
	GetWorldTimerManager().SetTimer(DeactivateHandle, this, &ThisClass::OnDeactivate, 1.0f, false);
}

void AServerTorchPowerDrainTest::OnDeactivate()
{
	if (FMath::IsNearlyEqual(ServerTorch->GetPower(), PowerAtDeactivation, 0.1f) &&
		FMath::IsNearlyEqual(Client1Torch->GetPower(), PowerAtDeactivation, 0.1f) &&
		FMath::IsNearlyEqual(Client2Torch->GetPower(), PowerAtDeactivation, 0.1f))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch power has changed since deactivation"));
	}
}
