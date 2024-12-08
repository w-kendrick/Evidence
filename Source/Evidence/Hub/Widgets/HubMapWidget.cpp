// Fill out your copyright notice in the Description page of Project Settings.


#include "HubMapWidget.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Evidence/Hub/Hub.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/BaseCharacter.h"
#include "MapPlayerWidget.h"
#include "Evidence/Libraries/EvidenceFunctionLibrary.h"
#include "Evidence/Game/MapInfoActor.h"

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
	
	GetWorld()->GetTimerManager().SetTimer(PlayerHandle, this, &ThisClass::OnPlayerUpdate, PLAYER_WIDGET_UPDATE_DELAY, true);
}

void UHubMapWidget::OnPlayerUpdate()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Actors);

	for (AActor* const Actor : Actors)
	{
		ABaseCharacter* const Character = Cast<ABaseCharacter>(Actor);

		UMapPlayerWidget* MapPlayerWidget = GetPlayerWidget(Character);

		if (!MapPlayerWidget)
		{
			MapPlayerWidget = CreateWidget<UMapPlayerWidget>(this, PlayerWidgetClass);
			MapPlayerWidget->SetCharacter(Character);
			Canvas->AddChild(MapPlayerWidget);

			PlayerWidgets.Add(MapPlayerWidget);
		}

		SetPosition(MapPlayerWidget, WorldLocationToMap(Character->GetActorLocation()));
	}
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

void UHubMapWidget::SetPosition(UMapPlayerWidget* const MapPlayerWidget, const FVector2D Position)
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(MapPlayerWidget);

	PanelSlot->SetPosition(Position);
}

UMapPlayerWidget* UHubMapWidget::GetPlayerWidget(const ABaseCharacter* const Character) const
{
	UMapPlayerWidget* Result = nullptr;

	for (UMapPlayerWidget* const PlayerWidget : PlayerWidgets)
	{
		if (PlayerWidget->GetCharacter() == Character)
		{
			Result = PlayerWidget;
		}
	}

	return Result;
}

FVector2D UHubMapWidget::WorldLocationToMap(const FVector& Location) const
{
	AMapInfoActor* const MapInfo = UEvidenceFunctionLibrary::GetMapInfo(GetWorld());

	checkf(MapInfo != nullptr, TEXT("Map doesn't have a AMapInfoActor present"))

	const float WorldLengthX = FMath::Abs(MapInfo->GetBottomRightPoint().X - MapInfo->GetTopLeftPoint().X);
	const float WorldLengthY = FMath::Abs(MapInfo->GetTopLeftPoint().Y - MapInfo->GetBottomRightPoint().Y);

	const float ScaledX = (Location.X - MapInfo->GetTopLeftPoint().X) / WorldLengthX;
	const float ScaledY = (Location.Y - MapInfo->GetBottomRightPoint().Y) / WorldLengthY;

	const float MapLengthX = FMath::Abs(BottomRightCorner.X - TopLeftCorner.X);
	const float MapLengthY = FMath::Abs(TopLeftCorner.Y - BottomRightCorner.Y);

	const float MapPosX = (MapLengthX * ScaledX) + TopLeftCorner.X;
	const float MapPosY = (MapLengthY * ScaledY) + BottomRightCorner.Y;

	return FVector2D(MapPosX, MapPosY);
}
