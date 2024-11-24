// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evidence/Tests/MasterTest.h"
#include "LockerStorageVisibilityTest.generated.h"

class ALocker;

/**
 * 
 */
UCLASS()
class EVIDENCE_API ALockerStorageVisibilityTest : public AMasterTest
{
	GENERATED_BODY()

public:
	ALockerStorageVisibilityTest();

	void StartTest() override;

private:
	void AfterEquipmentStore();
	void AfterEquipmentRemoval();

	UPROPERTY()
	ALocker* Locker;

	UPROPERTY()
	AEquipment* ServerTestEquipment = nullptr;

	UPROPERTY()
	AEquipment* Client1TestEquipment = nullptr;

	UPROPERTY()
	AEquipment* Client2TestEquipment = nullptr;
};
