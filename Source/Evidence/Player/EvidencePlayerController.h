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
	UFUNCTION(Client, Reliable)
	void ClientSetTerminalMenuVisibility(const bool bVisibility);

	UFUNCTION(Client, Reliable)
	void ClientSetAttachmentWidgetVisibility(const bool bVisibility);

	UFUNCTION(BlueprintCallable)
	void SetInteractWidgetVisibility(const bool bVisibility, const float Duration, const FString& DisplayString);

	UFUNCTION(BlueprintCallable)
	void SetInteractTimerState(const bool bState, const float Duration);

	FOnSetTerminalMenuVisibility OnSetTerminalMenuVisibility;
	FOnSetAttachmentWidgetVisibility OnSetAttachmentWidgetVisibility;
	FOnSetInteractWidgetVisibility OnSetInteractWidgetVisibility;
	FOnInteractTimerStateChanged OnInteractTimerStateChanged;
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
