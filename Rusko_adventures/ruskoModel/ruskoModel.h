//
//  ruskoModel.h
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/9/13.
//
//
//
// ruskoModel.h
// Rusko_adventures
//
// Created by Pamela Martinez on 6/9/13.
//
//

#ifndef __Rusko_adventures__ruskoModel__
#define __Rusko_adventures__ruskoModel__

#include <iostream>
#include "Framework.h"
#include "Renderable.h"


//include material,mesh,obj for ruskoModel
#include "material.h"
#include "mesh.h"
#include "obj.h"

// The ruskoModel class

class ruskoModel : Renderable
{
public:
    ruskoModel();
    ruskoModel(const std::string &path);
    ruskoModel(const std::string &path, float scale);
    ruskoModel(const std::string &path, STPoint3 centerMass, float maxLength); //flag to use fitSphere with offset
    
    virtual ~ruskoModel();
    
    void render();
    STPoint3 getCenterPoint();
    
    STPoint3 getCenterMass();
    float getMaxLength();
    
    BBox bbox;
    BCir bcir;
    bool started;
    
private:
    void fitSphere(float scale);
    void fitSphere_withOffset(float scale, STPoint3 centerMass, float maxLength);
    
    BBox findBBox();
    
    STPoint3 centerPoint;
    STPoint3 centerMass;
    float scaleLength;
    
    mesh* Mesh;
    
    //mesh materials
    typedef map<string, material> MaterialList;
    MaterialList materials_;
    
    //mesh components
    vector<STPoint3>* vertices;
    vector<STPoint3>* vertices_n;
    vector<STPoint2>* vertices_t;
    
    vector<STPoint3>* faces;
    vector<STPoint3>* faces_vn;
    vector<STPoint3>* faces_vt;
    
    vector<string>* matNames;
    vector<int>* faces_mt;
    
};

#endif /* defined(__Rusko_adventures__ruskoModel__) */