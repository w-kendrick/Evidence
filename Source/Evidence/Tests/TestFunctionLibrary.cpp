// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "AdvancedAbilityComponent.h"

void UTestFunctionLibrary::StartSetupPeriod(UWorld* World)
{
	AEvidenceGameMode* EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(World));

	if (EvidenceGameMode)
	{
		EvidenceGameMode->EndPreSetup();
	}
}

void UTestFunctionLibrary::KillPlayer(ACharacter* Character, TSubclassOf<UGameplayEffect> KillPlayerEffectClass)
{
	UAdvancedAbilityComponent* AbilityComponent = Character->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(KillPlayerEffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
}
