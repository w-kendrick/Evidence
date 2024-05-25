// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvidenceCaptureEquipment.h"
#include "Evidence/Delegates.h"
#include "AudioRecorder.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Hearing;
struct FEvidentialInfo;
struct FEvidentialCapture;

UCLASS()
class EVIDENCE_API AAudioRecorder : public AEvidenceCaptureEquipment
{
	GENERATED_BODY()

public:
	AAudioRecorder();

	FOnRecordingChanged OnRecordingChanged;

	void StartRecording();
	void StopRecording();

	bool GetIsRecording() const { return isRecording; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void OnRecordingEnd();
	void SetIsRecording(const bool NewIsRecording);

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Hearing* Hearing;

	UFUNCTION()
	void OnSense(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditDefaultsOnly)
	float MaxLength;

	UPROPERTY(ReplicatedUsing = OnRep_IsRecording)
	bool isRecording;

	UFUNCTION()
	void OnRep_IsRecording(const bool PrevIsRecording);

	UPROPERTY()
	TArray<FEvidentialInfo> Recording;

private:
	FTimerHandle RecordHandle;

	uint8 Count;

};
