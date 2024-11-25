#pragma once
#pragma comment(lib, "bakkesmod.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "plane.h"

class PlacementTraining : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    virtual void onLoad();
    virtual void onUnload();

    void spawnGoal(bool& retflag);
    void checkCollision(std::string eventName);

private:
    Plane plane;
    bool blockGoal = false;

    void render(CanvasWrapper canvas);
    Vector calculatePlanePosition(CarWrapper car);
    void renderCorrectly(CanvasWrapper canvas, Vector firstPoint, Vector secondPoint, Vector camLocation, Rotator camRotation, Vector2 canvasSize);
};

void strip(std::string& input);
