// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientTorchActivationTest.h"
#include "Evidence/Items/Equipment/Torch.h"
#include "Components/SpotLightComponent.h"

AClientTorchActivationTest::AClientTorchActivationTest()
{
}

void AClientTorchActivationTest::StartTest()
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

void AClientTorchActivationTest::OnEquip()
{
	if ((ServerTestInfo.Client1Character->GetEquipped() != ServerTorch) ||
		(Client1TestInfo.MyCharacter->GetEquipped() != Client1Torch) ||
		(Client2TestInfo.OtherClientCharacter->GetEquipped() != Client2Torch))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to equip"));
	}

	InjectInput(Client1TestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	FTimerHandle ActivateHandle;
	GetWorldTimerManager().SetTimer(ActivateHandle, this, &ThisClass::OnActivate, 1.0f, false);
}

void AClientTorchActivationTest::OnActivate()
{
	if ((ServerTorch->GetLightComponent()->GetVisibleFlag() == false) || 
		(Client1Torch->GetLightComponent()->GetVisibleFlag() == false) ||
		(Client2Torch->GetLightComponent()->GetVisibleFlag() == false))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed to activate"));
	}

	InjectInput(Client1TestInfo.InputSubsystem, UseAction, FVector(1, 0, 0));

	FTimerHandle DeactivateHandle;
	GetWorldTimerManager().SetTimer(DeactivateHandle, this, &ThisClass::OnDeactivate, 1.0f, false);
}

void AClientTorchActivationTest::OnDeactivate()
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
