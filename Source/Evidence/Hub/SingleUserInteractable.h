// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "SingleUserInteractable.generated.h"

class ABaseCharacter;

UCLASS()
class EVIDENCE_API ASingleUserInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ASingleUserInteractable();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent, AActor* InteractingActor) const override;
	void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;

	void Relinquish();

protected:
	UPROPERTY(Replicated)
	ABaseCharacter* Interactor;

	virtual void OnInteract();

	UFUNCTION(Server, Reliable)
	void ServerRelinquish();

};
