#include "EditorCurve.h"



BuildingEditorCurve::BuildingEditorCurve()
{
}

BuildingEditorCurve::~BuildingEditorCurve()
{
}

BuildingEditorCurve& BuildingEditorCurve::Get()
{
	static TUniquePtr<BuildingEditorCurve> obj;
	if (!obj)
	{
		obj = MakeUnique<BuildingEditorCurve>();
	}
	return *obj;

}

TArray<int32> BuildingEditorCurve::GetSplineOtherPoint(USplineComponent* SplineComp)
{
	TArray<int32> otherIndex;
	if (SplineComp == nullptr)
	{
		return otherIndex;
	}

	int32 num = SplineComp->GetNumberOfSplinePoints();

	for (int32 i = 0; i < num; i++)
	{
		if (i > 1)
		{
			otherIndex.Add(i);
		}
	}

	return otherIndex;
}

void BuildingEditorCurve::BatchDeleteSplinePoint(USplineComponent* SplineComp, const TArray<int32>& SelectedKeys)
{
	if (SplineComp == nullptr || SelectedKeys.Num() == 0)
	{
		return;
	}


	TArray<int32> SelectedKeysSorted;
	for (int32 SelectedKeyIndex : SelectedKeys)
	{
		SelectedKeysSorted.Add(SelectedKeyIndex);
	}
	SelectedKeysSorted.Sort([](int32 A, int32 B) { return A > B; });

	// Delete selected keys from list, highest index first
	FInterpCurveVector& SplinePosition = SplineComp->GetSplinePointsPosition();
	FInterpCurveQuat& SplineRotation = SplineComp->GetSplinePointsRotation();
	FInterpCurveVector& SplineScale = SplineComp->GetSplinePointsScale();
	USplineMetadata* SplineMetadata = SplineComp->GetSplinePointsMetadata();

	for (int32 SelectedKeyIndex : SelectedKeysSorted)
	{
		if (SplineMetadata)
		{
			SplineMetadata->RemovePoint(SelectedKeyIndex);
		}

		SplinePosition.Points.RemoveAt(SelectedKeyIndex);
		SplineRotation.Points.RemoveAt(SelectedKeyIndex);
		SplineScale.Points.RemoveAt(SelectedKeyIndex);

		for (int Index = SelectedKeyIndex; Index < SplinePosition.Points.Num(); Index++)
		{
			SplinePosition.Points[Index].InVal -= 1.0f;
			SplineRotation.Points[Index].InVal -= 1.0f;
			SplineScale.Points[Index].InVal -= 1.0f;
		}
	}


	SplineComp->UpdateSpline();
	SplineComp->bSplineHasBeenEdited = true;

	GEditor->RedrawLevelEditingViewports(true);

}


void BuildingEditorCurve::BatchAddSplinePoint(USplineComponent* SplineComp, const int32& SideNum)
{
	if (SplineComp == nullptr)
	{
		return;
	}

	FVector v = FVector(100, 0, 0);
	FVector rot = FRotator::ZeroRotator.Vector();
	for (int32 i = 0; i < SideNum - 2; i++)
	{
		v = rot * 100 + v;
		SplineComp->AddSplinePoint(v, ESplineCoordinateSpace::Local);
	}
}