// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientHealthCapTest.h"
#include "AdvancedAbilityComponent.h"

AClientHealthCapTest::AClientHealthCapTest()
{
	TimeLimit = 5.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AClientHealthCapTest::StartTest()
{
	Super::StartTest();

	UAdvancedAbilityComponent* AbilityComponent = Client1TestInfo.MyCharacter->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(AwardHealthEffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Character has no ability system component"));
	}
}

void AClientHealthCapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (Client1TestInfo.MyCharacter->GetHealth() > MAX_HEALTH || ServerTestInfo.Client1Character->GetHealth() > MAX_HEALTH)
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
		}
	}
}
