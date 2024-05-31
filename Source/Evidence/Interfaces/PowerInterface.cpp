// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerInterface.h"

// Add default functionality here for any IPowerInterface functions that are not pure virtual.

UPowerComponent* IPowerInterface::GetPowerComponent() const
{
	return nullptr;
}

void IPowerInterface::Activate()
{
}

void IPowerInterface::Deactivate()
{
}
