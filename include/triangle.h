#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

class Triangle
{

private:

    float points[9];

public:

    Triangle(float* p);
    Triangle(float a, float b, float c,
             float d, float e, float f,
             float g, float h, float i);
    Triangle();

    void setPoints(float a, float b, float c,
             float d, float e, float f,
             float g, float h, float i);

    void setPoints(float* p);

    float* getPoints();
    unsigned int getSize();

};

#endif
