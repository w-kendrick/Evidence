// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Structs/SpawnInfo.h"
#include "Evidence/Structs/ShopItem.h"
#include "Evidence/Hub/SingleUserInteractable.h"
#include "Hub.generated.h"

class AEquipment;
class AMovementSensor;
class ARadialSensor;
class ATrueTrackerDart;
class UBoxComponent;
class AEvidenceCaptureEquipment;
class AEvidenceGameState;
class USphereComponent;
class UStaticMeshComponent;
class ABaseCharacter;
	
UCLASS()
class EVIDENCE_API AHub : public ASingleUserInteractable
{
	GENERATED_BODY()
	
public:	
	AHub();

	void ConsumeCaptures();

	FString GetInteractionString_Implementation() override;

	UFUNCTION(Server, Reliable)
	void ServerPurchaseEquipment(const FShopItem& Item);
	void SubscribeToTrackerDart(ATrueTrackerDart* Dart);

	FORCEINLINE TArray<FShopItem> GetShopItems() const { return ShopItems; }
	FORCEINLINE const TArray<AEvidenceCaptureEquipment*>& GetCaptureDevices() const { return CaptureDevices; }

protected:
	void BeginPlay() override;
	void OnInteract() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FSpawnInfo> InitialSpawns;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* Bounds;

	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* PurchaseSpawn;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Terminal;

	void OnMovementSensed(AMovementSensor* const Sensor);
	void OnRadiusSensed(ARadialSensor* const Sensor, const TArray<FVector> Locations);
	void OnDartLocationReceived(ATrueTrackerDart* const Dart, const FVector& Location);

	UPROPERTY(EditDefaultsOnly)
	TArray<FShopItem> ShopItems;

private:
	void CreateInitialSpawns();
	void SpawnEquipment(const FSpawnInfo& SpawnInfo);
	void SpawnMovementSensor(const FSpawnInfo& SpawnInfo);
	void SpawnRadialSensor(const FSpawnInfo& SpawnInfo);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	TArray<AEvidenceCaptureEquipment*> CaptureDevices;

	float CalculateStoredCash() const;

	UPROPERTY()
	AEvidenceGameState* GameState;

	FTransform MakePurchaseSpawnTransform() const;
};
