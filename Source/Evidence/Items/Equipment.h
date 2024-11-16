// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "Evidence/Delegates.h"
#include "AbilitySet.h"
#include "Equipment.generated.h"

class ABaseCharacter;

UCLASS()
class EVIDENCE_API AEquipment : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEquipment();

	FOnAttachmentsUpdated OnAttachmentsUpdated;

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	virtual FString GetInteractionString_Implementation() override;

	void Pickup(ABaseCharacter* Char);
	void Stow(ABaseCharacter* Char);
	void Drop();

	void Attach(ABaseCharacter* Char, const bool isVisible);
	void Detach();

	FORCEINLINE USkeletalMeshComponent* GetWorldMesh() const { return WorldMesh; }
	FORCEINLINE FString GetEquipmentName() const { return EquipmentName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WorldMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* LocalMesh;

	bool bIsPickedUp = false;

	UPROPERTY(EditDefaultsOnly)
	FName EquipSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<const UAbilitySet> AbilitySet;

	FAbilitySet_GrantedHandles GrantedHandles;

	UPROPERTY(EditDefaultsOnly)
	FString EquipmentName;

private:
	void FindGround(FVector& Location, FRotator& Rotation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float MaxGroundDistance = 10000.f;

	void AddAbilities(ABaseCharacter* Char);
	void RemoveAbilities(ABaseCharacter* Char);

};
