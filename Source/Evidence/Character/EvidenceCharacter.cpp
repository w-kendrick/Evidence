// Copyright Epic Games, Inc. All Rights Reserved.

#include "EvidenceCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Abilities/EIGameplayAbility.h"

#pragma region Class Essentials

AEvidenceCharacter::AEvidenceCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("CharacterAbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
}

#pragma endregion

#pragma region Abilities

void AEvidenceCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		InitializeAttributes();

		AddCharacterAbilities();
	}
}

void AEvidenceCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void AEvidenceCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent)
	{
		return;
	}

	for (TSubclassOf<UEIGameplayAbility>& Ability : StartupAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 0, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->bAbilitiesGiven = true;
}

#pragma endregion

#pragma region Getters

float AEvidenceCharacter::GetHealth() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetHealth();
	}
	return 0.0f;
}

float AEvidenceCharacter::GetMaxHealth() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

#pragma endregion