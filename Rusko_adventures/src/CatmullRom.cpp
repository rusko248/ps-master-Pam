//
//  CatmullRom.cpp
//  CatmullSpline
//
//  Created by Pamela Martinez on 4/24/13.
//
//

#include "CatmullRom.h"
#include <fstream>
#include <sstream>
#include <math.h>


CatmullRom::CatmullRom(){
    segmentNum = -1;
    numControlPoints = 0;
    controlPoints = new vector<STPoint3>();
}


void CatmullRom::readFile(string filename)
{
    std::ifstream file(filename.c_str());
    
	// Die if we couldn't find the file
	if (file.fail())
	{
		printf("obj::Parse - Could not find input obj file '%s'\n", filename.c_str());
		exit(1);
	}
    
	char line[1024];
	while (!file.eof())
	{
		file.getline(line, 1023);
		std::stringstream ss;
		ss.str(line);
		std::string command;
		ss >> command;
        
        
		if (command == "cp")
		{
			float vx, vy, vz;
			ss >> vx >> vy >> vz;
            addControlPoint(vx, vy, vz);
		}
	}
	file.close();
}


void CatmullRom::addControlPoint(float x, float y, float z)
{
    controlPoints->push_back(STPoint3(x, y, z));
    numControlPoints++;
}


void CatmullRom::newSegment(int i){
    segmentNum = i;
    
    if (i+1 >= numControlPoints){
        printf("problem!! asked for segment for an index out of bounds");
        exit(0);
    }
        
    STVector3 p_neg, p_i, p_i1, p_i2;
    if (i >= 1) p_neg = STVector3(controlPoints->at(i-1));
    p_i = STVector3(controlPoints->at(i));
    p_i1 = STVector3(controlPoints->at(i+1));
    
    if (i+2 < numControlPoints) p_i2 = STVector3(controlPoints->at(i+2));
    else {
      p_i2 = STVector3(p_i1.x + (p_i1.x - p_i.x), p_i1.y + (p_i1.y - p_i.y), p_i1.z + (p_i1.z - p_i.z));
    }
    
    //checks for endpoints
    //if this is first segment
    if (i < 1) {
      p_neg = STVector3(p_i.x - (p_i1.x - p_i.x), p_i.y - (p_i1.y - p_i.y), p_i.z - (p_i1.z - p_i.z));
    }
    
    c0 = p_i;
    c1 = (p_i1-p_neg)/2;
    c2 = p_neg + (((float)-5/2)*p_i) + (2*p_i1) + (((float)-1/2)*(p_i2));
    c3 = (((float)-1/2)*p_neg) + (((float)3/2)*p_i) + (((float)-3/2)*p_i1) + (((float)1/2)*p_i2);
}


STPoint3 CatmullRom::curveAt(float u, int i)
{
    if (segmentNum != i) {
        newSegment(i);
    }
    
    STPoint3 fu;
    
    if (i+1 >= numControlPoints || u > 1){
        printf("problem!! called with an index out of bounds");
        exit(0);
    }
    
    fu = STPoint3(c0 + c1*u + c2*((float)pow(u, 2)) + c3*((float)pow(u, 3)));
    return fu;
}
