// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Equipment/PlantableEquipment.h"
#include "GameplayEffectTypes.h"
#include "Claymore.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class EVIDENCE_API AClaymore : public APlantableEquipment
{
	GENERATED_BODY()

public:
	AClaymore();

	FGameplayEffectSpecHandle DamageEffectHandle;

	bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const override;

	void Plant() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY()
	UAISenseConfig_Sight* Sight;

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void Detonate();

private:
	float CalculateDamage(const FVector Location) const;
	
};
