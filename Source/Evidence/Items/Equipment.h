// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "Evidence/Enums/AttachmentType.h"
#include "Equipment.generated.h"

class AEvidenceCharacter;
class UEIGameplayAbility;
class AEquipmentAttachment;

UCLASS()
class EVIDENCE_API AEquipment : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AEquipment();

	void AddAttachment(AEquipmentAttachment* const Attachment, const EAttachmentType Type);
	void RemoveAttachment(const EAttachmentType Type);
	FGameplayAbilitySpecHandle AddAttachmentAbility(const TSubclassOf<UEIGameplayAbility>& Ability);
	void RemoveAttachmentAbility(const FGameplayAbilitySpecHandle& Handle, const TSubclassOf<UEIGameplayAbility>& Ability);

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;

	void Pickup(AEvidenceCharacter* Char);
	void Drop();

	void Attach(AEvidenceCharacter* Char, const bool isVisible);

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

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UEIGameplayAbility>> Abilities;

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;

	UPROPERTY(EditDefaultsOnly)
	FString EquipmentName;

	UPROPERTY()
	TMap<EAttachmentType, AEquipmentAttachment*> Attachments;

private:
	void FindGround(FVector& Location, FRotator& Rotation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float MaxGroundDistance = 10000.f;

	void AddAbilities(AEvidenceCharacter* Char);
	void RemoveAbilities(AEvidenceCharacter* Char);
	
};
