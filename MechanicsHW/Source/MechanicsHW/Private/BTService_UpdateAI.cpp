#include "BTService_UpdateAI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LabAICharacter.h"
#include "LabAIController.h"
#include "MechanicsCharacter.h"
UBTService_UpdateAI::UBTService_UpdateAI()
{
    NodeName = TEXT("Update AI State");
    bNotifyTick = true;
    Interval = 0.2f;
    RandomDeviation = 0.0f;
}
void UBTService_UpdateAI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    ALabAIController* Controller = Cast<ALabAIController>(OwnerComp.GetAIOwner());
    UBlackboardComponent* Board = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Board)
        return;
    ALabAICharacter* Enemy = Cast<ALabAICharacter>(Controller->GetPawn());
    AMechanicsCharacter* Player = Cast<AMechanicsCharacter>(UGameplayStatics::GetPlayerCharacter(Controller, 0));
    if (!Enemy)
        return;
    if (!Player)
    {
        Board->ClearValue(TEXT("TargetActor"));
        Board->SetValueAsBool(TEXT("IsFleeing"), false);
        Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
        return;
    }
    Player->OnInteraction.AddUniqueDynamic(Controller, &ALabAIController::OnPlayerInteraction);
    bool IsFleeing = Controller->GetWorld()->GetTimeSeconds() < Controller->FleeUntil;
    bool HasTarget = Board->GetValueAsObject(TEXT("TargetActor")) != nullptr;
    float Distance = FVector::Dist2D(Enemy->GetActorLocation(), Player->GetActorLocation());
    float Range = HasTarget ? 1800.0f : 1200.0f;
    if (Distance <= Range)
        Board->SetValueAsObject(TEXT("TargetActor"), Player);
    else
        Board->ClearValue(TEXT("TargetActor"));
    Board->SetValueAsBool(TEXT("IsFleeing"), IsFleeing);
    if (IsFleeing)
        Enemy->GetCharacterMovement()->MaxWalkSpeed = 700.0f;
    else if (Board->GetValueAsObject(TEXT("TargetActor")))
        Enemy->GetCharacterMovement()->MaxWalkSpeed = 550.0f;
    else
        Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}