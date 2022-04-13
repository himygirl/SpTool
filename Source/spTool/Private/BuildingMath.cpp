#include "BuildingMath.h"



BuildingMath::BuildingMath()
{
}

BuildingMath::~BuildingMath()
{
}

BuildingMath& BuildingMath::Get()
{
	static TUniquePtr<BuildingMath> obj;
	if (!obj)
	{
		obj = MakeUnique<BuildingMath>();
	}
	return *obj;



}

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
TArray<twoPoints> BuildingMath::GetConsecutivePointXY(const TArray<FVector>& points, const FString& tag)
{
	TArray<FVector> ves = points;

	TArray<twoPoints> twoPos;
	for (const FVector& c : points)
	{
		ves.Remove(c);
		if (ves.Num() == 0)
		{
		 continue;
		}

		TMap<int32,TArray<FVector>> ps;
		for (const FVector& d : ves)
		{
			FRotator rot = UKismetMathLibrary::FindLookAtRotation(c, d);
			float nearly = 0.5f;
			if (FMath::IsNearlyEqual(rot.Yaw,0.0f, nearly))
			{
				TArray<FVector>& p = ps.FindOrAdd(0);
				p.Add(d);			
			}
			else if (FMath::IsNearlyEqual(rot.Yaw, 90.0f, nearly))
			{
				TArray<FVector>& p = ps.FindOrAdd(90);
				p.Add(d);
			}
			else if (FMath::IsNearlyEqual(rot.Yaw, -90.0f, nearly))
			{
				TArray<FVector>& p = ps.FindOrAdd(-90);
				p.Add(d);
			}
			else if (FMath::IsNearlyEqual(rot.Yaw, 180.0f, nearly))
			{
				TArray<FVector>& p = ps.FindOrAdd(180);
				p.Add(d);
			}
		}

		for (auto & d : ps)
		{
			TArray<FVector> vs = d.Value;

			if (vs.Num() == 0)
			{
				continue;
			}
			twoPoints p;
			p.A = c;

			if (c == FVector(1327,-2020,0))
			{
				 FString vvcd = c.ToString();
			}



			if (vs.Num() == 1)
			{
				p.B = vs[0];
			}
			else
			{
				FVector v = FVector::ZeroVector;
				float dis =0;
				for (int32 i = 0 ;i< vs.Num();i++)
				{
					float dd = UKismetMathLibrary::Vector_Distance(c, vs[i]);
					if (i == 0)
					{
						dis = dd;
						v = vs[0];
					}
					else
					{
						if (dd<dis)
						{
							v = vs[i];
						}
					}
				}
				if (v == FVector(0,-2020,0))
				{
					FString ddcc = v.ToString();
				}



				p.B = v;			
			}
			twoPos.Add(p);
		}

		
	}

	return twoPos;
}