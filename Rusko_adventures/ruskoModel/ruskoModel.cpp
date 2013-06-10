//
//  ruskoModel.cpp
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/9/13.
//
//

#include "ruskoModel.h"

#define NOMINMAX
#define _USE_MATH_DEFINES

using namespace std;

ruskoModel::ruskoModel() {
    started = true;
}

ruskoModel::ruskoModel(const std::string &path) {
    started = true;
    obj* object = new obj(path);
    Mesh = object->getMesh();
    materials_ = Mesh->materials_;
    
    //mesh components
    vertices = Mesh->getVertices();
    vertices_n = Mesh->getVertices_n();
    faces = Mesh->getFaces();
    faces_vn = Mesh->getFaces_vn();
    matNames = Mesh->getMatNames();
    faces_mt = Mesh->getFaces_mt();
    faces_vt = Mesh->getFaces_vt();
    vertices_t = Mesh->getVertices_t();
    
    //fit into a sphere
	fitSphere(1.0);
    
	bbox = findBBox();
	bcir.x = bcir.y = bcir.z = 0.f;
	bcir.radius = 1.0;

}

ruskoModel::ruskoModel(const std::string &path, float scale) {
    started = true;

    obj* object = new obj(path);
    Mesh = object->getMesh();
    materials_ = Mesh->materials_;
    
    //mesh components
    vertices = Mesh->getVertices();
    vertices_n = Mesh->getVertices_n();
    faces = Mesh->getFaces();
    faces_vn = Mesh->getFaces_vn();
    matNames = Mesh->getMatNames();
    faces_mt = Mesh->getFaces_mt();
    faces_vt = Mesh->getFaces_vt();
    vertices_t = Mesh->getVertices_t();


    //fit into a sphere
	fitSphere(scale);
    
	bbox = findBBox();
	bcir.x = bcir.y = bcir.z = 0.f;
	bcir.radius = scale;
}


ruskoModel::ruskoModel(const std::string &path, STPoint3 centerMass, float maxLength) {
	
    obj* object = new obj(path);
    Mesh = object->getMesh();
    materials_ = Mesh->materials_;
    
    //mesh components
    vertices = Mesh->getVertices();
    vertices_n = Mesh->getVertices_n();
    faces = Mesh->getFaces();
    faces_vn = Mesh->getFaces_vn();
    matNames = Mesh->getMatNames();
    faces_mt = Mesh->getFaces_mt();
    
	fitSphere_withOffset(1.f, centerMass, maxLength);
    
	bbox = findBBox();
}

ruskoModel::~ruskoModel() {
	
}

STPoint3 ruskoModel::getCenterPoint(){
    return centerPoint;
}

