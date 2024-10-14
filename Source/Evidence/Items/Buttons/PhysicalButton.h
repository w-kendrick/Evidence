// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "PhysicalButton.generated.h"

UCLASS()
class EVIDENCE_API APhysicalButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	APhysicalButton();

	bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	FString GetInteractionString_Implementation() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FString DisplayString;

	void SetIsAvailable(const bool bNewValue);

	virtual void Interact() {};

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Mesh;

	bool bIsAvailable;
};
