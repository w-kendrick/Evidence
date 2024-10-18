// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Game/EvidenceGameMode.h"

UHealthSet::UHealthSet()
{
	isAlive = true;
	DeathEventTag = FGameplayTag::RequestGameplayTag("GameplayEvent.Death");
}

void UHealthSet::Respawn()
{
	isAlive = true;
}

void UHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float NewHealth = GetHealth() - GetDamage();
		SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

		if (GetHealth() == 0.0f && isAlive)
		{
			DeathEvent(Data);
		}
	}
}

void UHealthSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthSet, Health, OldHealth);
}

void UHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthSet, Health, OldMaxHealth);
}

void UHealthSet::DeathEvent(const FGameplayEffectModCallbackData& Data)
{
	isAlive = false;

	FGameplayEventData Payload;
	Payload.ContextHandle = Data.EffectSpec.GetContext();
	Payload.EventTag = DeathEventTag;
	Payload.Instigator = Data.EffectSpec.GetEffectContext().GetInstigator();
	Payload.Target = GetOwningActor();
	Payload.InstigatorTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	Payload.TargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

	GetOwningAbilitySystemComponentChecked()->HandleGameplayEvent(Payload.EventTag, &Payload);

	AEvidenceGameMode* const EvidenceGameMode = Cast<AEvidenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (EvidenceGameMode)
	{
		EvidenceGameMode->OnPlayerDeath(GetActorInfo()->PlayerController.Get());
	}
}
