// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoCamera.h"
#include "Net/UnrealNetwork.h"

AVideoCamera::AVideoCamera()
{
	FPS = 10;
	MaxVideoLength = 10.f;
	isRecording = false;
}

void AVideoCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVideoCamera, isRecording);
}

void AVideoCamera::StartRecording()
{
	FrameCount = 0;
	CurrentCaptures.Empty();
	GetWorldTimerManager().SetTimer(RecordHandle, this, &ThisClass::FrameCheck, 1.f / FPS, true);
	SetIsRecording(true);
}

void AVideoCamera::StopRecording()
{
	GetWorldTimerManager().ClearTimer(RecordHandle);
	SetIsRecording(false);
	
	const FEvidentialCapture Capture = FEvidentialCapture(EEvidentialMedium::Photo, CurrentCaptures);
	AddCapture(Capture);
}

void AVideoCamera::FrameCheck()
{
	if (isRecording && FrameCount < FPS * MaxVideoLength)
	{
		const TArray<FEvidentialInfo>& Captured = CaptureFrame();
		AddToCurrentCaptures(Captured);
		FrameCount++;
	}
	else
	{
		StopRecording();
	}
}

void AVideoCamera::AddToCurrentCaptures(const TArray<FEvidentialInfo>& New)
{
	for (const FEvidentialInfo& Info : New)
	{
		CurrentCaptures.Add(Info);
	}
}

void AVideoCamera::SetIsRecording(const bool NewIsRecording)
{
	isRecording = NewIsRecording;
	OnRecordingChanged.Broadcast(isRecording);
}

void AVideoCamera::OnRep_IsRecording(const bool PrevIsRecording)
{
	OnRecordingChanged.Broadcast(isRecording);
}

uint8 AVideoCamera::GetFrameIndex() const
{
	return FrameCount;
}
