#include "MyBTTask_FindTownHall.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UMyBTTask_FindTownHall::UMyBTTask_FindTownHall()
{
    NodeName = TEXT("Find TownHall!");

    // Set the default class for TrooperClass
    ConstructorHelpers::FClassFinder<AActor> TrooperBPClass(TEXT("/Game/Licenta/Core/Buildings/Warehouse_Town_Hall/BP_TownHall.BP_TownHall_C"));
    if (TrooperBPClass.Class != nullptr)
    {
        TrooperClass = TrooperBPClass.Class;
    }
}

EBTNodeResult::Type UMyBTTask_FindTownHall::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Reinitialize references to ensure they are correct for each AI instance
    UWorld* World = GetWorld();
    if (!World)
    {
        return EBTNodeResult::Failed;
    }

    // Ensure TrooperClass is valid
    if (!TrooperClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("TrooperClass is not set"));
        return EBTNodeResult::Failed;
    }

    // Reinitialize the AIController reference
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    // Reinitialize the AIPawn reference
    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    // Find all actors of the TrooperClass in the world
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

    // Reinitialize the BlackboardComp reference
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Set the random actor as the value of the blackboard key
    BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), RandomActor);

    return EBTNodeResult::Succeeded;
}
