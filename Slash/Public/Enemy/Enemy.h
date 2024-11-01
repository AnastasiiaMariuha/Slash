#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	/** <AActor>*/
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	/** </AActor>*/

	/** <IHitInterface>*/
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	/** </IHitInterface>*/

protected:
	/** <AActor>*/
	virtual void BeginPlay() override;
	/** </AActor>*/

	/** <ABaseCharacter>*/
	virtual void Die() override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual int32 PlayDeathMontage() override;
	/** </ABaseCharacter>*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	bool bPlayEquipSoundForPlayerOnly;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
private:
	/** AI Behavior */
	void InitializeEnemy();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void DelayFunction();											//discord option for the delaying time	
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void SpawnDefaultWeapon();
	
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn); //Callback for OnPawnSeen in UPawnSensingComponent

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY()
	class AAIController* EnemyController;

	// Current patrol target
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;


	FTimerHandle PatrolTimer;
	FTimerHandle DelayTimer;										//discord option for the delaying time	

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 2.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 8.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PtrollingSpeed = 124.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeathLifeSpan = 8.f;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	double CombatRadius = 1000.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	double AttackRadius = 500.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	double PatrolRadius = 200.f;
};