// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientInitialHealthTest.h"

AClientInitialHealthTest::AClientInitialHealthTest()
{
}

void AClientInitialHealthTest::StartTest()
{
	Super::StartTest();

	const bool Client1_Result = (Client1TestInfo.MyCharacter->GetHealth() == 100.f) && (Client1TestInfo.MyCharacter->GetMaxHealth() == 100.f);
	const bool Client2_Result = (Client2TestInfo.MyCharacter->GetHealth() == 100.f) && (Client2TestInfo.MyCharacter->GetMaxHealth() == 100.f);

	bool Server_Result = true;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		ABaseCharacter* Character = Cast<ABaseCharacter>(Actor);

		if (Character)
		{
			Server_Result &= (Character->GetHealth() == 100.f) && (Character->GetMaxHealth() == 100.f);
		}
	}

	if (Server_Result && Client1_Result && Client2_Result)
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Passed"));
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
	}
}
