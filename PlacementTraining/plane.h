#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"

class Plane
{
public:
    // Constructors
    Plane();
    Plane(Vector newPoint, Vector newNormal);
    Plane(Vector newPoint, Vector newNormal, float width, float height);

    // Destructor
    ~Plane();

    // Setters
    void setPoint(Vector newPoint);
    void setNormal(Vector newNormal);
    void setDimensions(float newWidth, float newHeight);

    // Getters
    Vector getPoint();
    Vector getNormal();
    float getWidth();
    float getHeight();

    // Check if object intersects
    bool intersects(Vector other);

private:
    Vector point;
    Vector normal;
    float width;
    float height;

    // Additional functions
    void calculateCorners();
    Vector corners[4];
};