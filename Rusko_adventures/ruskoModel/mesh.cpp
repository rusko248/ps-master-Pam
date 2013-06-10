//
//  mesh.cpp
//  Metamorphosis
//
//  Created by Pamela Martinez on 4/7/13.
//
//

#include "mesh.h"

mesh::mesh(){
    numFaces = 0;
    numVertices = 0;
    
    vertices = new vector<STPoint3>();
    vertices_t = new vector<STPoint2>();
    vertices_n = new vector<STPoint3>();

    normals = new vector<Vertex*>();  //stores face normals for each vertex

    faces = new vector<STPoint3>();
    faces_vt = new vector<STPoint3>();
    faces_vn = new vector<STPoint3>();
    
    faces_mat = new vector<int>();
    materialNames = new vector<string>();

    
    maxx = minx = maxy = miny = maxz = minz = 0;
}


void mesh::addVertex(float vx, float vy, float vz)
{
    vertices->push_back(STPoint3(vx, vy, vz));
    
    //checks to pick max/min
    if (vx > maxx) maxx = vx;
    if (vx < minx) minx = vx;
    if (vy > maxy) maxy = vy;
    if (vy < miny) miny = vy;
    if (vz > maxz) maxz = vz;
    if (vz < minz) minz = vz;
    
    numVertices++;
}

void mesh::addVertex_t(float vx, float vy)
{
    vertices_t->push_back(STPoint2(vx, vy));
}

void mesh::addVertex_n(float vx, float vy, float vz)
{
    vertices_n->push_back(STPoint3(vx, vy, vz));
}

void mesh::addFace(int v1, int v2, int v3)
{
    faces->push_back(STPoint3(v1-1, v2-1, v3-1));
    numFaces++;
}

void mesh::addFace_vt(int v1, int v2, int v3)
{
    faces_vt->push_back(STPoint3(v1-1, v2-1, v3-1));
}

void mesh::addFace_vn(int v1, int v2, int v3)
{
    faces_vn->push_back(STPoint3(v1-1, v2-1, v3-1));
}

void mesh::addMatName(string matName, int currFace)
{
    materialNames->push_back(matName);
    faces_mat->push_back(currFace);
}


vector<STPoint3>* mesh::getVertices(){
    return vertices;
}

vector<STPoint2>* mesh::getVertices_t(){
    return vertices_t;
}

vector<STPoint3>* mesh::getVertices_n(){
    return vertices_n;
}


void mesh::makeNormals(){
    for (int i = 0; i < numVertices; i++){
        Vertex* vx = (Vertex*)malloc(sizeof(Vertex));
        vector<STVector3>* faceNormals = new vector<STVector3>();
        vx->faceNormals = faceNormals;
        normals->push_back(vx);
    }
}

void mesh::addFaceNormal(STVector3 fNormal, int v){
    Vertex* vStruct = normals->at(v);
    vector<STVector3>* vNormals = vStruct->faceNormals;
    vNormals->push_back(fNormal);
}

vector<STVector3>* mesh::getVNormals(int v){
    Vertex* vStruct = normals->at(v);
    vector<STVector3>* vNormals = vStruct->faceNormals;
    return vNormals;
}


vector<STPoint3>* mesh::getFaces(){
    return faces;
}

vector<STPoint3>* mesh::getFaces_vt(){
    return faces_vt;
}

vector<STPoint3>* mesh::getFaces_vn(){
    return faces_vn;
}

vector<string>* mesh::getMatNames(){
    return materialNames;
}
vector<int>* mesh::getFaces_mt(){
    return faces_mat;
}


int mesh::sizeVertices(){
    return numVertices;
}

int mesh::sizeFaces(){
    return numFaces;
}

