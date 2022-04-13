// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapezoidalEdtiorActor.h"

// Sets default values
ATrapezoidalEdtiorActor::ATrapezoidalEdtiorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrapezoidalEdtiorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapezoidalEdtiorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> ATrapezoidalEdtiorActor::EditorCurve(USplineComponent* splineCom)
{
	TArray<FVector> vecs;
	if (splineCom == nullptr)
	{
		return vecs;
	}

	if (splineCom->GetNumberOfSplinePoints() != 4)
	{
		return vecs;
	}

	float tanLeft = FMath::Tan(PI / (180.f) * LeftDeg);
	float tanRight = FMath::Tan(PI / (180.f) * RightDeg);
	if (tanLeft ==0.0f || tanRight ==0.0f)
	{
		return vecs;
	}


	float LeftBottomFragment = Height / tanLeft;
	float RightBottomFragment = Height/ tanRight;
	if ((LeftBottomFragment + RightBottomFragment)> BottomLong)
	{
		return vecs;
	}



	FVector v = FVector::ZeroVector;
	vecs.Add(v);

	v = FVector(BottomLong, 0, 0);
	vecs.Add(v);

	v = FVector(BottomLong - RightBottomFragment, -Height, 0);
	vecs.Add(v);

	v = FVector(LeftBottomFragment, -Height, 0);
	vecs.Add(v);
	
	return vecs;
}

#include "Kismet/KismetMathLibrary.h"

TArray<FVector> ATrapezoidalEdtiorActor::GetSemicircleAndQuadranglePoints(USplineComponent* splineCom)
{
	float r = (FMath::Pow(L_Semicircle, 2.0f) + FMath::Pow(Height_Semicircle, 2.0f)) / (2 * Height_Semicircle);

	TArray<FVector> points;
	if (r < Height_Semicircle || SemicircleNum == 0)
	{
		return points;
	}

	float offsetX = 0;
	float offsetY = 0;
	float offsetZ = 0;
	
	points.Add(FVector(offsetX, offsetY, offsetZ));
	points.Add(FVector(A_Quadrangle + offsetX, offsetY, offsetZ));
	points.Add(FVector(A_Quadrangle + offsetX, Height_Quadrangle + offsetY, offsetZ));
	points.Add(FVector(2 * L_Semicircle - A_Quadrangle + offsetX, Height_Quadrangle + offsetY, offsetZ));
	points.Add(FVector(2 * L_Semicircle - A_Quadrangle + offsetX, offsetY, offsetZ));
	points.Add(FVector(2 * L_Semicircle + offsetX, offsetY, offsetZ));


	FVector rLineCenter = FVector(L_Semicircle + offsetX, offsetY, offsetZ);
	

	float rL_deg = (180.f) / PI * FMath::Asin(L_Semicircle / r);
	float deg = rL_deg*2/ SemicircleNum;

	FVector r_v = rLineCenter + FVector(offsetX,r - Height_Semicircle, offsetZ);
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(r_v, FVector((2 * L_Semicircle + offsetX), 0, 0));
	for (int32 i = 1;i< SemicircleNum;i++)
	{
		points.Add(r_v + (rot + FRotator(0,  -i * deg,0)).Vector() * r) ;
	}

	return points;
}

#include "EditorCurve.h"
void ATrapezoidalEdtiorActor::EditorSemicircleAndQuadrangleCurve(USplineComponent* splineCom)
{
	if (splineCom == nullptr)
	{
		return;
	}

	TArray<FVector> points = GetSemicircleAndQuadranglePoints(splineCom);

	TArray<int32> CurveOtherPoints = BuildingEditorCurve::Get().GetSplineOtherPoint(splineCom);
	BuildingEditorCurve::Get().BatchDeleteSplinePoint(splineCom, CurveOtherPoints);

	BuildingEditorCurve::Get().BatchAddSplinePoint(splineCom, points.Num());

	for (int32 i = 0 ;i<points.Num();i++)
	{
		splineCom->SetLocationAtSplinePoint(i,points[i], ESplineCoordinateSpace::Local);
		splineCom->SetSplinePointType(i, ESplinePointType::Linear);

	}
}


TArray<FVector> ATrapezoidalEdtiorActor::EditorConvexCurve(USplineComponent* splineCom)
{
	TArray<FVector> vecs;
	if (splineCom == nullptr)
	{
		return vecs;
	}

	if (splineCom->GetNumberOfSplinePoints() != 8)
	{
		return vecs;
	}

	float offsetX = 0;
	float offsetY = 0;
	float offsetZ = 0;
	vecs.Add(FVector(offsetX,offsetY,offsetZ));
	vecs.Add(FVector(left_a + top_ + right_a + offsetX,offsetY,offsetZ));
	vecs.Add(FVector(left_a + top_ + right_a + offsetX,-bottom_h + offsetY,offsetZ));
	vecs.Add(FVector(left_a + top_ +offsetX,-bottom_h + offsetY,offsetZ));
	vecs.Add(FVector(left_a +top_ + offsetX,-(bottom_h + top_h) + offsetY,offsetZ));
	vecs.Add(FVector(left_a + offsetX,-(bottom_h + top_h) + offsetY,offsetZ));
	vecs.Add(FVector(left_a + offsetX,-bottom_h + offsetY,offsetZ));
	vecs.Add(FVector(offsetX, -bottom_h + offsetY, offsetZ));

	return vecs;
}

void ATrapezoidalEdtiorActor::SetConvexSplineComPoints(USplineComponent* splineCom)
{
	if (splineCom == nullptr)
	{
		return;
	}
	TArray<FVector> locs = EditorConvexCurve(splineCom);
    

	if (locs.Num() != splineCom->GetNumberOfSplinePoints())
	{
		return;
	}

	for (int32 i = 0; i < locs.Num(); i++)
	{
		splineCom->SetLocationAtSplinePoint(i, locs[i], ESplineCoordinateSpace::Local);
		splineCom->SetSplinePointType(i, ESplinePointType::Linear);

	}
}

#include "BuildingMath.h"
#include "Engine/Classes/Engine/StaticMeshActor.h"
void ATrapezoidalEdtiorActor::GetConsecutivePointXY(AActor* act)
{
	 if (act == nullptr)
	 {
	 return;
	 }
	 FString str = "/Game/Cone.Cone";
	 UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr,*str);
	 UWorld* World = GEditor->GetEditorWorldContext().World();
	 TArray<UStaticMeshComponent*> meshComs;
	 act->GetComponents<UStaticMeshComponent>(meshComs);

	 TMap<FVector,UStaticMeshComponent*> coms;
	 TArray<FVector> ves;
	 for (UStaticMeshComponent* c : meshComs)
	 {
		if (c == nullptr)
		{
		continue;
		}

		ves.Add(c->GetComponentToWorld().GetLocation());
	 }

	 TArray<twoPoints> points =  BuildingMath::Get().GetConsecutivePointXY(ves, "");

	 FTransform f = FTransform::Identity;
	 for (twoPoints& c : points)
	 {
		FVector v = c.A + c.B;

		if (v/2 == FVector(663.5,-2020,0))
		{

			FString a = c.A.ToString() + "_" + c.B.ToString();
			
		}



		f.SetLocation(v/2);

		if (AStaticMeshActor* meshActor = Cast<AStaticMeshActor>(World->SpawnActor(AStaticMeshActor::StaticClass(),&f)))
		{
			meshActor->GetStaticMeshComponent()->SetStaticMesh(mesh);
		}
		
		

	 }




}