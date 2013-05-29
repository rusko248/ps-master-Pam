//
//  Quaternion.cpp
//  assignment2
//
//  Created by Aaron Damashek on 4/22/13.
//
//

#include "Quaternion.h"

Quaternion Quaternion::operator+ (Quaternion quat) {
    Quaternion temp(W + quat.W, X + quat.X, Y + quat.Y, Z + quat.Z);
    return temp;
}

Quaternion Quaternion::operator* (float mult) {
    Quaternion temp(W*mult, X*mult, Y*mult, Z*mult);
    return temp;
}

void Quaternion::Normalize(){
    float mag2 = W*W + X*X + Y*Y + Z*Z;
	if (fabs(mag2) > 0.001f && fabs(mag2 - 1.0f) > 0.001f) {
		float mag = sqrt(mag2);
		W /= mag;
		X /= mag;
		Y /= mag;
		Z /= mag;
	}

}

Quaternion::Quaternion(float w, float x, float y, float z){
    W = w;
    X = x;
    Y = y;
    Z = z;
}

Quaternion::Quaternion(float pitch, float yaw, float roll)
{
	// Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
	// and multiply those together.
	// the calculation below does the same, just shorter
    float pi = 3.1459;
	float p = pitch * pi / 360;
	float y = yaw * pi/ 360;
	float r = roll * pi / 360;
    
	float sinp = sin(p);
	float siny = sin(y);
	float sinr = sin(r);
	float cosp = cos(p);
	float cosy = cos(y);
	float cosr = cos(r);
    
	X = sinr * cosp * cosy - cosr * sinp * siny;
	Y = cosr * sinp * cosy + sinr * cosp * siny;
	Z = cosr * cosp * siny - sinr * sinp * cosy;
	W = cosr * cosp * cosy + sinr * sinp * siny;
    
}

Quaternion::Quaternion(float rotationAngle, STVector3 rotationAxis){
    float halfAngle = rotationAngle/2;
    float sinHalf = sinf(halfAngle);
    rotationAxis.Normalize();
    W = cosf(sinHalf);
    X = rotationAxis.x * sinHalf;
	Y = rotationAxis.y * sinHalf;
	Z = rotationAxis.z * sinHalf;
}

Quaternion Quaternion::negate(Quaternion quat){
    return Quaternion(-quat.W, -quat.X, -quat.Y, -quat.Z);
}

Quaternion Quaternion::conjugate(Quaternion quat){
    return Quaternion(quat.W, -quat.X, -quat.Y, -quat.Z);
}

float Quaternion::dotProduct(Quaternion quatOne, Quaternion quatTwo){
    float dotProduct = quatOne.W*quatTwo.W + quatOne.X*quatTwo.X + quatOne.Y*quatTwo.Y + quatOne.Z*quatTwo.Z;
    return dotProduct;
}

Quaternion Quaternion::crossProduct(Quaternion quatOne, Quaternion quatTwo){
    float w = quatOne.W*quatTwo.W - quatOne.X*quatTwo.X - quatOne.Y*quatTwo.Y - quatOne.Z*quatTwo.Z;
    float x = quatOne.W*quatTwo.X + quatOne.X*quatTwo.W + quatOne.Y*quatTwo.Z - quatOne.Z*quatTwo.Y;
    float y = quatOne.W*quatTwo.Y - quatOne.X*quatTwo.Z + quatOne.Y*quatTwo.W + quatOne.Z*quatTwo.X;
    float z = quatOne.W*quatTwo.Z + quatOne.X*quatTwo.Y - quatOne.Y*quatTwo.X + quatOne.Z*quatTwo.W;
    Quaternion crossP = Quaternion(w,x,y,z);
    return crossP;
}

STVector3 Quaternion::rotate(STVector3 vect, Quaternion rotation){
    Quaternion vecQuat = Quaternion(0, vect.x, vect.y, vect.z);
    Quaternion rotatedQuat = crossProduct(crossProduct(rotation, vecQuat), conjugate(rotation));
    return STVector3(rotatedQuat.X, rotatedQuat.Y, rotatedQuat.Z);
}

Quaternion Quaternion::Slerp(Quaternion one, Quaternion two, float t){
    one.Normalize();
    two.Normalize();
    float angle = acosf(dotProduct(one, two));
    Quaternion slerp = one*(sinf((1-t)*angle)/sinf(angle)) + two*(sinf(t*angle)/sinf(angle));
    return slerp;
}

Quaternion Quaternion::identity(){
    return Quaternion(1,0,0,0);
}

Matrix Quaternion::rotationMatrix(Quaternion quat){
    Matrix rotation;
    rotation.matrix[0] = 1 - 2*pow(Y,2) - 2*pow(Z,2);
    rotation.matrix[1] = 2*X*Y - 2*W*Z;
    rotation.matrix[2] = 2*X*Z + 2*W*Y;
    rotation.matrix[3] = 0;
    rotation.matrix[4] = 2*X*Y + 2*W*Z;
    rotation.matrix[5] = 1 - 2*pow(X,2) - 2*pow(Z,2);
    rotation.matrix[6] = 2*Y*Z - 2*W*X;
    rotation.matrix[7] = 0;
    rotation.matrix[8] = 2*X*Z - 2*W*Y;
    rotation.matrix[9] = 2*W*X + 2*Y*Z;
    rotation.matrix[10] = 1 - 2*pow(X,2) - 2*pow(Y,2);
    rotation.matrix[11] = 0;
    rotation.matrix[12] = 0;
    rotation.matrix[13] = 0;
    rotation.matrix[14] = 0;
    rotation.matrix[15] = 1;
    return rotation;
}