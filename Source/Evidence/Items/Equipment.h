// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/AbilityActor.h"
#include "Interactable.h"
#include "Equipment.generated.h"

class AEvidencePlayerCharacter;

UCLASS()
class EVIDENCE_API AEquipment : public AAbilityActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEquipment();

	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WorldMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* LocalMesh;

	//Pickup
	void HandlePickup(AEvidencePlayerCharacter* Char);

	UFUNCTION(NetMulticast, Unreliable)
	virtual void MulticastPickup(AEvidencePlayerCharacter* Char);

	void Pickup(AEvidencePlayerCharacter* Char);

	bool bIsPickedUp = false;

	UPROPERTY(EditDefaultsOnly)
	FName EquipSocket;
	
};
