// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment.h"
#include "Evidence/Structs/EvidentialCapture.h"
#include "Camera.generated.h"

UCLASS()
class EVIDENCE_API ACamera : public AEquipment
{
	GENERATED_BODY()

public:
	ACamera();

	void SaveFrame();

protected:
	UPROPERTY(VisibleDefaultsOnly)
	USceneCaptureComponent2D* SceneCaptureComponent;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(Replicated)
	TArray<FEvidentialCapture> Captures;
	
};
