//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* createTriangleRGB(GLdouble rd);	//creates a new Triangle mesh
	static Mesh* generaPoligono(GLuint numL, GLdouble rd); //creates a polygon Mesh
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP);	//creates Piersinski Mesh
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h); //creates a "Star"3d
	static Mesh* generaContCubo(GLdouble ld);
	static Mesh* generaContCuboSuelo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCuboTexCor(GLdouble nl); 
	static Mesh* generaContCuboSueloTexCor(GLdouble w, GLdouble h);
	//Practica 2
	static Mesh* generaPolygon3D(GLdouble re, GLuint np);
	static Mesh* generaPolygonTexCor(GLdouble re, GLuint np);

	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
		
protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	std::vector<glm::dvec2> vTexCoords;
	std::vector < glm::dvec3> vNormals;	//tabla de normales
	virtual void draw() const;
};
//-------------------------------------------------------------------------

class IndexMesh : public Mesh {
protected:
	GLuint mNumIndices = 0;
	GLuint* vIndices = nullptr;
	virtual void draw() const;
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndices; }
	virtual void render() const;
	void buildNormalVectors();

	static IndexMesh* generaAnilloCuadradoIndexado();
	static IndexMesh* generaCuboConTapasIndexado(GLdouble l);
};

#endif //_H_Scene_H_