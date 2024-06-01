// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidentialFunctionLibrary.h"
#include "Evidence/Structs/EvidentialInfo.h"

TMap<TPair<EEvidentialType, EEvidentialMedium>, float> WorthMap = {
	{{EEvidentialType::Alien, EEvidentialMedium::Photo}, 1.0f},
	{{EEvidentialType::Alien, EEvidentialMedium::Audio}, 5.0f}
};

float UEvidentialFunctionLibrary::CalculateCash(const TArray<FEvidentialCapture>& CaptureArray)
{
	return CaptureArray.Num();
}

float UEvidentialFunctionLibrary::GetWorth(const EEvidentialType Type, const EEvidentialMedium Medium)
{
	float Worth = 0.0f;

	const TPair<EEvidentialType, EEvidentialMedium> Pair = { Type, Medium };

	float* const Lookup = WorthMap.Find(Pair);

	if (Lookup)
	{
		Worth = *Lookup;
	}

	return Worth;
}
