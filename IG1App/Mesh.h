#pragma once

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* generaPoligono(GLuint numL, GLdouble rd);
	static Mesh* createTriangleRGB(GLdouble rd);
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP);
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCubo(GLdouble ld);
	static Mesh* generaContCuboTexCor(GLdouble nl);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaContCristal(GLdouble ld);
	static Mesh* generaGrassTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
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
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndices; }
	virtual void render() const;
	void buildNormalVectors();

	static IndexMesh* generaAnilloCuadradoIndexado();
	static IndexMesh* generaCuboConTapasIndexado(GLdouble l);
	static IndexMesh* generateGrid(GLdouble lado, GLuint nDiv);
	static IndexMesh* generateGridTex(GLdouble lado, GLuint nDiv);
protected:
	GLuint mNumIndices = 0;
	GLuint* vIndices = nullptr;
	virtual void draw() const;
};

class MbR : public IndexMesh {
public:
	MbR(int m, int n, glm::dvec3* perfil);
	static MbR* generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil);
protected:
	int m_; // numero de puntos del perfil
	int n_; // numero de rotaciones (muestras) que se toman
	glm::dvec3* perfil_; // perfil original en el plano XY
};