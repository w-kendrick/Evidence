// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidentialFunctionLibrary.h"
#include "Evidence/Structs/EvidentialCapture.h"

TMap<TPair<EEvidentialType, EEvidentialMedium>, float> WorthMap = {
	{{EEvidentialType::Alien, EEvidentialMedium::Photo}, 5.0f},
	{{EEvidentialType::Alien, EEvidentialMedium::Audio}, 5.0f},
	{{EEvidentialType::Alien, EEvidentialMedium::Video}, 7.5f},
	{{EEvidentialType::Alien, EEvidentialMedium::Item}, 1000.0f},
	{{EEvidentialType::UFO, EEvidentialMedium::Photo}, 3.0f},
	{{EEvidentialType::UFO, EEvidentialMedium::Audio}, 1.0f},
	{{EEvidentialType::UFO, EEvidentialMedium::Video}, 10.0f},
	{{EEvidentialType::UFO, EEvidentialMedium::Item}, 1000000.0f},
	{{EEvidentialType::Victim, EEvidentialMedium::Photo}, 3.0f},
	{{EEvidentialType::Victim, EEvidentialMedium::Audio}, 1.0f},
	{{EEvidentialType::Victim, EEvidentialMedium::Video}, 10.0f},
	{{EEvidentialType::Victim, EEvidentialMedium::Item}, 1000000.0f},
	{{EEvidentialType::Tech, EEvidentialMedium::Photo}, 3.0f},
	{{EEvidentialType::Tech, EEvidentialMedium::Audio}, 1.0f},
	{{EEvidentialType::Tech, EEvidentialMedium::Video}, 10.0f},
	{{EEvidentialType::Tech, EEvidentialMedium::Item}, 1000000.0f},
	{{EEvidentialType::Prints, EEvidentialMedium::Photo}, 3.0f},
	{{EEvidentialType::Prints, EEvidentialMedium::Audio}, 1.0f},
	{{EEvidentialType::Prints, EEvidentialMedium::Video}, 10.0f},
	{{EEvidentialType::Prints, EEvidentialMedium::Item}, 1000000.0f},
	{{EEvidentialType::Blood, EEvidentialMedium::Photo}, 3.0f},
	{{EEvidentialType::Blood, EEvidentialMedium::Audio}, 1.0f},
	{{EEvidentialType::Blood, EEvidentialMedium::Video}, 10.0f},
	{{EEvidentialType::Blood, EEvidentialMedium::Item}, 1000000.0f}

};

float UEvidentialFunctionLibrary::CalculateCash(const TArray<FEvidentialCapture>& CaptureArray)
{
	float Cash = 0.0f;

	for (const FEvidentialCapture& Capture : CaptureArray)
	{
		Cash += Capture.GetWorth();
	}

	return Cash;
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
