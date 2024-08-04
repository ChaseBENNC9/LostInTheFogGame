// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/SpringArmComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Attach PlayerModel to the Root
	playerModel = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerParent"));
		playerModel->SetupAttachment(RootComponent);

	//Attach the VisualMesh to the PlayerModel 
	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
		visualMesh->SetupAttachment(playerModel);

	 springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	 springArm->SetupAttachment(RootComponent);
	 springArm->TargetArmLength = 300.f;
	 springArm->bUsePawnControlRotation = true;

	 //Attach the camera to the root component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(springArm,USpringArmComponent::SocketName);
	//Camera->SetupAttachment(RootComponent);
		Camera->bUsePawnControlRotation = false;



	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));



	if (CubeVisualAsset.Succeeded())

	{

		visualMesh->SetStaticMesh(CubeVisualAsset.Object);

		visualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	}

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MouseLocation, MouseDirection;

	APlayerController* PController = Cast<APlayerController>(Controller);

	PController->bShowMouseCursor = false;

	float xMouse, yMouse;

	PController->GetMousePosition(xMouse, yMouse);

	FVector CharLoc = GetActorLocation();

	FVector2D CharInScreen;
	PController->ProjectWorldLocationToScreen(CharLoc, CharInScreen);

	FVector2D Result;
	Result.X = -(yMouse - CharInScreen.Y);
	Result.Y = xMouse - CharInScreen.X;

	// Get angle rotation and rotation Character
	float angle = FMath::RadiansToDegrees(FMath::Acos(Result.X / Result.Size()));

	if (Result.Y < 0)
		angle = 360 - angle;

	FRotator rot(0, angle, 0);

	SetActorRotation(rot);



}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::OnMove);

		//Looking
	}
	

}

void AMyCharacter::OnMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add movement
		FVector ForwardDirection = GetActorForwardVector();
		FVector RightDirection = GetActorRightVector();

		// Calculate the movement direction based on input
		FVector MovementDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y * movementSpeed);
		AddMovementInput(GetActorRightVector(), MovementVector.X * movementSpeed);


	}
	
}
	void AMyCharacter::OnLook(const FInputActionValue & Value)
	{

	}

