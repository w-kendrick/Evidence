// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Structs/EquipmentList.h"
#include "Evidence/Interfaces/Interactable.h"
#include "Locker.generated.h"

class AEquipment;
class UStaticMeshComponent;

UCLASS()
class EVIDENCE_API ALocker : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	ALocker();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	FString GetInteractionString_Implementation() override;

	void SetLockerStorage(AEquipment* const Equipment, const uint8 Index);
	const FEquipmentList& GetStorage() const { return Storage; }

	static constexpr uint8 STORAGE_CAPACITY = 16U;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Storage)
	FEquipmentList Storage;

	UFUNCTION()
	void OnRep_Storage();
};
