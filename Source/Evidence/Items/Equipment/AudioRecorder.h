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

	void StartRecording();
	void StopRecording();

	ERecordStatus GetRecordStatus() const { return RecordStatus; }

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

private:
	FTimerHandle RecordHandle;

};
