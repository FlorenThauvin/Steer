#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicule.generated.h"

UCLASS()
class TP1_IA_API AVehicule : public AActor
{
	GENERATED_BODY()
	
public:	
	AVehicule();
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE FVector GetVelocity() { return Velocity; };
	FVector Truncate(FVector v, float maxi);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Physic")
	FVector Velocity;
	UPROPERTY(EditAnywhere, Category = "Physic")
	float Mass = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Physic")
	float MaxSpeed = 15.0f;
	UPROPERTY(EditAnywhere, Category = "Physic")
	float MaxForce = 1.0f;

};
