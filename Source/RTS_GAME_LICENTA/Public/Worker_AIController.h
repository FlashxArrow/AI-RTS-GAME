// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Worker_AIController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_LICENTA_API AWorker_AIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AWorker_AIController(FObjectInitializer const& FObjectInitializer); // cream un obiect editabil

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
