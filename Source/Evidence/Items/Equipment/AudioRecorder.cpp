// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioRecorder.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"

AAudioRecorder::AAudioRecorder()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	
	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing"));
	
	PerceptionComponent->ConfigureSense(*Hearing);
}

void AAudioRecorder::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnSense);
}

void AAudioRecorder::OnSense(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Sensed");
}
