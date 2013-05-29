#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Model.h"

using namespace std;
using namespace OpenMesh;

Model::Model() {
}

Model::Model(const std::string &path) {
	IO::Options opt;
	opt += IO::Options::VertexNormal;
	opt += IO::Options::FaceNormal;

	Mesh mesh;
	
	mesh.request_face_normals();
	mesh.request_vertex_normals();
	mesh.request_vertex_colors();
	mesh.request_vertex_texcoords2D();
    
	
	if ( !IO::read_mesh(mesh, path, opt )) {
		printf("Cannot load mesh from %s\n", path.c_str());
		exit(1);
	}
	
	mesh.update_normals();

	meshes.push_back(mesh);
}

Model::~Model() {
	
}

void Model::addMesh(const std::string &path) {
	IO::Options opt;
	opt += IO::Options::VertexNormal;
	opt += IO::Options::FaceNormal;

	Mesh mesh;
	
	mesh.request_face_normals();
	mesh.request_vertex_normals();
	mesh.request_vertex_colors();
	mesh.request_vertex_texcoords2D();
	
	if ( !IO::read_mesh(mesh, path, opt )) {
		printf("Cannot load mesh from %s\n", path.c_str());
		exit(1);
	}
	
	mesh.update_normals();

	meshes.push_back(mesh);
}

void Model::render() {
	fitSphereAll();
	renderModel();
}

void Model::renderModel() {
	glDepthRange(0.001,1);
	glEnable(GL_NORMALIZE);

	for (unsigned int i = 0; i < meshes.size(); ++i) {
		Mesh mesh = meshes[i];
		for (Mesh::ConstFaceIter it = mesh.faces_begin(); it != mesh.faces_end(); ++it) {
			Vec3f nA, nB, nC;
			Vec3f pA, pB, pC;
			Vec2f tA, tB, tC;
			Mesh::ConstFaceVertexIter cfv_it = mesh.cfv_iter(it.handle());
            
			nA = mesh.normal(cfv_it.handle());
			pA = mesh.point(cfv_it.handle());
			tA = mesh.texcoord2D(cfv_it.handle());
			nB = mesh.normal((++cfv_it).handle());
			pB = mesh.point(cfv_it.handle());
			tB = mesh.texcoord2D(cfv_it.handle());
			nC = mesh.normal((++cfv_it).handle());
			pC = mesh.point(cfv_it.handle());
			tC = mesh.texcoord2D(cfv_it.handle());
                        
			glBegin(GL_TRIANGLES);
            glColor3f(0.7,0.7,0.7);
            glTexCoord2f(tA[0],tA[1]);
			glNormal3f(nA[0],nA[1],nA[2]);
			glVertex3f(pA[0],pA[1],pA[2]);
			glTexCoord2f(tB[0],tB[1]);
			glNormal3f(nB[0],nB[1],nB[2]);
			glVertex3f(pB[0],pB[1],pB[2]);
			glTexCoord2f(tC[0],tC[1]);
			glNormal3f(nC[0],nC[1],nC[2]);
			glVertex3f(pC[0],pC[1],pC[2]);
			glEnd();
		}
	}
	
	glDepthRange(0,1);
}

// Normalize model
void Model::fitSphereAll() {
	for (unsigned int i = 0; i < meshes.size(); ++i)
		fitSphere(i);
}

void Model::fitSphere(unsigned int i) {
	Mesh mesh = meshes[i];

	// Move center of mass to origin
	Vec3f center(0,0,0);
	for (Mesh::ConstVertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) center += mesh.point(vIt);
	center /= mesh.n_vertices();
	for (Mesh::VertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) meshes[i].point(vIt) -= center;

	// Fit in the unit sphere
	float maxLength = 0;
	for (Mesh::ConstVertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) maxLength = max(maxLength, mesh.point(vIt).length());
	for (Mesh::VertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) meshes[i].point(vIt) /= maxLength;
}