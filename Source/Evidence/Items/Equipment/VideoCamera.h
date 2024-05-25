// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera.h"
#include "Evidence/Enums/RecordStatus.h"
#include "Evidence/Delegates.h"
#include "VideoCamera.generated.h"

UCLASS()
class EVIDENCE_API AVideoCamera : public ACamera
{
	GENERATED_BODY()

public:
	AVideoCamera();

	FOnRecordingChanged OnRecordingChanged;

	void StartRecording();
	void StopRecording();

	ERecordStatus GetRecordStatus() const { return RecordStatus; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	void SetRecordStatus(const ERecordStatus NewStatus);

	UPROPERTY(EditDefaultsOnly)
	uint8 FPS;

	UPROPERTY(EditDefaultsOnly)
	float MaxVideoLength;

	UPROPERTY(ReplicatedUsing = OnRep_RecordStatus)
	ERecordStatus RecordStatus;

	UFUNCTION()
	void OnRep_RecordStatus(const ERecordStatus PrevStatus);

	virtual uint8 GetFrameIndex() const override;

private:
	void FrameCheck();

	uint8 FrameCount;
	FTimerHandle RecordHandle;

	UPROPERTY()
	TArray<FEvidentialInfo> CurrentCaptures;

	void AddToCurrentCaptures(const TArray<FEvidentialInfo>& New);
	
};
