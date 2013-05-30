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
	opt += IO::Options::VertexColor;
	opt += IO::Options::FaceColor;
	
	mesh.request_face_normals();
	mesh.request_vertex_normals();
	mesh.request_face_colors();
	mesh.request_vertex_colors();
	mesh.request_vertex_texcoords2D();
	
	if ( !IO::read_mesh(mesh, path, opt )) {
		printf("Cannot load mesh from %s\n", path);
		exit(1);
	}
	
	mesh.update_normals();

	fitSphere();

	bbox = findBBox();
}

Model::~Model() {
	
}

void Model::render() {
	glDepthRange(0.001,1);
	glEnable(GL_NORMALIZE);

	for (Mesh::ConstFaceIter it = mesh.faces_begin(); it != mesh.faces_end(); ++it) {
		Vec3f nA, nB, nC;
		Vec3f pA, pB, pC;
		Vec2f tA, tB, tC;
		Vec3f cA, cB, cC;
		Mesh::ConstFaceVertexIter cfv_it = mesh.cfv_iter(it.handle());
		nA = mesh.normal(cfv_it.handle());
		pA = mesh.point(cfv_it.handle());
		tA = mesh.texcoord2D(cfv_it.handle());
		cA = mesh.color(cfv_it.handle());
		nB = mesh.normal((++cfv_it).handle());
		pB = mesh.point(cfv_it.handle());
		tB = mesh.texcoord2D(cfv_it.handle());
		cB = mesh.color(cfv_it.handle());
		nC = mesh.normal((++cfv_it).handle());
		pC = mesh.point(cfv_it.handle());
		tC = mesh.texcoord2D(cfv_it.handle());
		cC = mesh.color(cfv_it.handle());
		glBegin(GL_TRIANGLES);
		glColor3f(cA[0],cA[1],cA[2]);
		glTexCoord2f(tA[0],tA[1]);
		glNormal3f(nA[0],nA[1],nA[2]);
		glVertex3f(pA[0],pA[1],pA[2]);
		glColor3f(cB[0],cB[1],cB[2]);
		glTexCoord2f(tB[0],tB[1]);
		glNormal3f(nB[0],nB[1],nB[2]);
		glVertex3f(pB[0],pB[1],pB[2]);
		glColor3f(cC[0],cC[1],cC[2]);
		glTexCoord2f(tC[0],tC[1]);
		glNormal3f(nC[0],nC[1],nC[2]);
		glVertex3f(pC[0],pC[1],pC[2]);
		glEnd();
	}
	
	glDepthRange(0,1);
}

void Model::scale(float s) {
	for (Mesh::ConstVertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) mesh.point(vIt) *= s;
}

void Model::fitSphere() {
	// Move center of mass to origin
	Vec3f cm(0,0,0);
	for (Mesh::ConstVertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) cm += mesh.point(vIt);
	cm /= mesh.n_vertices();
	for (Mesh::VertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) mesh.point(vIt) -= cm;

	// Fit in the unit sphere
	float maxLength = 0;
	for (Mesh::ConstVertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) maxLength = max(maxLength, mesh.point(vIt).length());
	for (Mesh::VertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) mesh.point(vIt) /= maxLength;
}

BBox Model::findBBox() {
	float minx, miny, minz; minx = miny = minz = 10000.0f;
	float maxx, maxy, maxz; maxx = maxy = maxz = 0.0f;

	for (Mesh::ConstVertexIter vIt = mesh.vertices_begin(); vIt != mesh.vertices_end(); ++vIt) {
		Vec3f v = mesh.point(vIt);
		minx = min(v[0], minx); miny = min(v[1], miny); minz = min(v[2], minz);
		maxx = max(v[0], maxx); maxy = max(v[1], maxy); maxz = max(v[2], maxz);
	}

	BBox ret = BBox();
	ret.minx = minx; ret.miny = miny; ret.minz = minz;
	ret.maxx = maxx; ret.maxy = maxy; ret.maxz = maxz;

	return ret;
}