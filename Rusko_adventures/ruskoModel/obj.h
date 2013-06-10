//
//  obj.h
//  Metamorphosis
//
//  Created by Pamela Martinez on 4/7/13.
//
//

#ifndef __Metamorphosis__obj__
#define __Metamorphosis__obj__

#include <iostream>
#include "st.h"
#include "mesh.h"
#include "material.h"
#include <map>


using namespace std;

class obj
{
    
public:
	obj(std::string _filename);
    mesh* getMesh();
    
private:

	/** Parsing helpers **/
	void Parse(std::string _filename);
	void FinishedParsing();
    
    /**stores the mesh**/
    mesh* objMesh;
    int vertexNormals;
    
    bool readMaterial(fstream& _in);
    void trimString(string& _string);
    
    string path_;
    
};


#endif /* defined(__Metamorphosis__obj__) */
