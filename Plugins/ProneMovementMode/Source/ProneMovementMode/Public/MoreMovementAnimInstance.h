// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MoreMovementAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMoreMovementMode : uint8
{
	Walk		UMETA(DisplayName = "Walk"),
	Prone		UMETA(DisplayName = "Prone"),
	Crouch		UMETA(DisplayName = "Crouch"),
	Sprint		UMETA(DisplayName = "Sprint"),
	Jump		UMETA(DisplayName = "Jump")
};

class AProneCharacter;

/*
	Anim instance that sets up variables for animation state transitions 
*/
UCLASS()
class PRONEMOVEMENTMODE_API UMoreMovementAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	EMoreMovementMode Mode;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	AProneCharacter* MoreMovementCharacter;

	virtual EMoreMovementMode GetMovementMode() const;
	
};
