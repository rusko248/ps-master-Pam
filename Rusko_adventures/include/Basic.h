//
//  Basic.h
//  assignment2
//
//  Created by Aaron Damashek on 5/8/13.
//
//

#ifndef assignment2_Basic_h
#define assignment2_Basic_h

struct vector3 {
    float x;
    float y;
    float z;
    
    vector3(){};
    vector3(float x, float y, float z) : x(x), y(y), z(z) { };
    vector3 operator + (const vector3 &p)  const { return vector3(x+p.x, y+p.y, z + p.z); }
    vector3 operator - (const vector3 &p)  const { return vector3(x-p.x, y-p.y, y - p.z); }
    vector3 operator * (double c)     const { return vector3(x*c, y*c, z*c); }
};

#endif
