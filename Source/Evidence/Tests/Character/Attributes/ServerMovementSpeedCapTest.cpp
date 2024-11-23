// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerMovementSpeedCapTest.h"
#include "AdvancedAbilityComponent.h"

AServerMovementSpeedCapTest::AServerMovementSpeedCapTest()
{
	TimeLimit = 5.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AServerMovementSpeedCapTest::StartTest()
{
	Super::StartTest();

	UAdvancedAbilityComponent* AbilityComponent = ServerTestInfo.MyCharacter->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(MovementSpeedEffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Character has no ability system component"));
	}
}

void AServerMovementSpeedCapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (ServerTestInfo.Client1Character->GetMoveSpeed() > MAX_MOVEMENT_SPEED)
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
		}
	}
}
