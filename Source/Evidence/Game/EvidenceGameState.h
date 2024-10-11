// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Evidence/Delegates.h"
#include "EvidenceGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, FName)

class AHub;

UCLASS()
class EVIDENCE_API AEvidenceGameState : public AGameState
{
	GENERATED_BODY()

public:
	AEvidenceGameState();
	virtual void OnRep_MatchState() override;

	FOnMatchStateChanged OnMatchStateChanged;

	AHub* GetHub();

	FOnCashChanged OnCashChanged;

	float GetCash() const { return Cash; }
	void AwardCash(const float Amount);
	bool SpendCash(const float Amount);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	AHub* Hub;

	UPROPERTY(ReplicatedUsing=OnRep_Cash)
	float Cash = 100.f;

	UFUNCTION()
	void OnRep_Cash(float PrevCash);
	
};
