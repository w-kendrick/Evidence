// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PhotoCamera.h"
#include "Evidence/Interfaces/PowerInterface.h"
#include "AutoCamera.generated.h"

UCLASS()
class EVIDENCE_API AAutoCamera : public APhotoCamera, public IPowerInterface
{
	GENERATED_BODY()

public:
	AAutoCamera();
	
	virtual UPowerComponent* GetPowerComponent() const override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UPowerComponent* PowerComponent;

	virtual void Activate() override;
	virtual void Deactivate() override;

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
