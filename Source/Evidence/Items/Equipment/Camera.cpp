// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Evidence/Interfaces/Evidential.h"
#include "Evidence/Structs/EvidentialInfo.h"

ACamera::ACamera()
{
	MaxPhotos = 10;

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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString("Take photo: ") + FString::FromInt(Photos.Num() - (RemainingPhotos + 1)));

	UTextureRenderTarget2D* Target = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 960, 540);
	SceneCaptureComponent->TextureTarget = Target;
	SceneCaptureComponent->CaptureScene();

	Photos[Photos.Num() - (RemainingPhotos + 1)] = Target;
}

void ACamera::AwardCash()
{
	TArray<FHitResult> Hits;
	const FVector Loc = SceneCaptureComponent->GetComponentLocation();
	const FQuat Rot = SceneCaptureComponent->GetComponentQuat();
	const FCollisionShape Shape = FCollisionShape::MakeBox(FVector3f(1, 2, 3));

	TArray<FEvidentialInfo> CapturedEvidentials;

	if (GetWorld()->SweepMultiByChannel(Hits, Loc, Loc, Rot, ECollisionChannel::ECC_Visibility, Shape))
	{
		for (const FHitResult Hit : Hits)
		{
			IEvidential* const Evidential = Cast<IEvidential>(Hit.GetActor());
			if (Evidential)
			{
				FEvidentialInfo Info = FEvidentialInfo(Evidential->GetType(), EEvidentialMedium::Photo, Evidential->GetBaseWorth());
				CapturedEvidentials.Add(Info);
			}
		}
	}
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
