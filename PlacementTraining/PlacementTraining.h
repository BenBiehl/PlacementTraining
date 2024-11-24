#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"

#pragma comment( lib, "pluginsdk.lib" )

class PlacementTraining : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	bool placementEnabled = false;

public:
	virtual void onLoad();
	virtual void onUnload();
	virtual void loadGoal(int shotNum);
};

