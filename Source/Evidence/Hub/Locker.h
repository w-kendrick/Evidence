// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Locker.generated.h"

class AEquipment;

UCLASS()
class EVIDENCE_API ALocker : public AActor
{
	GENERATED_BODY()
	
public:
	ALocker();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Storage)
	TArray<AEquipment*> Storage;

	UFUNCTION()
	void OnRep_Storage();
};
