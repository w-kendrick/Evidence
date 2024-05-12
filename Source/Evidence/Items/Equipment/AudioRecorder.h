// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Delegates.h"
#include "AudioRecorder.generated.h"

UCLASS()
class EVIDENCE_API AAudioRecorder : public AEquipment
{
	GENERATED_BODY()

public:
	AAudioRecorder();

	FOnRecordingChanged OnRecordingChanged;
	
};
