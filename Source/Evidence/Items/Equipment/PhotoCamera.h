// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera.h"
#include "PhotoCamera.generated.h"

class USceneCaptureComponent2D;

UCLASS()
class EVIDENCE_API APhotoCamera : public ACamera
{
	GENERATED_BODY()

public:
	APhotoCamera();

	void SaveFrame();

	void TakePhoto();

protected:
	virtual uint8 GetFrameIndex() const override;

private:
	UPROPERTY()
	TArray<UTextureRenderTarget2D*> Photos;
	
};
