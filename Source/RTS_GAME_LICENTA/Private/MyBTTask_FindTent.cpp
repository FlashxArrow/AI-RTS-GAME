// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindTent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UMyBTTask_FindTent::UMyBTTask_FindTent()
{
    NodeName = TEXT("Find Furthest Tent");

    // Set the default class for TrooperClass
    static ConstructorHelpers::FClassFinder<AActor> TrooperBPClass(TEXT("/Game/Licenta/Core/Buildings/Military_Tent/BP_Tent.BP_Tent_C"));
    if (TrooperBPClass.Class != nullptr)
    {
        TrooperClass = TrooperBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_FindTent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    AActor* FurthestActor = nullptr;
    float MaxDistance = 0.0f;

    for (AActor* Actor : FoundActors)
    {
        if (!Actor) continue;

        float Distance = FVector::Dist(AILocation, Actor->GetActorLocation());
        if (Distance > MaxDistance)
        {
            MaxDistance = Distance;
            FurthestActor = Actor;
        }
    }

    if (!FurthestActor)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Make sure the blackboard key name matches the one in your blackboard asset (e.g., TargetTrooperer)
    BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), FurthestActor);

    return EBTNodeResult::Succeeded;
}
