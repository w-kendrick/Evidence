// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HubMapWidget.generated.h"

class AMovementSensor;
class ARadialSensor;
class ATrueTrackerDart;
class UImage;
class UCanvasPanel;
class ABaseCharacter;
class UMapPlayerWidget;

/**
 * 
 */
UCLASS()
class EVIDENCE_API UHubMapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(meta = (BindWidget))
	UImage* MapImage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMapPlayerWidget> PlayerWidgetClass;

private:
	static constexpr float PLAYER_WIDGET_UPDATE_DELAY = 1.0f;

	void OnPlayerUpdate();
	void OnMovementSensed(AMovementSensor* const Sensor);
	void OnRadiusSensed(ARadialSensor* const Sensor, const TArray<FVector>& Locations);
	void OnDartLocationReceived(ATrueTrackerDart* const Dart, const FVector& Location);

	FVector2D TopLeftCorner;
	FVector2D BottomRightCorner;

	FTimerHandle PlayerHandle;

	UPROPERTY()
	TArray<UMapPlayerWidget*> PlayerWidgets;

	void SetPosition(UMapPlayerWidget* const MapPlayerWidget, const FVector2D Position);
	UMapPlayerWidget* GetPlayerWidget(const ABaseCharacter* const Character) const;
	FVector2D WorldLocationToMap(const FVector& Location) const;
};
