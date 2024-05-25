// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvidenceCaptureEquipment.h"
#include "Evidence/Structs/EvidentialCapture.h"
#include "Camera.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class EVIDENCE_API ACamera : public AEvidenceCaptureEquipment
{
	GENERATED_BODY()

public:
	ACamera();

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USceneCaptureComponent2D* SceneCaptureComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Sight* Sight;

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	virtual uint8 GetFrameIndex() const;

	TArray<FEvidentialInfo> CaptureFrame();

};
