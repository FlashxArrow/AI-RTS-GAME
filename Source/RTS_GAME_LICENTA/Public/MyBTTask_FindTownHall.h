// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindTownHall.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_LICENTA_API UMyBTTask_FindTownHall : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTTask_FindTownHall();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Search")
		TSubclassOf<AActor> TrooperClass;
};
