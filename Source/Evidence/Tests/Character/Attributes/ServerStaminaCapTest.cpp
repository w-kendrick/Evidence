// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerStaminaCapTest.h"
#include "AdvancedAbilityComponent.h"

AServerStaminaCapTest::AServerStaminaCapTest()
{
	TimeLimit = 5.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AServerStaminaCapTest::StartTest()
{
	Super::StartTest();

	UAdvancedAbilityComponent* AbilityComponent = ServerTestInfo.MyCharacter->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(AwardStaminaEffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Character has no ability system component"));
	}
}

void AServerStaminaCapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (ServerTestInfo.Client1Character->GetStamina() > MAX_STAMINA)
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
		}
	}
}
