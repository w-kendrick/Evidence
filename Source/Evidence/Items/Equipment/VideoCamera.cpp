// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoCamera.h"
#include "Net/UnrealNetwork.h"

AVideoCamera::AVideoCamera()
{
	FPS = 10;
	MaxVideoLength = 10.f;
}

void AVideoCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVideoCamera, isRecording);
}

void AVideoCamera::StartRecording()
{

}

void AVideoCamera::StopRecording()
{

}

void AVideoCamera::SetIsRecording(const bool new_isRecording)
{
	isRecording = new_isRecording;
	OnRecordingChanged.Broadcast(isRecording);
}

void AVideoCamera::OnRep_IsRecording(const bool prev_isRecording)
{
	OnRecordingChanged.Broadcast(isRecording);
}
