// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Structs/EvidentialCapture.h"
#include "Camera.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhotosChanged, const uint8);

class USceneCaptureComponent2D;

UCLASS()
class EVIDENCE_API ACamera : public AEquipment
{
	GENERATED_BODY()

public:
	ACamera();

	FOnPhotosChanged OnPhotosChanged;

	void TakePhoto();
	void AwardCash();

	void SetRemainingPhotos(const uint8 Remaining);
	uint8 GetRemainingPhotos() const { return RemainingPhotos; }

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USceneCaptureComponent2D* SceneCaptureComponent;

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaxPhotos;

	UPROPERTY(ReplicatedUsing=OnRep_RemainingPhotos)
	uint8 RemainingPhotos;

	UFUNCTION()
	void OnRep_RemainingPhotos();

private:
	UPROPERTY()
	TArray<UTextureRenderTarget2D*> Photos;

	UPROPERTY(Replicated)
	TArray<FEvidentialCapture> Captures;
	
};
