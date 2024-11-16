// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Evidential.h"
#include "Evidence/Interfaces/Interactable.h"
#include "BloodStain.generated.h"

class UBoxComponent;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class EVIDENCE_API ABloodStain : public AActor, public IEvidential, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ABloodStain();

	bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const override;
	void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	FString GetInteractionString_Implementation() override;

	EEvidentialType GetType() const override;
	float GetBaseWorth() const override;

protected:
	void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionStimuliSourceComponent* Stimulus;

};
