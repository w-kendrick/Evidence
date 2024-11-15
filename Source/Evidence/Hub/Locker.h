// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Structs/EquipmentList.h"
#include "Evidence/Hub/SingleUserInteractable.h"
#include "Locker.generated.h"

class AEquipment;
class UStaticMeshComponent;

UCLASS()
class EVIDENCE_API ALocker : public ASingleUserInteractable
{
	GENERATED_BODY()
	
public:
	ALocker();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetInteractionString_Implementation() override;

	void SetEquipmentAtIndex(AEquipment* const Equipment, const uint8 Index);
	AEquipment* GetEquipmentAtIndex(const uint8 Index) const;
	const FEquipmentList& GetStorage() const { return Storage; }

	static constexpr uint8 STORAGE_CAPACITY = 16U;

	FOnLockerStorageChanged OnLockerStorageChanged;

protected:
	void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	void OnInteract() override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Storage)
	FEquipmentList Storage;

	UFUNCTION()
	void OnRep_Storage();
};
