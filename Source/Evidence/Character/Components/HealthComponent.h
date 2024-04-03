// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVIDENCE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	void ReceiveDamage(const float Amount);

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_IsAlive)
	bool isAlive = true;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float Health;

	UFUNCTION()
	void OnRep_IsAlive(const bool PrevIsAlive);

	UFUNCTION()
	void OnRep_Health(const float PrevHealth);
		
};
