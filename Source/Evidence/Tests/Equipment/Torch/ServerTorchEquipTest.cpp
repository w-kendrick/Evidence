// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerTorchEquipTest.h"
#include "Evidence/Items/Equipment/Torch.h"

AServerTorchEquipTest::AServerTorchEquipTest()
{
}

void AServerTorchEquipTest::StartTest()
{
	Super::StartTest();

	ServerTorch = Cast<ATorch>(UGameplayStatics::GetActorOfClass(GetWorld(), ATorch::StaticClass()));
	Client1Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 0));
	Client2Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 1));

	if (!ServerTorch || !Client1Torch || !Client2Torch)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch missing from level"));
	}

	// Assumes Interact abilities are functional because it is difficult to get the characters to spawn
	// in the same place consistently and, therefore, it is difficult to line up the player and equipment 
	// for interaction
	ServerTestInfo.MyCharacter->Pickup(ServerTorch);

	FTimerHandle EquipHandle;
	GetWorldTimerManager().SetTimer(EquipHandle, this, &ThisClass::OnEquip, 1.0f, false);
}

void AServerTorchEquipTest::OnEquip()
{
	if ((ServerTestInfo.MyCharacter->GetEquipped() != ServerTorch) ||
		(Client1TestInfo.ServerCharacter->GetEquipped() != Client1Torch) ||
		(Client2TestInfo.ServerCharacter->GetEquipped() != Client2Torch))
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}

	InjectInput(ServerTestInfo.InputSubsystem, DropAction, FVector(1, 0, 0));

	FTimerHandle DropHandle;
	GetWorldTimerManager().SetTimer(DropHandle, this, &ThisClass::OnDrop, 1.0f, false);
}

void AServerTorchEquipTest::OnDrop()
{
	if ((ServerTestInfo.MyCharacter->GetEquipped() == nullptr) &&
		(Client1TestInfo.ServerCharacter->GetEquipped() == nullptr) &&
		(Client2TestInfo.ServerCharacter->GetEquipped() == nullptr))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
}

