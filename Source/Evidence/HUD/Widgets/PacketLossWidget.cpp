// Fill out your copyright notice in the Description page of Project Settings.

#include "PacketLossWidget.h"
#include "Components/TextBlock.h"

void UPacketLossWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyNetConnection = GetOwningPlayer()->GetNetConnection();
	if (!MyNetConnection)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPacketLossWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (MyNetConnection)
	{
		const int32 InLoss = MyNetConnection->InPacketsLost;
		const int32 OutLoss = MyNetConnection->OutPacketsLost;

		const int32 AvgLoss = (InLoss + OutLoss) / 2;

		LossText->SetText(FText::FromString(FString(TEXT("Pkt Loss: ")) + FString::FromInt(AvgLoss) + FString(TEXT("%"))));
	}
}
