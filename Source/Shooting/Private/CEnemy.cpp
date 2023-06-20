// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "CPlayer.h"
#include <Kismet/KismetMathLibrary.h>
#include "DestoryZone.h"
#include "CBullet.h"

// BoxComp 가 다른 물체와 충돌했을 때
// 갸도 죽고 나도 죽고 하고싶다.
// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	// BoxComp 의 충돌 프리셋 설정;
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComp);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BodyMesh 에서 사용할 StaticMesh 데이터 동적 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingAssets/Drone/Drone_low.Drone_low'"));
	// 만약 성공적으로 로딩이 됐다면
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh 의 StaticMesh 에 할당하고 싶다.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
}


// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	// BoxComp 가 다른 물체와 충돌했을 때
	// -> 처리할 콜백 함수를 등록하고 싶다.
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);

	// 타겟을 찾아서 Target 변수에 넣어놓자.
	Target = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));

	// 태어날때 방향 구하기
	// 타겟이 있으면 타겟쪽으로
	// 타겟이 있을 때 랜덤한 30% 의 확률로 타겟쪽으로 아니면 아래로
	int percent = FMath::RandRange(1, 100);
	if (Target && percent < 30)
	{
		Direction = Target->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	}
	// 그렇지 않으면 
	else
	{
		// 아래로
		Direction = FVector::DownVector;
	}

	// Direction 방향으로 Actor 가 회전하도록 처리하고 싶다.
	FRotator Rot = UKismetMathLibrary::MakeRotFromZX(Direction, GetActorForwardVector());
	SetActorRotation(Rot);
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 플레이어를 오른쪽으로 계속 이동시키고 싶다.
	// 2. 이동시키고 싶다.
	// P = P0 + vt
	
	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);


	// 5초후에 사라지게 하고 싶다.
	// 1. 시간이 흘렀으니까
	currentTime += DeltaTime;
	// 2. why? 5초가 됐으니까
	// -> 만약 경과시간이 제거시간을 초과했다면
	if (currentTime > destroyTime)
	{
		// 3. 사라지게 하고싶다.	
		Destroy();
	}
}

// 갸도 죽고 나도 죽고 하고싶다.
void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 녀석이 DestroyZone 이라면 
	ADestoryZone* DZ = Cast<ADestoryZone>(OtherActor);
	if (DZ != nullptr)
	{
		// 아무것도 처리하지 않는다.
		return;
	}

	// 폭발효과 재생
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorLocation());

	// 만약 부딪힌 녀석이 총알이라면
	// -> 탄창에 넣어주자.
	// 그렇지않으면
	// -> 제거하자
	ACBullet* BT = Cast<ACBullet>(OtherActor);
	if (BT != nullptr)
	{
		// 탄창에 넣어주자
		// 1. 플레이어가 필요하다.
		ACPlayer* Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		// 2. 탄창이 필요하다.
		Player->bulletPool.Add(BT);
		BT->SetActive(false);
	}
	else
	{
		OtherActor->Destroy();
	}

	Destroy();
}

