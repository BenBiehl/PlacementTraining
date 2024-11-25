#include "plane.h"

Plane::Plane()
{
    this->point = Vector(0, 0, 0);
    this->normal = Vector(0, 0, 1); // Default facing forward
    this->width = 0;
    this->height = 0;
    calculateCorners();
}

Plane::Plane(Vector newPoint, Vector newNormal)
{
    this->point = newPoint;
    this->normal = newNormal.getNormalized();
    this->width = 0;
    this->height = 0;
    calculateCorners();
}

Plane::Plane(Vector newPoint, Vector newNormal, float width, float height)
{
    this->point = newPoint;
    this->normal = newNormal.getNormalized();
    this->width = width;
    this->height = height;
    calculateCorners();
}

Plane::~Plane() {}

void Plane::setPoint(Vector newPoint)
{
    this->point = newPoint;
    calculateCorners();
}

void Plane::setNormal(Vector newNormal)
{
    this->normal = newNormal.getNormalized();
    calculateCorners();
}

void Plane::setDimensions(float newWidth, float newHeight)
{
    this->width = newWidth;
    this->height = newHeight;
    calculateCorners();
}

Vector Plane::getPoint()
{
    return this->point;
}

Vector Plane::getNormal()
{
    return this->normal;
}

float Plane::getWidth()
{
    return this->width;
}

float Plane::getHeight()
{
    return this->height;
}

bool Plane::intersects(Vector other)
{
    Vector relativePos = other - point;
    float distanceToPlane = Vector::dot(relativePos, normal);
    if (abs(distanceToPlane) > 0.01f)
        return false;

    Vector inPlanePos = relativePos - (normal * distanceToPlane);
    Vector edge1 = corners[1] - corners[0];
    Vector edge2 = corners[3] - corners[0];

    float u = Vector::dot(inPlanePos, edge1) / (edge1.magnitude() * edge1.magnitude());
    float v = Vector::dot(inPlanePos, edge2) / (edge2.magnitude() * edge2.magnitude());

    return (u >= 0 && u <= 1 && v >= 0 && v <= 1);
}

void Plane::calculateCorners()
{
    Vector tangent1, tangent2;
    if (normal.X != 0 || normal.Y != 0)
    {
        tangent1 = Vector(-normal.Y, normal.X, 0).getNormalized();
    }
    else
    {
        tangent1 = Vector(1, 0, 0);
    }
    tangent2 = Vector::cross(normal, tangent1).getNormalized();

    Vector halfWidth = tangent1 * (width / 2.0f);
    Vector halfHeight = tangent2 * (height / 2.0f);

    corners[0] = point - halfWidth - halfHeight; // Bottom-left
    corners[1] = point + halfWidth - halfHeight; // Bottom-right
    corners[2] = point + halfWidth + halfHeight; // Top-right
    corners[3] = point - halfWidth + halfHeight; // Top-left
}
