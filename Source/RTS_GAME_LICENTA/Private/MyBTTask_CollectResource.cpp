// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_CollectResource.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
 

     UMyBTTask_CollectResource::UMyBTTask_CollectResource()
{
    NodeName = TEXT("Collect Resource");

    static ConstructorHelpers::FClassFinder<AActor> WorkerBPClass(TEXT("/Game/Licenta/Core/Players/Enemies/Enemy_Worker/BP_WORKER_ENEMY.BP_WORKER_ENEMY_C"));
    if (WorkerBPClass.Class != nullptr)
    {
        WorkerClass = WorkerBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_CollectResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(GetSelectedBlackboardKey()));
    if (!TargetActor)
    {
        return EBTNodeResult::Failed;
    }

    AActor* WorkerActor = UGameplayStatics::GetActorOfClass(GetWorld(), WorkerClass);
    if (!WorkerActor)
    {
        return EBTNodeResult::Failed;
    }

    // Use reflection to call the Blueprint function
    FName FunctionName = FName(TEXT("GatherThisResource"));
    UFunction* Function = WorkerActor->FindFunction(FunctionName);

    if (Function)
    {
        struct FCustomAttackParams
        {
            AActor* Target;
        };

        FCustomAttackParams Params;
        Params.Target = TargetActor;

        WorkerActor->ProcessEvent(Function, &Params);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
