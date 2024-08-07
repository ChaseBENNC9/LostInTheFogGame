#pragma once
//Header file for the Brazier class
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

#include "Brazier.generated.h"

UCLASS()
class MYPROJECT_API ABrazier : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABrazier();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	UStaticMeshComponent* VisualMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
	UPointLightComponent* light;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* TriggerBox;
	void Activate();
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	void Flicker();
	FTimerHandle MemberTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
