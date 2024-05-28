// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

AAlienCharacter::AAlienCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WorthAlive = 1000.f;
	WorthDead = 500.f;
}

float AAlienCharacter::GetBaseWorth() const
{
	if (IsAlive())
	{
		return WorthAlive;
	}
	{
		return WorthDead;
	}
}

EEvidentialType AAlienCharacter::GetType() const
{
	return EEvidentialType::Alien;
}
