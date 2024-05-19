// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Delegates.h"
#include "Evidence/Interfaces/CaptureDevice.h"
#include "AudioRecorder.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Hearing;
struct FEvidentialInfo;
struct FEvidentialCapture;

UCLASS()
class EVIDENCE_API AAudioRecorder : public AEquipment, public ICaptureDevice
{
	GENERATED_BODY()

public:
	AAudioRecorder();

	FOnRecordingChanged OnRecordingChanged;

	void StartRecording();
	void StopRecording();

	ERecordStatus GetRecordStatus() const { return RecordStatus; }

	virtual TArray<FEvidentialCapture> GetCaptures() const override;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void OnRecordingEnd();
	void SetRecordStatus(const ERecordStatus NewStatus);

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Hearing* Hearing;

	UFUNCTION()
	void OnSense(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly)
	float MaxLength;

	UPROPERTY(ReplicatedUsing = OnRep_RecordStatus)
	ERecordStatus RecordStatus;

	UFUNCTION()
	void OnRep_RecordStatus(const ERecordStatus PrevStatus);

	UPROPERTY()
	TArray<FEvidentialInfo> Recording;

	UPROPERTY()
	TArray<FEvidentialCapture> Captures;

private:
	FTimerHandle RecordHandle;

};
