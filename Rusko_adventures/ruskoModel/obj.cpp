//
//  obj.cpp
//  Metamorphosis
//
//  Created by Pamela Martinez on 4/7/13.
//
//

#include "obj.h"
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string>


using namespace std;

obj::obj(std::string _filename)
{
    objMesh = new mesh();
    vertexNormals = 0;
    
    {
#if defined(WIN32)
        std::string::size_type dot = _filename.find_last_of("\\/");
#else
        std::string::size_type dot = _filename.rfind("/");
#endif
        path_ = (dot == std::string::npos)
        ? "./"
        : std::string(_filename.substr(0,dot+1));
    }
    
    
	Parse(_filename);
    
    
}


void obj::Parse(std::string _filename)
{
    
	std::ifstream objFile(_filename.c_str());
    
	// Die if we couldn't find the file
	if (objFile.fail())
	{
		printf("obj::Parse - Could not find input obj file '%s'\n", _filename.c_str());
		exit(1);
	}
    
	char line[1024];
	while (!objFile.eof())
	{
		objFile.getline(line, 1023);
		std::stringstream ss;
		ss.str(line);
		std::string command;
		ss >> command;
        
        
		if (command == "v")
		{
			float vx, vy, vz;
			ss >> vx >> vy >> vz;
            objMesh->addVertex(vx, vy, vz);
		}
        
        if (command == "vt")
        {
            float vt1, vt2;
            ss >> vt1 >> vt2;
            objMesh->addVertex_t(vt1, vt2);
        }
        
        
        if (command == "vn")
        {
            float vn1, vn2, vn3;
            ss >> vn1 >> vn2 >> vn3;
            objMesh->addVertex_n(vn1, vn2, vn3);
            vertexNormals++;
        }
        
        if (command == "f")
        {
            int v1a, v2a, v3a;
            int v1b, v2b, v3b;
            int v1c, v2c, v3c;
            string lin;
            lin = string(line);
           
            //finds v1a v2a v3a
            int ind = lin.find('/');
            if (ind == string::npos){
                int v1, v2, v3;
                ss >> v1 >> v2 >> v3;
                objMesh->addFace(v1, v2, v3);
            }
            else {
                string temp = lin.substr(2, ind-2);
                v1a = atoi(temp.c_str());
                
                lin = lin.substr(ind+1);
                ind = lin.find('/');
                temp = lin.substr(0, ind);
                v2a = atoi(temp.c_str());
                
                lin = lin.substr(ind+1);
                ind = lin.find(' ');
                temp = lin.substr(0, ind);
                v3a = atoi(temp.c_str());
                
                
                //finds v1b v2b v3b
                lin = lin.substr(ind+1);
                ind = lin.find('/');
                temp = lin.substr(0, ind);
                v1b = atoi(temp.c_str());
                
                lin = lin.substr(ind+1);
                ind = lin.find('/');
                temp = lin.substr(0, ind);
                v2b = atoi(temp.c_str());
                
                lin = lin.substr(ind+1);
                ind = lin.find(' ');
                temp = lin.substr(0, ind);
                v3b = atoi(temp.c_str());
                
                
                //finds v1c v2c v3c
                lin = lin.substr(ind+1);
                ind = lin.find('/');
                temp = lin.substr(0, ind);
                v1c = atoi(temp.c_str());
                
                lin = lin.substr(ind+1);
                ind = lin.find('/');
                temp = lin.substr(0, ind);
                v2c = atoi(temp.c_str());
                
                lin = lin.substr(ind+1);
                ind = lin.find(' ');
                temp = lin.substr(0, ind);
                v3c = atoi(temp.c_str());
                
                objMesh->addFace(v1a, v1b, v1c);
                objMesh->addFace_vt(v2a, v2b, v2c);
                objMesh->addFace_vn(v3a, v3b, v3c);
            }
        }
        // usemtl
        else if (command == "usemtl")
        {
            string matname;
            ss >> matname;
            if (objMesh->materials_.find(matname)==objMesh->materials_.end())
            {
                cout << "Warning! Material '" << matname << "' not defined in material file.\n";
                matname="";
            }
            else {
                int currFace = objMesh->numFaces;
                objMesh->addMatName(matname, currFace);

                //objMesh->addFace(0, 0, 0);
            }

        }

        else if (command == "mtllib")
        {
            std::string matFile;
            
            // Get the rest of the line, removing leading or trailing spaces
            // This will define the filename of the texture
            std::getline(ss,matFile);
            trimString(matFile);
            
            matFile = path_ + matFile;
            
            std::fstream matStream( matFile.c_str(), std::ios_base::in );
            
            if ( matStream ){
                
                if ( !readMaterial( matStream ) )
                    cout << "  Warning! Could not read file properly!\n";
                matStream.close();
                
            }
        }
 
	}
	objFile.close();
    
    FinishedParsing();
}



