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

void UTestFunctionLibrary::KillPlayer(ACharacter* Character, const TSubclassOf<UGameplayEffect>& KillPlayerEffectClass)
{
	ApplyGameplayEffect(Character, KillPlayerEffectClass);
}

void UTestFunctionLibrary::ApplyGameplayEffect(ACharacter* Character, const TSubclassOf<UGameplayEffect>& EffectClass)
{
	UAdvancedAbilityComponent* AbilityComponent = Character->GetComponentByClass<UAdvancedAbilityComponent>();

	if (AbilityComponent)
	{
		const FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(EffectClass, 1, AbilityComponent->MakeEffectContext());
		AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
}

AEquipment* UTestFunctionLibrary::SpawnEquipment(UWorld* World, const TSubclassOf<AEquipment>& EquipmentClass, const FVector& Location)
{
	AEquipment* NewEquipment = World->SpawnActor<AEquipment>(EquipmentClass, FTransform(Location));

	return NewEquipment;
}
