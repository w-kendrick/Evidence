// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Evidence/Interfaces/Interactable.h"
#include "AttachmentBench.generated.h"

UCLASS()
class EVIDENCE_API AAttachmentBench : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AAttachmentBench();

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractionComponent) const override;
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractionComponent) override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Bench;
};