void obj::FinishedParsing()
{
    //this means we had no vertex Normal info, and have to define our own
    if (vertexNormals == 0) {
        
       // printf("we're in trouble");
        
        vector<STPoint3>* vertices = objMesh->getVertices();        
        vector<STPoint3>* faces = objMesh->getFaces();
        
        //creates the normals for vertices
        objMesh->makeNormals();
        
        //saves the face normal for each vertex
        for (int i=0; i < faces->size(); i++){
            STPoint3 fac = faces->at(i);
            
            STPoint3 v1 = vertices->at((int)fac.x);
            STPoint3 v2 = vertices->at((int)fac.y);
            STPoint3 v3 = vertices->at((int)fac.z);
            
            STVector3 faceNormal = STVector3::Cross(STVector3(v1-v2), STVector3(v1-v3));
            faceNormal.Normalize();
            
            objMesh->addFaceNormal(faceNormal, (int)fac.x);
            objMesh->addFaceNormal(faceNormal, (int)fac.y);
            objMesh->addFaceNormal(faceNormal, (int)fac.z);
            
            objMesh->addFace_vn((int)fac.x+1, (int)fac.y+1, (int)fac.z+1);
        }
        
        //goes through each vertex and averages its face normals, to calculate vertex normals
        for (int i=0; i < vertices->size(); i++){
            vector<STVector3>* vNormals = objMesh->getVNormals(i);
            
            STVector3 vertexNormal = STVector3(0, 0, 0);
            int totalVN = vNormals->size();
            for (int j=0; j < totalVN; j++){
                vertexNormal += vNormals->at(j);
            }
            
            vertexNormal = vertexNormal/totalVN;
            objMesh->addVertex_n(vertexNormal.x, vertexNormal.y, vertexNormal.z);
        }
    }
    
}


mesh* obj::getMesh(){
    return objMesh;
}


bool obj::readMaterial(fstream& _in){
    
    
    std::string line;
    std::string keyWrd;
    std::string textureName;
    
    std::string key;
    material    mat;
    float       f1,f2,f3;
    bool        indef = false;
    int         textureId = 1;
    
    
    objMesh->materials_.clear();
    mat.cleanup();
    
    while( _in && !_in.eof() )
    {
        std::getline(_in,line);
        if ( _in.bad() ){
            cout << "  Warning! Could not read file properly!\n";
            return false;
        }
        
        if ( line.empty() )
            continue;
        
        std::stringstream stream(line);
        
        stream >> keyWrd;
        
        if( ( isspace(line[0]) && line[0] != '\t' ) || line[0] == '#' )
        {
            if (indef && !key.empty() && mat.is_valid())
            {
                objMesh->materials_[key] = mat;
                mat.cleanup();
            }
        }
        
        else if (keyWrd == "newmtl") // begin new material definition
        {
            stream >> key;
            indef = true;
        }
        
        else if (keyWrd == "Kd") // diffuse color
        {
            stream >> f1; stream >> f2; stream >> f3;
            
            if( !stream.fail() )
                mat.set_Kd(f1,f2,f3);
        }
        
        else if (keyWrd == "Ka") // ambient color
        {
            stream >> f1; stream >> f2; stream >> f3;
            
            if( !stream.fail() )
                mat.set_Ka(f1,f2,f3);
        }
        
        else if (keyWrd == "Ks") // specular color
        {
            stream >> f1; stream >> f2; stream >> f3;
            
            if( !stream.fail() )
                mat.set_Ks(f1,f2,f3);
        }
#if 0
        else if (keyWrd == "illum") // diffuse/specular shading model
        {
            ; // just skip this
        }
        
        else if (keyWrd == "Ns") // Shininess [0..200]
        {
            ; // just skip this
        }
        
        else if (keyWrd == "map_") // map images
        {
            // map_Ks, specular map
            // map_Ka, ambient map
            // map_Bump, bump map
            // map_d,  opacity map
            ; // just skip this
        }
#endif
        else if (keyWrd == "map_Kd" ) {
            // Get the rest of the line, removing leading or trailing spaces
            // This will define the filename of the texture
            std::getline(stream,textureName);
            trimString(textureName);
            if ( ! textureName.empty() )
                mat.set_map_Kd( textureName, textureId++ );
        }
        else if (keyWrd == "Tr") // transparency value
        {
            stream >> f1;
            
            if( !stream.fail() )
                mat.set_Tr(f1);
        }
        else if (keyWrd == "d") // transparency value
        {
            stream >> f1;
            
            if( !stream.fail() )
                mat.set_Tr(f1);
        }
        
        if ( _in && indef && mat.is_valid() && !key.empty())
            objMesh->materials_[key] = mat;
    }
    return true;
}
    

void obj::trimString(string& _string) {
        // Trim Both leading and trailing spaces
        
        size_t start = _string.find_first_not_of(" \t\r\n");
        size_t end   = _string.find_last_not_of(" \t\r\n");
        
        if(( std::string::npos == start ) || ( std::string::npos == end))
            _string = "";
        else
            _string = _string.substr( start, end-start+1 );
}
