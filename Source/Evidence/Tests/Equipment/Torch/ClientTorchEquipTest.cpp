// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientTorchEquipTest.h"
#include "Evidence/Items/Equipment/Torch.h"

AClientTorchEquipTest::AClientTorchEquipTest()
{
}

void AClientTorchEquipTest::StartTest()
{
	Super::StartTest();

	ServerTorch = Cast<ATorch>(UGameplayStatics::GetActorOfClass(GetWorld(), ATorch::StaticClass()));
	Client1Torch= Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 0));
	Client2Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 1));

	if (!ServerTorch || !Client1Torch || !Client2Torch)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch missing from level"));
	}

	// Assumes Interact abilities are functional because it is difficult to get the characters to spawn
	// in the same place consistently and, therefore, it is difficult to line up the player and equipment 
	// for interaction
	ServerTestInfo.Client1Character->Pickup(ServerTorch);

	FTimerHandle EquipHandle;
	GetWorldTimerManager().SetTimer(EquipHandle, this, &ThisClass::OnEquip, 1.0f, false);
}

void AClientTorchEquipTest::OnEquip()
{
	if ((ServerTestInfo.Client1Character->GetEquipped() != ServerTorch) ||
		(Client1TestInfo.MyCharacter->GetEquipped() != Client1Torch) ||
		(Client2TestInfo.OtherClientCharacter->GetEquipped() != Client2Torch))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}

	InjectInput(Client1TestInfo.InputSubsystem, DropAction, FVector(1, 0, 0));

	FTimerHandle DropHandle;
	GetWorldTimerManager().SetTimer(DropHandle, this, &ThisClass::OnDrop, 1.0f, false);
}

void AClientTorchEquipTest::OnDrop()
{
	if ((ServerTestInfo.Client1Character->GetEquipped() == nullptr) &&
		(Client1TestInfo.MyCharacter->GetEquipped() == nullptr) &&
		(Client2TestInfo.OtherClientCharacter->GetEquipped() == nullptr))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
}
