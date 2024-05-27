// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien_AIController.h"
#include "AlienCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

AAlien_AIController::AAlien_AIController()
{
}

void AAlien_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AAlienCharacter* const Char = Cast<AAlienCharacter>(InPawn))
	{
		if (UBehaviorTree* const Tree = Char->GetBehaviourTree())
		{
			UBlackboardComponent* BC;
			UseBlackboard(Tree->BlackboardAsset, BC);
			Blackboard = BC;
			RunBehaviorTree(Tree);
		}
	}
}
