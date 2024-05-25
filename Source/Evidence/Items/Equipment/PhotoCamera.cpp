// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotoCamera.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"

APhotoCamera::APhotoCamera()
{
	MaxPhotos = 10;

	for (int i = 0; i < MaxPhotos; i++)
	{
		Photos.Add(nullptr);
	}
}

void APhotoCamera::BeginPlay()
{
	Super::BeginPlay();

	SetRemainingPhotos(MaxPhotos);
}

void APhotoCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APhotoCamera, RemainingPhotos);
}

void APhotoCamera::TakePhoto()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString("Take photo: ") + FString::FromInt(Photos.Num() - (RemainingPhotos + 1)));

	UTextureRenderTarget2D* const Target = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 960, 540);
	SceneCaptureComponent->TextureTarget = Target;
	SceneCaptureComponent->CaptureScene();

	Photos[Photos.Num() - (RemainingPhotos + 1)] = Target;
}

void APhotoCamera::SetRemainingPhotos(const uint8 Remaining)
{
	RemainingPhotos = Remaining;
	OnPhotosChanged.Broadcast(RemainingPhotos);
}

void APhotoCamera::OnRep_RemainingPhotos()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Remaining: ") + FString::FromInt(RemainingPhotos));
	OnPhotosChanged.Broadcast(RemainingPhotos);

	for (int i = 0; i < RemainingPhotos; i++)
	{
		Photos[Photos.Num() - (i + 1)] = nullptr;
	}
}

uint8 APhotoCamera::GetFrameIndex() const
{
	return Photos.Num() - (RemainingPhotos + 1);
}
