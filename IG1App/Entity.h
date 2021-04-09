//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"
//-------------------------------------------------------------------------
class IG1App;
class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0) , mColor(0.0), mPos(0,0,0){};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update() {};

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	void changemColor(glm::dvec4 const& newColor) { mColor = newColor; };
	void seTexture(Texture* tex_) { mTexture = tex_; }
	void setTranslation(glm::dvec3 pos) { mPos = pos; }
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	glm::dvec4 mColor;		//glm::dvec4 = 4 elem vector, in this case its purpose is color info
	glm::dvec3 mPos;	//Posicion de la matriz
	Texture* mTexture = nullptr;
	
	//for vertex -> glm::dmat4 -> mat = matrix & 4 = 4 elem
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
class TriangleRGB : public Abs_Entity
{
public:
	explicit TriangleRGB(GLdouble rd);
	~TriangleRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
protected:
	//atributos de angulo de giro
	GLdouble mRotation = 0;	//sobre si mismo
	GLdouble mTranslation = 0;	//sobre un centro
};

//-------------------------------------------------------------------------

class PolygonLine : public Abs_Entity
{
public:
	explicit PolygonLine(GLuint numL, GLdouble rd, glm::dvec4 color);
	~PolygonLine();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class Sierpinkski : public Abs_Entity
{
public:
	explicit Sierpinkski( GLdouble rd, GLuint numP, glm::dvec4 color);
	~Sierpinkski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------
//Practica 2
//------------------------------------------------------------------------
class Star3D : public Abs_Entity
{
public:
	explicit Star3D(GLdouble re, GLuint np, GLdouble h);
	~Star3D();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update();

protected:
	GLdouble yRotation = 0;
	GLdouble zRotation = 0;
};

//-------------------------------------------------------------------------

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld, Texture* inTex);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	Texture* inTex_;
};

//-------------------------------------------------------------------------

class CajaconFondo : public Abs_Entity
{
public:
	explicit CajaconFondo(GLdouble ld, Texture* inTex);
	~CajaconFondo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
protected:
	Mesh* mesh_fondo = nullptr;
	glm::dmat4 mat_fondo = glm::dmat4(1.0);
	Texture* inTex_;
	GLdouble zRotation = 0;
	GLdouble ldl;
};

//-------------------------------------------------------------------------

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture* tex_window);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	Mesh* mMeshWindow = nullptr;
	glm::dmat4 mMatWindow = glm::dmat4(1.0); 
	Texture* mTex_window;
};
//-------------------------------------------------------------------------

class Grass : public Abs_Entity
{
public:
	explicit Grass(GLuint r,GLdouble w, GLdouble h, glm::dvec3 pos);
	~Grass();
	virtual void render(glm::dmat4 const& modelViewMat) const;
protected:
	std::vector<glm::dmat4> mMats_;
};
//-------------------------------------------------------------------------

class Foto : public Abs_Entity
{
public:
	explicit Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_