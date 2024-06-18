// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Evidence/Delegates.h"
#include "EvidencePlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class EVIDENCE_API AEvidencePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ShowInteractPrompt(const float Duration);
	void HideInteractPrompt();
	void StartInteractionTimer(const float Duration);
	void StopInteractionTimer();

	UFUNCTION(Client, Reliable)
	void ClientShowTerminalMenu();
	UFUNCTION(Client, Reliable)
	void ClientHideTerminalMenu();

	UFUNCTION(Client, Reliable)
	void ClientSetAttachmentWidgetVisibility(const bool bVisibility);

	FOnSetAttachmentWidgetVisibility OnSetAttachmentWidgetVisibility;
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* P) override;

	// End Actor interface
};
