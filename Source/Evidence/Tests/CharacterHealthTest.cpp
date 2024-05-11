#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Evidence/Character/EvidenceCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthTest, "Character.Health", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FHealthTest::RunTest(const FString& Parameters)
{
	const AEvidenceCharacter* const Char = NewObject<AEvidenceCharacter>();

	if (Char->GetHealth() != Char->GetMaxHealth())
	{
		AddError(TEXT("Newly-spawned characters must start at max health"));
	}

	return true;
}