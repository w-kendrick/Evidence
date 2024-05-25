// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera.h"
#include "PhotoCamera.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhotosChanged, const uint8);

class USceneCaptureComponent2D;

UCLASS()
class EVIDENCE_API APhotoCamera : public ACamera
{
	GENERATED_BODY()

public:
	APhotoCamera();

	FOnPhotosChanged OnPhotosChanged;

	void SaveFrame();

	void TakePhoto();

	void SetRemainingPhotos(const uint8 Remaining);
	uint8 GetRemainingPhotos() const { return RemainingPhotos; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(ReplicatedUsing = OnRep_RemainingPhotos)
	uint8 RemainingPhotos;

	UFUNCTION()
	void OnRep_RemainingPhotos();

	virtual uint8 GetFrameIndex() const override;

private:
	UPROPERTY()
	TArray<UTextureRenderTarget2D*> Photos;
	
};
