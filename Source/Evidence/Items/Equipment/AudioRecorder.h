// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Delegates.h"
#include "AudioRecorder.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Hearing;

UCLASS()
class EVIDENCE_API AAudioRecorder : public AEquipment
{
	GENERATED_BODY()

public:
	AAudioRecorder();

	FOnRecordingChanged OnRecordingChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Hearing* Hearing;

	UFUNCTION()
	void OnSense(AActor* Actor, FAIStimulus Stimulus);

};
