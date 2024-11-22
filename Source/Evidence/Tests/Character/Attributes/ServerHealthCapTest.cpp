// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerHealthCapTest.h"
#include "AdvancedAbilityComponent.h"

AServerHealthCapTest::AServerHealthCapTest()
{
	TimeLimit = 5.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AServerHealthCapTest::StartTest()
{
	Super::StartTest();

	UAdvancedAbilityComponent* AbilityComponent = ServerTestInfo.MyCharacter->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(AwardHealthEffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
}

void AServerHealthCapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (ServerTestInfo.Client1Character->GetHealth() > MAX_HEALTH)
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
		}
	}
}
