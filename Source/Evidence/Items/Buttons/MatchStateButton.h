// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Buttons/PhysicalButton.h"
#include "MatchStateButton.generated.h"

UCLASS()
class EVIDENCE_API AMatchStateButton : public APhysicalButton
{
	GENERATED_BODY()
	
public:	
	AMatchStateButton();

protected:
	void BeginPlay() override;

	void OnMatchStateChanged(FName State);

	void Interact() override;

	FName MatchState;

	UFUNCTION(Server, Reliable)
	void ServerEndPreSetup();

	UFUNCTION(Server, Reliable)
	void ServerEndSetup();

	UFUNCTION(Server, Reliable)
	void ServerEndNight();
};
