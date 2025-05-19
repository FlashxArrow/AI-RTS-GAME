// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ResetOrder.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_ResetOrder::UMyBTTask_ResetOrder()
{
	NodeName = TEXT("Reset Attack Completed");
}

EBTNodeResult::Type UMyBTTask_ResetOrder::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsBool(TEXT("bIsAttackCompleted"), false);

	return EBTNodeResult::Succeeded;
}