// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilityActor.generated.h"

UCLASS()
class EVIDENCE_API AAbilityActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AAbilityActor();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

};
