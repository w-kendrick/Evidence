// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "Evidence/Enums/AttachmentType.h"
#include "Evidence/Delegates.h"
#include "AbilitySet.h"
#include "Equipment.generated.h"

class ABaseCharacter;
class AEquipmentAttachment;

UCLASS()
class EVIDENCE_API AEquipment : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEquipment();

	FOnAttachmentsUpdated OnAttachmentsUpdated;

	void AddAttachment(AEquipmentAttachment* const Attachment, const EAttachmentType Type);
	void RemoveAttachment(const EAttachmentType Type);

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	virtual FString GetInteractionString_Implementation() override;

	void Pickup(ABaseCharacter* Char);
	void Drop();

	FORCEINLINE USkeletalMeshComponent* GetWorldMesh() const { return WorldMesh; }
	FORCEINLINE FString GetEquipmentName() const { return EquipmentName; }
	FORCEINLINE const TMap<EAttachmentType, AEquipmentAttachment*>& GetAttachments() const { return Attachments; };

	AEquipmentAttachment* GetAttachment(const EAttachmentType Type) const;

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

	UPROPERTY()
	TMap<EAttachmentType, AEquipmentAttachment*> Attachments;

	void Attach(ABaseCharacter* Char, const bool isVisible);
	void Detach();

private:
	void FindGround(FVector& Location, FRotator& Rotation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float MaxGroundDistance = 10000.f;

	void AddAbilities(ABaseCharacter* Char);
	void RemoveAbilities(ABaseCharacter* Char);
	
};
