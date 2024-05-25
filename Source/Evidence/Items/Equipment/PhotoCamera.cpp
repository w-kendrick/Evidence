// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotoCamera.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"

APhotoCamera::APhotoCamera()
{
	MaxCaptures = 10;
}

void APhotoCamera::SaveFrame()
{
	const TArray<FEvidentialInfo>& Captured = CaptureFrame();

	const FEvidentialCapture Capture = FEvidentialCapture(EEvidentialMedium::Photo, Captured);
	AddCapture(Capture);
}

void APhotoCamera::TakePhoto()
{
	UTextureRenderTarget2D* const Target = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 960, 540);
	SceneCaptureComponent->TextureTarget = Target;
	SceneCaptureComponent->CaptureScene();

	Photos.Add(Target);
}

uint8 APhotoCamera::GetFrameIndex() const
{
	return MaxCaptures - RemainingCaptures;
}
