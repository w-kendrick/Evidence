// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Equipment.generated.h"

class AEvidenceCharacter;
class UEIGameplayAbility;

UCLASS()
class EVIDENCE_API AEquipment : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEquipment();

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;

	void Pickup(AEvidenceCharacter* Char);
	void Drop();

	void Attach(AEvidenceCharacter* Char, const bool isVisible);

	USkeletalMeshComponent* GetWorldMesh() const { return WorldMesh; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WorldMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* LocalMesh;

	bool bIsPickedUp = false;

	UPROPERTY(EditDefaultsOnly)
	FName EquipSocket;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UEIGameplayAbility>> Abilities;

	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;

private:
	void FindGround(FVector& Location, FRotator& Rotation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float MaxGroundDistance = 10000.f;

	void AddAbilities(AEvidenceCharacter* Char);
	void RemoveAbilities(AEvidenceCharacter* Char);
	
};
