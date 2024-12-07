// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HubMapWidget.generated.h"

class AMovementSensor;
class ARadialSensor;
class ATrueTrackerDart;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UHubMapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

private:
	void OnMovementSensed(AMovementSensor* const Sensor);
	void OnRadiusSensed(ARadialSensor* const Sensor, const TArray<FVector>& Locations);
	void OnDartLocationReceived(ATrueTrackerDart* const Dart, const FVector& Location);
	
};
