// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"

ACamera::ACamera()
{
	MaxPhotos = 10;

	Photos.SetNum(MaxPhotos);
	for (int i = 0; i < MaxPhotos; i++)
	{
		Photos.Add(nullptr);
	}

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(LocalMesh);
}

void ACamera::BeginPlay()
{
	Super::BeginPlay();

	SetRemainingPhotos(MaxPhotos);
}

void ACamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACamera, RemainingPhotos);
}

void ACamera::TakePhoto()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Take photo");

	UTextureRenderTarget2D* Target = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 960, 540);
	SceneCaptureComponent->TextureTarget = Target;
	SceneCaptureComponent->CaptureScene();

	Photos[Photos.Num() - RemainingPhotos] = Target;
}

void ACamera::SetRemainingPhotos(const uint8 Remaining)
{
	RemainingPhotos = Remaining;
	OnPhotosChanged.Broadcast(RemainingPhotos);
}

void ACamera::OnRep_RemainingPhotos()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Remaining: ") + FString::FromInt(RemainingPhotos));
	OnPhotosChanged.Broadcast(RemainingPhotos);

	for (int i = 0; i < RemainingPhotos; i++)
	{
		Photos[Photos.Num() - (i + 1)] = nullptr;
	}
}
