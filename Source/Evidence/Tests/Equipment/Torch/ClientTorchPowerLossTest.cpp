// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientTorchPowerLossTest.h"
#include "Evidence/Items/Equipment/Torch.h"
#include "Components/SpotLightComponent.h"

AClientTorchPowerLossTest::AClientTorchPowerLossTest()
{
}

void AClientTorchPowerLossTest::StartTest()
{
	Super::StartTest();

	ServerTorch = Cast<ATorch>(UGameplayStatics::GetActorOfClass(GetWorld(), ATorch::StaticClass()));
	Client1Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 0));
	Client2Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 1));

	if (!ServerTorch || !Client1Torch || !Client2Torch)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch missing from level"));
	}

	ServerTestInfo.Client1Character->Pickup(ServerTorch);

	FTimerHandle EquipHandle;
	GetWorldTimerManager().SetTimer(EquipHandle, this, &ThisClass::OnEquip, 1.0f, false);
}

void AClientTorchPowerLossTest::OnEquip()
{
	if ((ServerTestInfo.Client1Character->GetEquipped() != ServerTorch) ||
		(Client1TestInfo.MyCharacter->GetEquipped() != Client1Torch) ||
		(Client2TestInfo.OtherClientCharacter->GetEquipped() != Client2Torch))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to equip"));
	}

	if ((ServerTorch->GetPower() != 100.f) ||
		(Client1Torch->GetPower() != 100.f) ||
		(Client2Torch->GetPower() != 100.f))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch not at 100% power"));
	}

	InjectInput(Client1TestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	FTimerHandle ActivationHandle;
	GetWorldTimerManager().SetTimer(ActivationHandle, this, &ThisClass::OnActivate, 1.0f, false);
}

void AClientTorchPowerLossTest::OnActivate()
{
	if ((ServerTorch->GetLightComponent()->GetVisibleFlag() == false) ||
		(Client1Torch->GetLightComponent()->GetVisibleFlag() == false) ||
		(Client2Torch->GetLightComponent()->GetVisibleFlag() == false))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to activate"));
	}

	FTimerHandle DrainHandle;
	GetWorldTimerManager().SetTimer(DrainHandle, this, &ThisClass::OnDrained, 5.0f, false);
}

void AClientTorchPowerLossTest::OnDrained()
{
	if ((ServerTorch->GetPower() == 0.0f) &&
		(Client1Torch->GetPower() == 0.0f) &&
		(Client2Torch->GetPower() == 0.0f) &&
		(ServerTorch->GetLightComponent()->GetVisibleFlag() == false) &&
		(Client1Torch->GetLightComponent()->GetVisibleFlag() == false) &&
		(Client2Torch->GetLightComponent()->GetVisibleFlag() == false))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch power not fully drained and deactivated"));
	}
}
