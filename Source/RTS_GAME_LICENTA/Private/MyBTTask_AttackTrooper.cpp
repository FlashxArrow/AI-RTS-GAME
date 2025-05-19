// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_AttackTrooper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"



UMyBTTask_AttackTrooper::UMyBTTask_AttackTrooper()
{
    NodeName = TEXT("Attack Trooper");

    // Set the default class for TrooperClass
    static ConstructorHelpers::FClassFinder<AActor> TrooperBPClass(TEXT(""));
    if (TrooperBPClass.Class != nullptr)
    {
        TrooperClass = TrooperBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_AttackTrooper::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    AActor* TrooperActor = UGameplayStatics::GetActorOfClass(GetWorld(), TrooperClass);
    if (!TrooperActor)
    {
        return EBTNodeResult::Failed;
    }

    // Use reflection to call the Blueprint function
    FName FunctionName = FName(TEXT("AttackThisActor"));
    UFunction* Function = TrooperActor->FindFunction(FunctionName);

    if (Function)
    {
        struct FCustomAttackParams
        {
            AActor* Target;
        };

        FCustomAttackParams Params;
        Params.Target = TargetActor;

        TrooperActor->ProcessEvent(Function, &Params);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
