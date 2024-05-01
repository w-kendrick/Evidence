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
	UTextureRenderTarget2D* Target = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 1920, 1080);
	SceneCaptureComponent->TextureTarget = Target;
	SceneCaptureComponent->CaptureScene();

	Photos[Photos.Num() - RemainingPhotos] = Target;

	SetRemainingPhotos(RemainingPhotos - 1);
}

void ACamera::SetRemainingPhotos(const uint8 Remaining)
{
	RemainingPhotos = Remaining;
	OnPhotosChanged.Broadcast(RemainingPhotos);
}

void ACamera::OnRep_RemainingPhotos()
{
	OnPhotosChanged.Broadcast(RemainingPhotos);
}
