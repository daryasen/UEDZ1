#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "LabAIController.generated.h"
class UBehaviorTree;
UCLASS()
class MECHANICSHW_API ALabAIController : public AAIController
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTree = nullptr;
    float FleeUntil = 0.0f;
    UFUNCTION()
    void OnPlayerInteraction();
protected:
    virtual void OnPossess(APawn* InPawn) override;
};