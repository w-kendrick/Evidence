// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Enums/EvidentialType.h"
#include "AudioSource.generated.h"

UCLASS()
class EVIDENCE_API AAudioSource : public AActor
{
	GENERATED_BODY()
	
public:	
	AAudioSource();

	void SetLifetime(const float NewLifetime);
	EEvidentialType GetType() const { return Type; }
	float GetAudibleRange() const { return AudibleRange; }

protected:
	UPROPERTY(EditDefaultsOnly)
	EEvidentialType Type;

	UPROPERTY(EditDefaultsOnly)
	float Lifetime;

	UPROPERTY(EditDefaultsOnly)
	float AudibleRange;

private:
	void EndLife();

	FTimerHandle LifeHandle;
};
