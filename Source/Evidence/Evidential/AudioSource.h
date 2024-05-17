// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Evidential.h"
#include "AudioSource.generated.h"

UCLASS()
class EVIDENCE_API AAudioSource : public AActor, public IEvidential
{
	GENERATED_BODY()
	
public:
	AAudioSource();

	virtual EEvidentialType GetType() const override;
	virtual float GetBaseWorth() const override;

protected:
	virtual void BeginPlay() override;

private:
	void PlayAudio();

};
