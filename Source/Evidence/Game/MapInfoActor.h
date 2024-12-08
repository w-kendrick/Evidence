// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapInfoActor.generated.h"

UCLASS()
class EVIDENCE_API AMapInfoActor : public AActor
{
	GENERATED_BODY()
	
public:
	AMapInfoActor();

	FVector2D GetTopLeftPoint() const { return TopLeftPoint; }
	FVector2D GetBottomRightPoint() const { return BottomRightPoint; }

private:
	UPROPERTY(EditDefaultsOnly)
	FVector2D TopLeftPoint;

	UPROPERTY(EditDefaultsOnly)
	FVector2D BottomRightPoint;

};
