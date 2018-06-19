// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	MovementManager = CreateDefaultSubobject<UPlayerMovementManager>(TEXT("PlayerMovementManager"));

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	CharacterCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CharacterCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Moveleft", this, &AMyCharacter::MoveLeft);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyCharacter::TouchStopped);
}

void AMyCharacter::MoveRight(float Val)
{
	AddMovementInput(FVector(1.0f, 0.f, 0.f), Val);
}

void AMyCharacter::MoveLeft(float Val)
{
	AddMovementInput(FVector(-1.0f, 0.f, 0.f), Val);
}

void AMyCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Jump();
}

void AMyCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}