void ruskoModel::render() {
    float materialAmbient[]  = { 0.8, 0.8, 0.2, 1.0 };
    float materialDiffuse[]  = { 0.8, 0.8, 0.2, 1.0 };
    float materialSpecular[] = { 0.4, 0.4, 0.4, 1.0 };
    float shininess          = 8.0;
    
    int mt_count = 0;
    int mt = faces_mt->at(mt_count);
    
    
	glDepthRange(0.001,1);
	glEnable(GL_NORMALIZE);
    
	for (int i=0; i < faces->size(); i++) {
        STPoint3 fac = faces->at(i);
        STPoint3 fac_vn = faces_vn->at(i);
        STPoint3 fac_vt = faces_vt->at(i);
        
        STPoint3 v1 = vertices->at((int)fac.x);
        STPoint3 v2 = vertices->at((int)fac.y);
        STPoint3 v3 = vertices->at((int)fac.z);
        
        STPoint3 vn1 = vertices_n->at((int)fac_vn.x);
        STPoint3 vn2 = vertices_n->at((int)fac_vn.y);
        STPoint3 vn3 = vertices_n->at((int)fac_vn.z);
        
        STPoint2 vt1 = STPoint2(0, 0);// = vertices_t->at((int)fac_vt.x);
        STPoint2 vt2 = STPoint2(0, 0);// = vertices_t->at((int)fac_vt.y);
        STPoint2 vt3 = STPoint2(0, 0);// = vertices_t->at((int)fac_vt.z);
        if (vertices_t->size() > 0){
            vt1 = vertices_t->at((int)fac_vt.x);
            vt2 = vertices_t->at((int)fac_vt.y);
            vt3 = vertices_t->at((int)fac_vt.z);
        }

        
        if ( i == mt) {
            string matName = matNames->at(mt_count);
            
            material currentMat = materials_.at(matName);
            float alpha = 1.0;
            
            if (currentMat.has_Tr()){
                alpha = currentMat.Tr();
            }
            
            if (currentMat.has_Ka()) {
                STVector3 color = currentMat.Ka();
                materialAmbient[0]  = color.x;
                materialAmbient[1]  = color.y;
                materialAmbient[2]  = color.z;
            }
            if (currentMat.has_Kd()) {
                STVector3 color = currentMat.Kd();
                materialDiffuse[0]  = color.x;
                materialDiffuse[1]  = color.y;
                materialDiffuse[2]  = color.z;
            }
            if (currentMat.has_Ks()) {
                STVector3 color = currentMat.Ks();
                materialSpecular[0]  = color.x;
                materialSpecular[1]  = color.y;
                materialSpecular[2]  = color.z;
            }
            
            glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
            glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
            
            
            if (mt_count < faces_mt->size()-1) {
                mt_count++;
                mt = faces_mt->at(mt_count);
            }
            
        }


		glBegin(GL_TRIANGLES);
        glNormal3f(vn1.x, vn1.y, vn1.z);
        glTexCoord2f(vt1.x,vt1.y);
        glVertex3f(v1.x,v1.y,v1.z);
        
        glNormal3f(vn2.x, vn2.y, vn2.z);
        glTexCoord2f(vt2.x,vt2.y);
        glVertex3f(v2.x,v2.y,v2.z);

        glNormal3f(vn3.x, vn3.y, vn3.z);
        glTexCoord2f(vt3.x,vt3.y);
        glVertex3f(v3.x,v3.y,v3.z);
		glEnd();
	}
	
	glDepthRange(0,1);
}

void ruskoModel::fitSphere(float scale) {
	// Move center of mass to origin
	STVector3 cm(0,0,0);
	for (int i = 0; i < vertices->size(); i++) cm += STVector3(vertices->at(i));
    cm /= vertices->size();
    
	for (int i = 0; i < vertices->size(); i++) {
      vertices->at(i) = STPoint3(STVector3(vertices->at(i))-cm);
    }
    
    centerMass = STPoint3(cm.x, cm.y, cm.z);
    
	// Fit in the unit sphere
	float maxLength = 0;
	for (int i = 0; i < vertices->size(); i++) {
        maxLength = max(maxLength, STVector3(vertices->at(i)).Length());
    }
    scaleLength = maxLength;
    
	for (int i = 0; i < vertices->size(); i++) {
       vertices->at(i) = STPoint3(STVector3(vertices->at(i)) * (scale / maxLength));
    }
}



void ruskoModel::fitSphere_withOffset(float scale, STPoint3 centerMass, float maxLength) {
	// Move center of mass to origin
	STVector3 cm(centerMass.x, centerMass.y, centerMass.z);
	for (int i = 0; i < vertices->size(); i++) {
        vertices->at(i) = STPoint3(STVector3(vertices->at(i))-cm);
    }
    
	// Fit in the unit sphere
	for (int i = 0; i < vertices->size(); i++) {
        vertices->at(i) = STPoint3(STVector3(vertices->at(i)) * (scale / maxLength));
    }
    
    
    cm = STVector3(0, 0, 0);
    for (int i = 0; i < vertices->size(); i++) cm += STVector3(vertices->at(i));
	cm /= vertices->size();
    
    centerPoint = STPoint3(cm.x, cm.y, cm.z);
}


BBox ruskoModel::findBBox() {
	float minx, miny, minz; minx = miny = minz = 10000.0f;
	float maxx, maxy, maxz; maxx = maxy = maxz = 0.0f;
    
	for (int i = 0; i < vertices->size(); i++) {
		STVector3 v = STVector3(vertices->at(i));
		minx = min(v.x, minx); miny = min(v.y, miny); minz = min(v.z, minz);
		maxx = max(v.x, maxx); maxy = max(v.y, maxy); maxz = max(v.z, maxz);
	}
    
	BBox ret = BBox();
	ret.minx = minx; ret.miny = miny; ret.minz = minz;
	ret.maxx = maxx; ret.maxy = maxy; ret.maxz = maxz;
    
	return ret;
}


STPoint3 ruskoModel::getCenterMass(){
    return centerMass;
}

float ruskoModel::getMaxLength(){
    return scaleLength;
}