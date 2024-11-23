// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientMovementSpeedCapTest.h"
#include "AdvancedAbilityComponent.h"

AClientMovementSpeedCapTest::AClientMovementSpeedCapTest()
{
	TimeLimit = 5.0f;
	TimesUpResult = EFunctionalTestResult::Succeeded;
}

void AClientMovementSpeedCapTest::StartTest()
{
	Super::StartTest();

	UAdvancedAbilityComponent* AbilityComponent = Client1TestInfo.MyCharacter->GetComponentByClass<UAdvancedAbilityComponent>();

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

void AClientMovementSpeedCapTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTestHasBegun)
	{
		if (Client1TestInfo.MyCharacter->GetMoveSpeed() > MAX_MOVEMENT_SPEED || ServerTestInfo.Client1Character->GetMoveSpeed() > MAX_MOVEMENT_SPEED)
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Failed"));
		}
	}
}
