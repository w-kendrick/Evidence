// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoCamera.h"
#include "Net/UnrealNetwork.h"

AVideoCamera::AVideoCamera()
{
	FPS = 10;
	MaxVideoLength = 10.f;
	RecordStatus = ERecordStatus::PreRecording;
}

void AVideoCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVideoCamera, RecordStatus);
}

void AVideoCamera::StartRecording()
{
	FrameCount = 0;
	CurrentCaptures.Empty();
	GetWorldTimerManager().SetTimer(RecordHandle, this, &ThisClass::FrameCheck, 1.f / FPS, true);
	SetRecordStatus(ERecordStatus::Recording);
}

void AVideoCamera::StopRecording()
{
	GetWorldTimerManager().ClearTimer(RecordHandle);
	SetRecordStatus(ERecordStatus::PostRecording);
	
	const FEvidentialCapture FinalCapture = FEvidentialCapture(EEvidentialMedium::Photo, CurrentCaptures);
	Captures.Add(FinalCapture);
}

void AVideoCamera::FrameCheck()
{
	if (RecordStatus == ERecordStatus::Recording && FrameCount < FPS * MaxVideoLength)
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

void AVideoCamera::SetRecordStatus(const ERecordStatus NewStatus)
{
	RecordStatus = NewStatus;
	OnRecordingChanged.Broadcast(RecordStatus);
}

void AVideoCamera::OnRep_RecordStatus(const ERecordStatus PrevStatus)
{
	OnRecordingChanged.Broadcast(RecordStatus);
}

uint8 AVideoCamera::GetFrameIndex() const
{
	return FrameCount;
}
