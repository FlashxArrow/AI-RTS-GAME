// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindResource.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"



UMyBTTask_FindResource::UMyBTTask_FindResource()
{
    NodeName = TEXT("Find Closest Resource");

    // Set the default class for WorkerClass
    static ConstructorHelpers::FClassFinder<AActor> WorkerBPClass(TEXT("/Game/Licenta/Core/Resource/BP_Resource.BP_Resource_C"));
    if (WorkerBPClass.Class != nullptr)
    {
        WorkerClass = WorkerBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_FindResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return EBTNodeResult::Failed;
    }

    if (!WorkerClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("WorkerClass is not set"));
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
    UGameplayStatics::GetAllActorsOfClass(World, WorkerClass, FoundActors);

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
