#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MechanicsCharacter.generated.h"
class UInputAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);
UCLASS()
class MECHANICSHW_API AMechanicsCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AMechanicsCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* SprintAction = nullptr;
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* InteractAction = nullptr;
    UPROPERTY(BlueprintReadOnly, Category = "Sprint")
    bool bIsSprinting = false;
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 900.0f;
    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    float Stamina = 100.0f;
    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FOnInteraction OnInteraction;
protected:
    virtual void BeginPlay() override;
private:
    float WalkSpeed = 500.0f;
    void StartSprint();
    void StopSprint();
    void Interact();
};