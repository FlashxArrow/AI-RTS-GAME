// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindTent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_LICENTA_API UMyBTTask_FindTent : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTTask_FindTent();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Search")
		TSubclassOf<AActor> TrooperClass;
};
