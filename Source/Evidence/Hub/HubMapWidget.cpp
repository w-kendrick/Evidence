// Fill out your copyright notice in the Description page of Project Settings.


#include "HubMapWidget.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Evidence/Hub/Hub.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UHubMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AHub* const Hub = UEvidenceFunctionLibrary::GetHub(GetWorld());
	if (Hub)
	{
		Hub->OnMovementSense.AddUObject(this, &ThisClass::OnMovementSensed);
		Hub->OnRadialSense.AddUObject(this, &ThisClass::OnRadiusSensed);
		Hub->OnTrackDartBroadcast.AddUObject(this, &ThisClass::OnDartLocationReceived);
	}

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(MapImage);
	const FVector2D Origin = PanelSlot->GetPosition();

	TopLeftCorner = Origin + FVector2D(-PanelSlot->GetSize().X, PanelSlot->GetSize().Y);
	BottomRightCorner = Origin + FVector2D(PanelSlot->GetSize().X, -PanelSlot->GetSize().Y);
}

void UHubMapWidget::OnMovementSensed(AMovementSensor* const Sensor)
{
}

void UHubMapWidget::OnRadiusSensed(ARadialSensor* const Sensor, const TArray<FVector>& Locations)
{
}

void UHubMapWidget::OnDartLocationReceived(ATrueTrackerDart* const Dart, const FVector& Location)
{
}
