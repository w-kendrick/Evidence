// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MoreMovementPlayerController.h"
#include "Evidence/Delegates.h"
#include "EvidencePlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class EVIDENCE_API AEvidencePlayerController : public AMoreMovementPlayerController
{
	GENERATED_BODY()

public:
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

	UFUNCTION(Client, Reliable)
	void ClientSetTerminalMenuVisibility(const bool bVisibility);

	UFUNCTION(Client, Reliable)
	void ClientSetAttachmentWidgetVisibility(const bool bVisibility);

	FOnSetTerminalMenuVisibility OnSetTerminalMenuVisibility;
	FOnSetAttachmentWidgetVisibility OnSetAttachmentWidgetVisibility;
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
