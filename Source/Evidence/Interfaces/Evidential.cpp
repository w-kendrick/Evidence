// Fill out your copyright notice in the Description page of Project Settings.


#include "Evidential.h"

// Add default functionality here for any IEvidential functions that are not pure virtual.

float IEvidential::GetBaseWorth() const
{
	return 0.0f;
}

EEvidentialType IEvidential::GetType() const
{
	return EEvidentialType::Alien;
}
