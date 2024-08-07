//Manages the Brazier that can be lit by the player and will save as a checkpoint

#include "Brazier.h"
#include "MyCharacter.h"

// Sets default values
ABrazier::ABrazier()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	RootComponent = VisualMesh;

	// Create the point light component
	light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	light->SetupAttachment(RootComponent);  // Attach the light to the visual mesh
	light->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	// Bind overlap events
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABrazier::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABrazier::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABrazier::BeginPlay()
{
	Super::BeginPlay();
	light->SetActive(false);
}

// Called every frame
void ABrazier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrazier::Activate()
{
	light->SetActive(true);

}

void ABrazier::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
		if (Player)
		{
			Player->focusedBrazier = this;
		}
	}
}

void ABrazier::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
		if (Player)
		{
			Player->focusedBrazier = nullptr;
		}
	}
}

void ABrazier::Flicker()
{
	if (light->Intensity > 0.0f)
		light->SetIntensity ( 0.0f );
	else
		light->SetIntensity (5000.0f);

}
