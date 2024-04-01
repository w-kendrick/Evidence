// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Rifle.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, uint8);

UCLASS()
class EVIDENCE_API ARifle : public AEquipment
{
	GENERATED_BODY()

public:
	ARifle();

	FOnAmmoChanged OnAmmoChanged;

	void SetCurrentClip(const uint8 NewClip);

	FORCEINLINE uint8 GetCurrentClip() const { return CurrentClip; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaxClipSize;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentClip)
	uint8 CurrentClip;

	UFUNCTION()
	void OnRep_CurrentClip(const uint8 OldClip);
	
};
