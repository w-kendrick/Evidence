// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera.h"
#include "VideoCamera.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordingChanged, bool);

UCLASS()
class EVIDENCE_API AVideoCamera : public ACamera
{
	GENERATED_BODY()

public:
	AVideoCamera();

	FOnRecordingChanged OnRecordingChanged;

	void StartRecording();
	void StopRecording();

	bool GetIsRecording() const { return isRecording; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	void SetIsRecording(const bool new_isRecording);

	UPROPERTY(EditDefaultsOnly)
	uint8 FPS;

	UPROPERTY(EditDefaultsOnly)
	float MaxVideoLength;

	UPROPERTY(ReplicatedUsing = OnRep_isRecording)
	bool isRecording;

	UFUNCTION()
	void OnRep_IsRecording(const bool prev_isRecording);
	
};
