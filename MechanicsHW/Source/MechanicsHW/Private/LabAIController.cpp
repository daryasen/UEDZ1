#include "LabAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
void ALabAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (!InPawn || !BehaviorTree || !BehaviorTree->BlackboardAsset)
        return;
    UBlackboardComponent* Board = nullptr;
    if (UseBlackboard(BehaviorTree->BlackboardAsset, Board))
    {
        Board->SetValueAsVector(TEXT("HomeLocation"), InPawn->GetActorLocation());
        Board->SetValueAsBool(TEXT("IsFleeing"), false);
        RunBehaviorTree(BehaviorTree);
    }
}
void ALabAIController::OnPlayerInteraction()
{
    APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
    APawn* Enemy = GetPawn();
    if (!Player || !Enemy)
        return;
    float Distance = FVector::Dist2D(Player->GetActorLocation(), Enemy->GetActorLocation());
    if (Distance <= 800.0f)
        FleeUntil = GetWorld()->GetTimeSeconds() + 5.0f;
}