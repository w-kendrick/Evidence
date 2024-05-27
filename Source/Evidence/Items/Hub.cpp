// Fill out your copyright notice in the Description page of Project Settings.


#include "Hub.h"
#include "Net/UnrealNetwork.h"
#include "Evidence/Evidence.h"
#include "Equipment/Sensors/MovementSensor.h"
#include "Equipment/RadialSensor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Equipment/Projectiles/TrueTrackerDart.h"
#include "Components/BoxComponent.h"
#include "Evidence/Items/Equipment/EvidenceCaptureEquipment.h"
#include "Evidence/Libraries/EvidentialFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/EvidenceGameState.h"
#include "Components/SphereComponent.h"
#include "Evidence/Character/EvidencePlayerCharacter.h"
#include "Evidence/EvidencePlayerController.h"

AHub::AHub()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Bounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));
	Bounds->SetupAttachment(RootComponent);
	Bounds->InitBoxExtent(FVector(200.f, 100.f, 100.f));
	Bounds->SetVisibility(true);
	Bounds->SetHiddenInGame(false);

	PurchaseSpawn = CreateDefaultSubobject<USphereComponent>(TEXT("PurchaseSpawn"));
	PurchaseSpawn->SetupAttachment(RootComponent);
	PurchaseSpawn->SetVisibility(false);
	PurchaseSpawn->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	Terminal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Terminal"));
	Terminal->SetupAttachment(RootComponent);
	Terminal->SetCollisionResponseToChannel(COLLISION_INTERACTABLE, ECollisionResponse::ECR_Overlap);
}

void AHub::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AEvidenceGameState>(UGameplayStatics::GetGameState(GetWorld()));

	if (HasAuthority())
	{
		CreateInitialSpawns();

		Bounds->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
		Bounds->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &ThisClass::CalculateStoredCash, 10.f, true);
	}
}

void AHub::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHub, Interactor);
}

bool AHub::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const
{
	return !Interactor;
}

void AHub::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent)
{
	if (HasAuthority())
	{
		AEvidencePlayerCharacter* const Char = Cast<AEvidencePlayerCharacter>(InteractingActor);
		if (Char)
		{
			Interactor = Char;

			AEvidencePlayerController* const EPC = Cast<AEvidencePlayerController>(Interactor->GetController());
			if (EPC)
			{
				SetOwner(InteractingActor);
				EPC->ClientShowTerminalMenu();
			}
		}
	}
}

void AHub::RelinquishTerminal()
{
	ServerRelinquishTerminal();
}

void AHub::ServerRelinquishTerminal_Implementation()
{
	Interactor = nullptr;
	SetOwner(nullptr);
}

void AHub::CreateInitialSpawns()
{
	for (const FSpawnInfo& SpawnInfo : InitialSpawns)
	{
		SpawnEquipment(SpawnInfo);
	}
}

void AHub::SpawnEquipment(const FSpawnInfo& SpawnInfo)
{
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	if (UKismetMathLibrary::ClassIsChildOf(Class, AMovementSensor::StaticClass()))
	{
		SpawnMovementSensor(SpawnInfo);
	}
	if (UKismetMathLibrary::ClassIsChildOf(Class, ARadialSensor::StaticClass()))
	{
		SpawnRadialSensor(SpawnInfo);
	}
}

void AHub::SpawnMovementSensor(const FSpawnInfo& SpawnInfo)
{
	const FTransform& Transform = SpawnInfo.Transform;
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	AMovementSensor* const MovementSensor = Cast<AMovementSensor>(GetWorld()->SpawnActor<AEquipment>(Class, Transform));
	MovementSensor->OnMovementSense.AddUObject(this, &ThisClass::OnMovementSensed);
}

void AHub::SpawnRadialSensor(const FSpawnInfo& SpawnInfo)
{
	const FTransform& Transform = SpawnInfo.Transform;
	const TSubclassOf<AEquipment>& Class = SpawnInfo.Class;

	ARadialSensor* const RadialSensor = Cast<ARadialSensor>(GetWorld()->SpawnActor<AEquipment>(Class, Transform));
	RadialSensor->OnRadialSense.AddUObject(this, &ThisClass::OnRadiusSensed);
}

void AHub::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEvidenceCaptureEquipment* const Device = Cast<AEvidenceCaptureEquipment>(OtherActor);
	if (Device)
	{
		CaptureDevices.Add(Device);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Add device");
	}
}

void AHub::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEvidenceCaptureEquipment* const Device = Cast<AEvidenceCaptureEquipment>(OtherActor);
	if (Device)
	{
		CaptureDevices.Remove(Device);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Remove device");
	}
}

void AHub::CalculateStoredCash()
{
	TArray<FEvidentialCapture> Captures;

	for (const AEvidenceCaptureEquipment* const Device : CaptureDevices)
	{
		const TArray<FEvidentialCapture>& DeviceCaptures = Device->GetCaptures();
		
		for (const FEvidentialCapture& Capture : DeviceCaptures)
		{
			Captures.Add(Capture);
		}
	}

	float Cash = UEvidentialFunctionLibrary::CalculateCash(Captures);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString(TEXT("Awarded: $")) + FString::SanitizeFloat(Cash));
}

FTransform AHub::MakePurchaseSpawnTransform() const
{
	FTransform T;
	T.SetLocation(PurchaseSpawn->GetComponentLocation());
	T.SetRotation(PurchaseSpawn->GetComponentQuat());
	T.SetScale3D(FVector::OneVector);
	return T;
}

void AHub::ServerPurchaseEquipment_Implementation(const FShopItem& Item)
{
	if (GameState)
	{
		if (GameState->SpendCash(Item.Price))
		{
			const TSubclassOf<AEquipment>& Class = Item.Class;

			const FSpawnInfo SpawnInfo = FSpawnInfo(Class, MakePurchaseSpawnTransform());
			SpawnEquipment(SpawnInfo);
		}
	}
}

void AHub::SubscribeToTrackerDart(ATrueTrackerDart* Dart)
{
	Dart->OnTrackDartBroadcast.AddUObject(this, &ThisClass::OnDartLocationReceived);
}

void AHub::OnMovementSensed(AMovementSensor* const Sensor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Movement sensed");
}

void AHub::OnRadiusSensed(ARadialSensor* const Sensor, const TArray<FVector> Locations)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Radius sensed");
}

void AHub::OnDartLocationReceived(ATrueTrackerDart* const Dart, const FVector& Location)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Tracker dart location received");
}
