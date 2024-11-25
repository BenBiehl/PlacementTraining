#include "PlacementTraining.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "plane.h"

BAKKESMOD_PLUGIN(PlacementTraining, "Placement Training Plugin", "1.0", PLUGINTYPE_FREEPLAY)

// NOT DONE YET, STILL NEED TO WORK ON EVERYTHING!!
void PlacementTraining::onLoad()
{
    this->blockGoal = false;
    cvarManager->registerCvar("placement_goal_block", "1", "Right now just need this variable here", true, true, 0.0f, true, 1.0f, true);

    cvarManager->registerNotifier("obstacle_place", [&gw = this->gameWrapper, this](std::vector<std::string> commands) {
        bool retflag;
        spawnGoal(retflag);
        if (retflag) return;
        this->blockGoal = true;
        gameWrapper->RegisterDrawable(std::bind(&PlacementTraining::render, this, std::placeholders::_1));
        gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", bind(&PlacementTraining::checkCollision, this, std::placeholders::_1));
        }, "Spawns the plane in front of the goal.", PERMISSION_FREEPLAY | PERMISSION_PAUSEMENU_CLOSED);
}

void PlacementTraining::onUnload()
{
    if (blockGoal)
    {
        blockGoal = false;
    }
}

void PlacementTraining::spawnGoal(bool& retflag)
{
    if (blockGoal)
    {
        retflag = false;
        return;
    }

    plane = Plane();

    plane.setPosition(Vector(100, 100, 100));

    blockGoal = true;

    retflag = true;
}

void PlacementTraining::checkCollision(std::string eventName)
{
    retflag = false;
}

void PlacementTraining::render(CanvasWrapper canvas)
{
    if (blockGoal)
    {
        plane.render(canvas);
    }
}

Vector PlacementTraining::calculatePlanePosition(CarWrapper car)
{
    Vector carPos = car.GetCarPosition();
    Vector planePos = carPos + Vector(0, 0, 100);

    return planePos;
}

void PlacementTraining::renderCorrectly(CanvasWrapper canvas, Vector firstPoint, Vector secondPoint,
    Vector camLocation, Rotator camRotation, Vector2 canvasSize)
{
    if (blockGoal)
    {
        Vector planePos = calculatePlanePosition(firstPoint);
        plane.setPosition(planePos);

        plane.render(canvas);
    }
}

void strip(std::string& input)
{
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);
}
