//
//  mesh.h
//  Metamorphosis
//
//  Created by Pamela Martinez on 4/7/13.
//
//

#ifndef __Metamorphosis__mesh__
#define __Metamorphosis__mesh__

#include <iostream>
#include <map>
#include "st.h"
#include <vector>
#include "material.h"


using namespace std;

class mesh
{
    
public:
	mesh();
    void addVertex(float vx, float vy, float vz);
    void addVertex_t(float vx, float vy);
    void addVertex_n(float vx, float vy, float vz);

    void addFace(int v1, int v2, int v3);
    void addFace_vt(int v1, int v2, int v3);
    void addFace_vn(int v1, int v2, int v3);
    
    void addMatName(string matName, int currFace);
        
    vector<STPoint3>* getVertices();
    vector<STPoint2>* getVertices_t();
    vector<STPoint3>* getVertices_n();
    
    vector<STPoint3>* getFaces();
    vector<STPoint3>* getFaces_vt();
    vector<STPoint3>* getFaces_vn();
    
    vector<string>* getMatNames();
    vector<int>* getFaces_mt();

    //functions to help figure out vertex normals
    void makeNormals();
    void addFaceNormal(STVector3 fNormal, int v);
    vector<STVector3>* getVNormals(int v);

    
    int sizeVertices();
    int sizeFaces();
    
    //bounding box for model
    float maxx, minx, maxy, miny, maxz, minz;

    
    typedef map<string, material> MaterialList;
    MaterialList materials_;
    
    int numFaces;

    
private:
    typedef struct Vertex {
        vector<STVector3>* faceNormals;
    } Vertex;
    
    vector<Vertex*>* normals;  //stores face normals for each vertex

    
    int numVertices;
    
    vector<STPoint3>* vertices; //stores all vertices
    vector<STPoint2>* vertices_t; //stores all vertices
    vector<STPoint3>* vertices_n; //stores all vertices

    vector<STPoint3>* faces; //stores all faces with materials... a flag of 0/-1 indicates change of material
    vector<STPoint3>* faces_vt; //stores all face texture coordinates
    vector<STPoint3>* faces_vn; //stores all face normal coordinates
    
    vector<int>* faces_mat; //stores index to materialNames
    vector<string>* materialNames;
};


#endif /* defined(__Metamorphosis__mesh__) */
