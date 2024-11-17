// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Structs/EvidentialCapture.h"
#include "Evidence/Delegates.h"
#include "EvidenceCaptureEquipment.generated.h"

UCLASS()
class EVIDENCE_API AEvidenceCaptureEquipment : public AEquipment
{
	GENERATED_BODY()

public:
	AEvidenceCaptureEquipment();

	FOnRemainingCapturesChanged OnRemainingCapturesChanged;

	virtual void Clear();
	TArray<FEvidentialCapture> GetCaptures() const;
	bool hasCapturesRemaining() const;

protected:
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY()
	TArray<FEvidentialCapture> Captures;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaxCaptures;

	UPROPERTY(ReplicatedUsing = OnRep_RemainingCaptures, SaveGame)
	uint8 RemainingCaptures;

	UFUNCTION()
	void OnRep_RemainingCaptures(const uint8 PrevRemaining);

	void AddCapture(const FEvidentialCapture& Capture);
	
};
