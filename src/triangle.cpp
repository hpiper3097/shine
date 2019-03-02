#include "../include/triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(float a, float b, float c,
             float d, float e, float f,
             float g, float h, float i)
{
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    points[4] = e;
    points[5] = f;
    points[6] = g;
    points[7] = h;
    points[8] = i;
}

Triangle::Triangle(float* p)
{
    for(int i = 0; i < 9; i++)
        points[i] = p[i];
}

void Triangle::setPoints(float a, float b, float c,
             float d, float e, float f,
             float g, float h, float i)
{
    points[0] = a;
    points[1] = b;
    points[2] = c;
    points[3] = d;
    points[4] = e;
    points[5] = f;
    points[6] = g;
    points[7] = h;
    points[8] = i;
}

void Triangle::setPoints(float* p)
{
    for(int i = 0; i < 9; i++)
        points[i] = p[i];
}

float* Triangle::getPoints()
{
    return points;
}

unsigned int Triangle::getSize()
{
    return sizeof(points);
}
