// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PhotoCamera.h"
#include "AutoCamera.generated.h"

UCLASS()
class EVIDENCE_API AAutoCamera : public APhotoCamera
{
	GENERATED_BODY()

public:
	AAutoCamera();

	void StartSensing();
	void StopSensing();

protected:
	void Sense();

	FTimerHandle SenseHandle;

	UPROPERTY()
	TArray<FVector> PreviousSense;

	UPROPERTY(EditDefaultsOnly)
	float SenseDelay;

	UPROPERTY(EditDefaultsOnly)
	float SenseRadius;

private:
	float GetAngleBetweenVectors(const FVector& Vec1, const FVector& Vec2) const;
	bool doArraysMatch(const TArray<FVector>& Arr1, const TArray<FVector>& Arr2) const;

	void MovementSensed();

};
