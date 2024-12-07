// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Evidence/Delegates.h"
#include "Evidence/Structs/SpectateeList.h"
#include "EvidenceGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, FName)

class AHub;
class ABaseCharacter;

UCLASS()
class EVIDENCE_API AEvidenceGameState : public AGameState
{
	GENERATED_BODY()

public:
	AEvidenceGameState();
	void Tick(float DeltaTime) override;
	void SetMatchState(const FName& State);
	virtual void OnRep_MatchState() override;

	void SetSetupCountdownLength(const float InCountdownLength);

	FOnMatchStateChanged OnMatchStateChanged;

	void EndNight();

	FOnNightChanged OnNightChanged;
	FOnCashChanged OnCashChanged;
	FOnCandidateSpectateesChanged OnCandidateSpectateesChanged;

	uint32 GetNight() const { return Night; }
	void SetNight(const uint32 NewNight);

	float GetCash() const { return Cash; }
	void SetCash(const float NewCash);
	void AwardCash(const float Amount);
	bool SpendCash(const float Amount);

	void AddLivingPlayer(APlayerController* const PlayerController);
	void RemoveLivingPlayer(APlayerController* const PlayerController);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated)
	float SetupCountdown;

	UPROPERTY(ReplicatedUsing = OnRep_Night)
	uint32 Night;

	UFUNCTION()
	void OnRep_Night(uint32 PrevNight);

	UPROPERTY(ReplicatedUsing=OnRep_Cash)
	float Cash;

	UFUNCTION()
	void OnRep_Cash(float PrevCash);

	UPROPERTY(ReplicatedUsing = OnRep_CandidateSpectatees)
	FSpectateeList CandidateSpectatees;

	UFUNCTION()
	void OnRep_CandidateSpectatees();
};
