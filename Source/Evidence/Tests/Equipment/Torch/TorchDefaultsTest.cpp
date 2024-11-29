// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchDefaultsTest.h"
#include "Evidence/Items/Equipment/Torch.h"

ATorchDefaultsTest::ATorchDefaultsTest()
{
}

void ATorchDefaultsTest::StartTest()
{
	Super::StartTest();

	ServerTorch = Cast<ATorch>(UGameplayStatics::GetActorOfClass(GetWorld(), ATorch::StaticClass()));
	Client1Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 0));
	Client2Torch = Cast<ATorch>(UMPTestHelpersBPLibrary::GetClientActorOfClass(ATorch::StaticClass(), 1));

	if (!ServerTorch || !Client1Torch || !Client2Torch)
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch missing from level"));
	}

	if ((ServerTorch->GetPower() == ServerTorch->GetMaxPower() && ServerTorch->GetPower() == 100.f) && 
		(Client1Torch->GetPower() == Client1Torch->GetMaxPower() && Client1Torch->GetPower() == 100.f) &&
		(Client2Torch->GetPower() == Client2Torch->GetMaxPower() && Client2Torch->GetPower() == 100.f))
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Torch power not defaulted to 100"));
	}
}
