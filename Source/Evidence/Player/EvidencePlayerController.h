// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MoreMovementPlayerController.h"
#include "Evidence/Delegates.h"
#include "Evidence/Structs/SpectateeList.h"
#include "EvidencePlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class EVIDENCE_API AEvidencePlayerController : public AMoreMovementPlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void ClientSetIsSpectating(const bool bInIsSpectating);

	UFUNCTION(Client, Reliable)
	void ClientSetInputEnabled(const bool bEnabled);

	UFUNCTION(Client, Reliable)
	void ClientSetTerminalMenuVisibility(const bool bVisibility);

	UFUNCTION(Client, Reliable)
	void ClientSetLockerWidgetVisibility(const bool bVisibility);

	UFUNCTION(BlueprintCallable)
	void SetInteractWidgetVisibility(const bool bVisibility, const float Duration, const FString& DisplayString);

	UFUNCTION(BlueprintCallable)
	void SetInteractTimerState(const bool bState, const float Duration);

	FOnSetLockerWidgetVisibility OnSetLockerWidgetVisibility;
	FOnSpectatingChanged OnSpectatingChanged;
	FOnSpectateeChanged OnSpectateeChanged;
	FOnSetTerminalMenuVisibility OnSetTerminalMenuVisibility;
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

private:
	void OnCandidateSpectateesChanged(FSpectateeList& SpectateeList);

	UPROPERTY()
	FSpectateeList CandidateSpectatees;

	bool bIsSpectating;
	int32 SpectateIndex;

	void SpectateNext();
	void SpectatePrevious();
	void UpdateSpectatee();
};
