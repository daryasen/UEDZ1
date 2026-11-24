#include "BTTask_FindAIPoint.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
UBTTask_FindAIPoint::UBTTask_FindAIPoint()
{
    NodeName = TEXT("Find AI Point");
}
EBTNodeResult::Type UBTTask_FindAIPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Board = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Board)
        return EBTNodeResult::Failed;
    APawn* Enemy = Controller->GetPawn();
    if (!Enemy)
        return EBTNodeResult::Failed;
    UNavigationSystemV1* Nav = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Enemy->GetWorld());
    if (!Nav)
        return EBTNodeResult::Failed;
    FNavLocation Point;
    if (!bFlee)
    {
        FVector Home = Board->GetValueAsVector(TEXT("HomeLocation"));
        if (!Nav->GetRandomReachablePointInRadius(Home, 1000.0f, Point))
            return EBTNodeResult::Failed;
    }
    else
    {
        APawn* Player = UGameplayStatics::GetPlayerPawn(Enemy, 0);
        if (!Player)
            return EBTNodeResult::Failed;
        FVector EnemyLocation = Enemy->GetActorLocation();
        FVector PlayerLocation = Player->GetActorLocation();
        Point.Location = EnemyLocation;
        float BestDistance = FVector::Dist2D(EnemyLocation, PlayerLocation);
        for (int i = 0; i < 20; i++)
        {
            FNavLocation Candidate;
            if (Nav->GetRandomReachablePointInRadius(EnemyLocation, 1000.0f, Candidate))
            {
                float Distance = FVector::Dist2D(Candidate.Location, PlayerLocation);
                if (Distance > BestDistance)
                {
                    BestDistance = Distance;
                    Point = Candidate;
                }
            }
        }
    }
    Board->SetValueAsVector(TEXT("MoveLocation"), Point.Location);
    return EBTNodeResult::Succeeded;
}