#include "pch.h"
#include "PlacementTraining.h"

BAKKESMOD_PLUGIN(PlacementTraining, "Placement Training Plugin", "1.0", PLUGINTYPE_FREEPLAY)

void PlacementTraining::onLoad()
{
	cvarManager->registerCvar("placement_select_shot", "0", "Choose which shot you want to practice", true, true, 0, false, 5);

	cvarManager->registerNotifier("placement_start", [this](std::vector<std::string> params) {
		if (!gameWrapper->IsInFreeplay())
		{
			return;
		}
		this->placementEnabled = true;
		int shotSelection = cvarManager->getCvar("placement_select_shot").getIntValue();
		this->loadGoal(shotSelection);

		}, "Sets up the goal with whatever shot you want to practice", PERMISSION_FREEPLAY);

	cvarManager->registerNotifier("placement_stop", [this](std::vector<std::string> params) {
			this->placementEnabled = false;
		}, "Turns off the plugin", PERMISSION_ALL);
}

void PlacementTraining::onUnload()
{
	this->placementEnabled = false;
}

void PlacementTraining::loadGoal(int shotNum)
{
	gameWrapper->RegisterDrawable([](CanvasWrapper goal) {
		Vector2F goalTopLeft = { 200.0f, 150.0f };
		Vector2F goalSize = { 100.0f, 50.0f };

		goal.SetPosition(goalTopLeft);
		goal.SetColor(255, 0, 0, 255);
		goal.FillBox(goalSize);
	});
}
