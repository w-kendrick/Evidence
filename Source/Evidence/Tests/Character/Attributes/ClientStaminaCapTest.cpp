// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientStaminaCapTest.h"
#include "AdvancedAbilityComponent.h"

AClientStaminaCapTest::AClientStaminaCapTest()
{
	TimeLimit = 5.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AClientStaminaCapTest::StartTest()
{
	Super::StartTest();

	UAdvancedAbilityComponent* AbilityComponent = Client1TestInfo.MyCharacter->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(AwardStaminaEffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
}

void AClientStaminaCapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (Client1TestInfo.MyCharacter->GetStamina() > MAX_STAMINA || ServerTestInfo.Client1Character->GetStamina() > MAX_STAMINA)
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
		}
	}
}
