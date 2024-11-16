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

	bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const override;
	void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;
	float GetInteractionDuration_Implementation(UPrimitiveComponent* InteractionComponent) const;
	FString GetInteractionString_Implementation() override;

protected:
	void SetIsAvailable(const bool bNewValue);
	void SetInteractString(const FString& NewString);
	void SetInteractDuration(const float NewDuration);

	virtual void Interact() {};

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Mesh;

	FString InteractString;
	float InteractDuration;

	bool bIsAvailable;
};
