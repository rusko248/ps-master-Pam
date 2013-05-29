//
//  Quaternion.h
//  assignment2
//
//  Created by Aaron Damashek on 4/22/13.
//
//

#ifndef __assignment2__Quaternion__
#define __assignment2__Quaternion__

#include <iostream>
#include "st.h"
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct Matrix
{
    float matrix[16];
} Matrix;

static const Matrix IDENTITY_MATRIX = { {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
} };


class Quaternion
{
public:
	Quaternion(float w, float x, float y, float z);
    Quaternion(float rotationAngle, STVector3 rotationAxis);
    Quaternion(float pitch, float yaw, float roll);
    Quaternion negate(Quaternion quat);
    Quaternion conjugate(Quaternion quat);
    Quaternion crossProduct(Quaternion quatOne, Quaternion quatTwo);
    float dotProduct(Quaternion quatOne, Quaternion quatTwo);
    STVector3 rotate(STVector3 vect, Quaternion rotation);
    Quaternion Slerp(Quaternion one, Quaternion two, float t);
    Quaternion identity();
    Matrix rotationMatrix(Quaternion quat);
    void Normalize();
    float W;
    float X;
    float Y;
    float Z;
    Quaternion operator + (Quaternion);
    Quaternion operator * (float);
private:

    
};
#endif /* defined(__assignment2__Quaternion__) */
