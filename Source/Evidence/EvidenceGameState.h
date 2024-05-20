// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Delegates.h"
#include "EvidenceGameState.generated.h"

class AHub;

UCLASS()
class EVIDENCE_API AEvidenceGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AHub* GetHub();

	float GetCash() const { return Cash; }
	void AwardCash(const float Amount);
	bool SpendCash(const float Amount);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	AHub* Hub;

	UPROPERTY(ReplicatedUsing=OnRep_Cash)
	float Cash;

	UFUNCTION()
	void OnRep_Cash(float PrevCash);

	FOnCashChanged OnCashChanged;
	
};
