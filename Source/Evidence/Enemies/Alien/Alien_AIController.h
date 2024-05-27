// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Alien_AIController.generated.h"

UCLASS()
class EVIDENCE_API AAlien_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AAlien_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;


};
