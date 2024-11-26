// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerTorchActivationTest.h"
#include "Evidence/Items/Equipment/Torch.h"
#include "Components/SpotLightComponent.h"

AServerTorchActivationTest::AServerTorchActivationTest()
{
}

void AServerTorchActivationTest::StartTest()
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

void AServerTorchActivationTest::OnEquip()
{
	if ((ServerTestInfo.MyCharacter->GetEquipped() != ServerTorch) ||
		(Client1TestInfo.ServerCharacter->GetEquipped() != Client1Torch) ||
		(Client2TestInfo.ServerCharacter->GetEquipped() != Client2Torch))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to equip"));
	}

	InjectInput(ServerTestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	FTimerHandle ActivateHandle;
	GetWorldTimerManager().SetTimer(ActivateHandle, this, &ThisClass::OnActivate, 1.0f, false);
}

void AServerTorchActivationTest::OnActivate()
{
	if ((ServerTorch->GetLightComponent()->GetVisibleFlag() == false) ||
		(Client1Torch->GetLightComponent()->GetVisibleFlag() == false) ||
		(Client2Torch->GetLightComponent()->GetVisibleFlag() == false))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to activate"));
	}

	InjectInput(ServerTestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	FTimerHandle DeactivateHandle;
	GetWorldTimerManager().SetTimer(DeactivateHandle, this, &ThisClass::OnDeactivate, 1.0f, false);
}

void AServerTorchActivationTest::OnDeactivate()
{
	if ((ServerTorch->GetLightComponent()->GetVisibleFlag() == false) &&
		(Client1Torch->GetLightComponent()->GetVisibleFlag() == false) &&
		(Client2Torch->GetLightComponent()->GetVisibleFlag() == false))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to deactivate"));
	}
}

