// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageCalculation.h"
#include "Evidence/Character/Abilities/AttributeSets/CharacterAttributeSet.h"
#include "Evidence/Character/Abilities/CharacterAbilitySystemComponent.h"

struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Damage, Source, true);
	}
};

static const DamageStatics& GetDamageStatics()
{
	static DamageStatics DStatics;
	return DStatics;
}

UDamageCalculation::UDamageCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.0f;
	// Capture optional damage value set on the damage GE as a CalculationModifier under the ExecutionCalculation
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().DamageDef, EvaluationParameters, Damage);
	// Add SetByCaller damage if it exists
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	if (Damage > 0.f)
	{
		// Set the Target's damage meta attribute
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageStatics().DamageProperty, EGameplayModOp::Additive, Damage));
	}
}
