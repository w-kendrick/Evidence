// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Evidential.h"
#include "BloodStain.generated.h"

class UBoxComponent;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class EVIDENCE_API ABloodStain : public AActor, public IEvidential
{
	GENERATED_BODY()
	
public:	
	ABloodStain();

	virtual EEvidentialType GetType() const override;
	virtual float GetBaseWorth() const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionStimuliSourceComponent* Stimulus;

};
