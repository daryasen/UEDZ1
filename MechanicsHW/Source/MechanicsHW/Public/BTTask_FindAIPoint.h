#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindAIPoint.generated.h"
UCLASS()
class MECHANICSHW_API UBTTask_FindAIPoint : public UBTTaskNode
{
    GENERATED_BODY()
public:
    UBTTask_FindAIPoint();
    UPROPERTY(EditAnywhere, Category = "AI")
    bool bFlee = false;
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};