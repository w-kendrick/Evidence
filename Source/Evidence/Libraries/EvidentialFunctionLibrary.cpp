// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidentialFunctionLibrary.h"
#include "Evidence/Structs/EvidentialInfo.h"

float UEvidentialFunctionLibrary::CalculateCash(const TArray<FEvidentialCapture>& CaptureArray)
{
	return CaptureArray.Num();
}
