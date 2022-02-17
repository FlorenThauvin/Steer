#pragma once
#include "CoreMinimal.h"
#include "Vehicule.h"
#include "VehiculeIA.generated.h"

UENUM()
enum AlgoUsing{
	SEEK	  UMETA(DisplayName = "Seek Algo"),
	EVADE	  UMETA(DisplayName = "Evade Algo"),
	FLEE	  UMETA(DisplayName = "Flee Algo"),
	ARRIVAL   UMETA(DisplayName = "Arrival Algo"),
	PURSUIT	  UMETA(DisplayName = "Pursuit Algo"),
};

UCLASS()
class TP1_IA_API AVehiculeIA : public AVehicule{
	GENERATED_BODY()

public:
	AVehiculeIA();
	virtual void Tick(float DeltaTime) override;
	FVector ArrivalVelocity(FVector TargetLocation);
	FVector SeekVelocity(FVector TargetLocation);
	FVector FleeVelocity(FVector TargetLocation);
	FVector EvadeVelocity(float DeltaTime);
	FVector PursuitVelocity();
	void ChangeAlgo();
	AlgoUsing IntToEnum();

protected:
	virtual void BeginPlay() override;
	bool IsNew = false;
	float Time = 0;
	int Index = 0;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
	TEnumAsByte<AlgoUsing> UsingAlgo;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
	float SlowingDistance;
	UPROPERTY(EditAnywhere, Category = "Target")
	AVehicule* Target;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
	float DistanceChange;
	FVector NewTargetEvade;
};
