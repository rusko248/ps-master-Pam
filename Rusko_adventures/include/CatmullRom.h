//
//  CatmullRom.h
//  CatmullSpline
//
//  Created by Pamela Martinez on 4/24/13.
//
//

#ifndef __CatmullSpline__CatmullRom__
#define __CatmullSpline__CatmullRom__

#include <iostream>

/** makes sure code is platform independent **/
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif

#include "st.h"
#include <vector>

using namespace std;

class CatmullRom
{
    
public:
	CatmullRom();
    CatmullRom(string filename); //automatically makes all points with increment of .1
    void done();
    
    void readFile(string filename);
    
    void addControlPoint(float x, float y, float z);
    
    //finds point at given interval, where 0<=u<=1
    //the i interval has to be i<numControlPoints-1
    STPoint3 curveAt(float u, int i);
   
    //stores number of control points in catmull-rom
    int numControlPoints;

    //stores total number of sections for catmull-rom
    STPoint3 pointAt(int i);
    int totalPoints;
    
private:
    void createAllPoints();
    vector<STPoint3>* allPoints;

    
    void newSegment(int i); //determines segment between point p(i) and p(i+1)
    vector<STPoint3>* controlPoints; //stores all vertices
    int segmentNum;
    STVector3 c0, c1, c2, c3;
    
};



#endif /* defined(__CatmullSpline__CatmullRom__) */
