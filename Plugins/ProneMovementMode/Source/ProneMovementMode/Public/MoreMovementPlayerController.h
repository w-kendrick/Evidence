// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MoreMovementPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRONEMOVEMENTMODE_API AMoreMovementPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

protected:
	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* P) override;

};
