// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MPTestHelpersBPLibrary.h"
#include "Evidence/Game/EvidenceGameMode.h"
#include "Evidence/Items/Buttons/MatchStateButton.h"
#include "AdvancedAbilityComponent.h"

AEvidenceGameMode* UTestFunctionLibrary::GetEvidenceGameMode(UWorld* World)
{
	return Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(World));
}

AMatchStateButton* UTestFunctionLibrary::GetMatchStateButton(UWorld* World)
{
	AMatchStateButton* Button = Cast<AMatchStateButton>(UGameplayStatics::GetActorOfClass(World, AMatchStateButton::StaticClass()));

	return Button;
}

AMatchStateButton* UTestFunctionLibrary::GetMatchStateButton(const uint8 ClientIndex)
{
	AMatchStateButton* Button = Cast<AMatchStateButton>(UMPTestHelpersBPLibrary::GetClientActorOfClass(AMatchStateButton::StaticClass(), ClientIndex));

	return Button;
}

void UTestFunctionLibrary::StartSetupPeriod(UWorld* World)
{
	AEvidenceGameMode* EvidenceGameMode = GetEvidenceGameMode(World);

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
