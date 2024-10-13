// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "PreSetupButton.generated.h"

UCLASS()
class EVIDENCE_API APreSetupButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	APreSetupButton();

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	virtual FString GetInteractionString_Implementation() override;

protected:
	void BeginPlay() override;

	void OnMatchStateChanged(FName State);

	UFUNCTION(Server, Reliable)
	void ServerEndPreSetup();

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Mesh;

	bool bIsAvailable;
};
