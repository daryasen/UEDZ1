#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateAI.generated.h"
UCLASS()
class MECHANICSHW_API UBTService_UpdateAI : public UBTService
{
    GENERATED_BODY()
public:
    UBTService_UpdateAI();
protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};