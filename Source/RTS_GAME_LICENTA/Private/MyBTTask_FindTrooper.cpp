// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindTrooper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"



UMyBTTask_FindTrooper::UMyBTTask_FindTrooper()
{
    NodeName = TEXT("Find Closest Trooper");

    // Set the default class for TrooperClass
    static ConstructorHelpers::FClassFinder<AActor> TrooperBPClass(TEXT("/Game/Licenta/Core/Players/Soldier/BP_TROOP.BP_TROOP_C"));
    if (TrooperBPClass.Class != nullptr)
    {
        TrooperClass = TrooperBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_FindTrooper::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    FVector AILocation = AIPawn->GetActorLocation();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(World, TrooperClass, FoundActors);

    if (FoundActors.Num() == 0)
    {
        return EBTNodeResult::Failed;
    }

    AActor* ClosestActor = nullptr;
    float MinDistance = TNumericLimits<float>::Max();

    for (AActor* Actor : FoundActors)
    {
        if (!Actor) continue;

        float Distance = FVector::Dist(AILocation, Actor->GetActorLocation());
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            ClosestActor = Actor;
        }
    }

    if (!ClosestActor)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }


    BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), ClosestActor);

    return EBTNodeResult::Succeeded;
}
