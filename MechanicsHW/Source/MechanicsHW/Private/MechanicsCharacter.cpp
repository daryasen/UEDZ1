#include "MechanicsCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
AMechanicsCharacter::AMechanicsCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AMechanicsCharacter::BeginPlay()
{
    Super::BeginPlay();
    WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}
void AMechanicsCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsSprinting)
    {
        Stamina = FMath::Max(0.0f, Stamina - 25.0f * DeltaTime);
        if (Stamina <= 0.0f)
        {
            StopSprint();
        }
    }
    else
    {
        Stamina = FMath::Min(100.0f, Stamina + 15.0f * DeltaTime);
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Green, FString::Printf(TEXT("Stamina: %.1f"), Stamina));
    }
}
void AMechanicsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (Input)
    {
        if (SprintAction)
        {
            Input->BindAction(SprintAction, ETriggerEvent::Started, this, &AMechanicsCharacter::StartSprint);
            Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMechanicsCharacter::StopSprint);
            Input->BindAction(SprintAction, ETriggerEvent::Canceled, this, &AMechanicsCharacter::StopSprint);
        }
        if (InteractAction)
        {
            Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AMechanicsCharacter::Interact);
        }
    }
}
void AMechanicsCharacter::StartSprint()
{
    if (Stamina > 0.0f)
    {
        bIsSprinting = true;
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}
void AMechanicsCharacter::StopSprint()
{
    bIsSprinting = false;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
void AMechanicsCharacter::Interact()
{
    OnInteraction.Broadcast();
}