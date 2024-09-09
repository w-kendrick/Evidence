// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class AEquipment;
class ARadialSensor;
class AMovementSensor;
struct FEquipmentList;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemainingCapturesChanged, uint8)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingChanged, bool)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryChanged, FEquipmentList)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEquippedChanged, AEquipment*, AEquipment*)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEquippedIndexChanged, uint8, uint8)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, uint8)

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPowerChanged, float, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveChanged, bool)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCashChanged, float)

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRadialSense, ARadialSensor*, const TArray<FVector>)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovementSense, AMovementSensor*)

DECLARE_DELEGATE_ThreeParams(FOnSetInteractWidgetVisibility, bool, float, FString)
DECLARE_DELEGATE_OneParam(FOnSetTerminalMenuVisibility, bool)
DECLARE_DELEGATE_OneParam(FOnSetAttachmentWidgetVisibility, bool)

DECLARE_MULTICAST_DELEGATE(FOnAttachmentsUpdated)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float)