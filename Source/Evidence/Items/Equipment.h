// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/AbilityActor.h"
#include "Interactable.h"
#include "Equipment.generated.h"

class AEvidenceCharacter;

UCLASS()
class EVIDENCE_API AEquipment : public AAbilityActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEquipment();

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;

	void Pickup(AEvidenceCharacter* Char);
	void Drop();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* WorldMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* LocalMesh;

	bool bIsPickedUp = false;

	UPROPERTY(EditDefaultsOnly)
	FName EquipSocket;

private:
	void FindGround(FVector& Location, FRotator& Rotation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float MaxGroundDistance = 10000.f;
	
};
