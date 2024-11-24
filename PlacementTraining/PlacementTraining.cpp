#include "pch.h"
#include "PlacementTraining.h"

BAKKESMOD_PLUGIN(PlacementTraining, "Placement Training Plugin", "1.0", PERMISSION_ALL)

void PlacementTraining::onLoad()
{
	this->Log("Placemnent Training Plugin Loaded Succesfully.");
	this->loadHooks();
}

void PlacementTraining::onUnload()
{

}

void PlacementTraining::loadHooks()
{

}

void PlacementTraining::Log(std::string msg)
{
	cvarManager->log(msg);
}
