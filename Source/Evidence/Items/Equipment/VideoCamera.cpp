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
	GetWorldTimerManager().SetTimer(RecordHandle, this, &ThisClass::FrameCheck, 1.f / FPS, true);
	RecordStatus = ERecordStatus::Recording;
}

void AVideoCamera::StopRecording()
{
	GetWorldTimerManager().ClearTimer(RecordHandle);
	RecordStatus = ERecordStatus::PostRecording;
}

void AVideoCamera::FrameCheck()
{
	FrameCount++;
	if (RecordStatus == ERecordStatus::Recording && FrameCount <= FPS * MaxVideoLength)
	{
		SaveFrame();
	}
	else
	{
		StopRecording();
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
