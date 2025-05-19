// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindTower.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UMyBTTask_FindTower::UMyBTTask_FindTower()
{
    NodeName = TEXT("Find Random Tower!");

    // Set the default class for TrooperClass
    static ConstructorHelpers::FClassFinder<AActor> TrooperBPClass(TEXT("/Game/Licenta/Core/Buildings/Military_Tower/BP_Tower.BP_Tower_C"));
    if (TrooperBPClass.Class != nullptr)
    {
        TrooperClass = TrooperBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_FindTower::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return EBTNodeResult::Failed;
    }

    if (!TrooperClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("TrooperClass is not set"));
        return EBTNodeResult::Failed;
    }

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(World, TrooperClass, FoundActors);

    if (FoundActors.Num() == 0)
    {
        return EBTNodeResult::Failed;
    }

    // Select a random actor from the array
    AActor* RandomActor = FoundActors[FMath::RandRange(0, FoundActors.Num() - 1)];

    if (!RandomActor)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Make sure the blackboard key name matches the one in your blackboard asset (e.g., TargetTrooperer)
    BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), RandomActor);

    return EBTNodeResult::Succeeded;
}
