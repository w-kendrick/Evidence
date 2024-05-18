// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enums/RecordStatus.h"

class AEquipment;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingChanged, ERecordStatus);

DECLARE_MULTICAST_DELEGATE(FOnInventoryRequest);
DECLARE_MULTICAST_DELEGATE(FOnInventoryChanged);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEquippedChanged, AEquipment*, AEquipment*);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, uint8);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPowerChanged, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveChanged, bool);