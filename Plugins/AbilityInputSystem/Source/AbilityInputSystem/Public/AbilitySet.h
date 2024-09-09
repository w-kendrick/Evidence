// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"
#include "ActiveGameplayEffectHandle.h"
#include "AdvancedAbilityComponent.h"
#include "AbilitySet.generated.h"

class UAdvancedAbilityComponent;
class UAdvancedGameplayAbility;
class UAttributeSet;
class UGameplayEffect;

/**
 * FAbilitySet_GameplayAbility
 *
 *	Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAdvancedGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * FAbilitySet_GameplayEffect
 *
 *	Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};


/**
 * FAbilitySet_GrantedHandles
 *
 *	Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(UAdvancedAbilityComponent* AASC)
	{
		check(AASC);

		if (!AASC->IsOwnerActorAuthoritative())
		{
			// Must be authoritative to give or take ability sets.
			return;
		}

		for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
		{
			if (Handle.IsValid())
			{
				AASC->ClearAbility(Handle);
			}
		}

		for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
		{
			if (Handle.IsValid())
			{
				AASC->RemoveActiveGameplayEffect(Handle);
			}
		}

		for (UAttributeSet* Set : GrantedAttributeSets)
		{
			AASC->RemoveSpawnedAttribute(Set);
		}

		AbilitySpecHandles.Reset();
		GameplayEffectHandles.Reset();
		GrantedAttributeSets.Reset();
	}

	template<class T>
	T* FindAttributeSetByClass() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, const UAttributeSet>::Value, "'T' template parameter to FindAttributeSetByClass must be derived from UAttributeSet");

		T* Result = nullptr;

		for (TObjectPtr<UAttributeSet> Set : GrantedAttributeSets)
		{
			if (Set.GetClass() == T::StaticClass())
			{
				Result = (T*)Set.Get();
			}
		}

		return Result;
	}

protected:

	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to the granted attribute sets
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

/**
 * 
 */
UCLASS()
class ABILITYINPUTSYSTEM_API UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(UAdvancedAbilityComponent* AASC, FAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilitySet_GameplayAbility> Abilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilitySet_GameplayEffect> Effects;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UAttributeSet>> AttributeSets;
	
};
