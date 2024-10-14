// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Items/Buttons/PhysicalButton.h"
#include "PreSetupButton.generated.h"

UCLASS()
class EVIDENCE_API APreSetupButton : public APhysicalButton
{
	GENERATED_BODY()
	
public:	
	APreSetupButton();

protected:
	void BeginPlay() override;

	void OnMatchStateChanged(FName State);

	void Interact() override;

	UFUNCTION(Server, Reliable)
	void ServerEndPreSetup();
};
