//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
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
	void setTexture(Texture* tex_) { mTexture = tex_; }
	void setTranslation(glm::dvec3 pos) { mPos = pos; }
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	IndexMesh* iMesh = nullptr;
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
//Practica 1
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

class Cristalera : public Abs_Entity {
public:
	explicit Cristalera(GLdouble ld);
	~Cristalera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------
//Practica 2
//------------------------------------------------------------------------
class QuadricEntity : public Abs_Entity
{
public:
	QuadricEntity(){ q = gluNewQuadric(); };
	virtual ~QuadricEntity() { gluDeleteQuadric(q); };
	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void update() {};
protected:
	GLUquadricObj* q;
	GLint slices_ = 50, stacks_ = 50;
};
//-------------------------------------------------------------------------
class Sphere :public QuadricEntity
{
public:
	explicit Sphere(GLdouble radius) : r(radius) {};
	~Sphere() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update() {};
protected:
	GLdouble r;
};
//-------------------------------------------------------------------------
class Cylinder : public QuadricEntity
{
public:
	explicit Cylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble heigth) :
		baseR(baseRadius), topR(topRadius), h(heigth) {};
	~Cylinder() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update() {};
protected:
	GLdouble baseR, topR, h;
};
//-------------------------------------------------------------------------
class Disk : public QuadricEntity
{
public:
	explicit Disk(GLdouble innerRadius, GLdouble outerRadius) : inR(innerRadius), outR(outerRadius) {};
	~Disk() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update() {};
protected:
	GLdouble inR, outR;
};
//-------------------------------------------------------------------------
class PartialDisk : public QuadricEntity
{
public:
	explicit PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle) :
		inR(innerRadius), outR(outerRadius), startAng(startAngle), sweepAng(sweepAngle) {};
	~PartialDisk() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
	virtual void update() {};
protected:
	GLdouble inR, outR, startAng, sweepAng;
};
//-------------------------------------------------------------------------
class Polygon3D : public Abs_Entity
{
public:
	explicit Polygon3D(GLdouble re, GLuint np);
	~Polygon3D();
	virtual void render(glm::dmat4 const& modelViewMat)const;
};
//-------------------------------------------------------------------------
class AnilloCuadrado : public Abs_Entity {
public:
	explicit AnilloCuadrado();
	~AnilloCuadrado();
	virtual void render(glm::dmat4 const& modelViewMat)const;
};
//-------------------------------------------------------------------------
class EntityWithIndexMesh : public Abs_Entity {
public:
	explicit EntityWithIndexMesh() {};
	~EntityWithIndexMesh() {};
	virtual void render(glm::dmat4 const& modelViewMat)const {};
};
//-------------------------------------------------------------------------
class Cubo : public EntityWithIndexMesh {
public:
	explicit Cubo(GLdouble l);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat)const;
};
//-------------------------------------------------------------------------
class CompoundEntity : public Abs_Entity{
public:
	explicit CompoundEntity() {};
	~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat)const;
	void addEntity(Abs_Entity* ae);
	void addLight(Light* light);
private:
	std::vector<Abs_Entity*> gObjects;
	std::vector<Light*> gLights;
};
//-------------------------------------------------------------------------
class TieFighter : public CompoundEntity {
public:
	TieFighter(Texture* tex_);
	~TieFighter() {};
};
//-------------------------------------------------------------------------
class Cono : public Abs_Entity {
public:
	explicit Cono(GLdouble h, GLdouble r, GLint n);
	~Cono() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
private:
	GLdouble h_;
	GLdouble r_;
	GLdouble n_;
};
//-------------------------------------------------------------------------
class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() {};
	~EntityWithMaterial() {};
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};
//-------------------------------------------------------------------------
class Esfera : public EntityWithMaterial {
public:
	explicit Esfera(GLdouble r, GLdouble p, GLint m);
	~Esfera() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
private:
	GLdouble r_;
	GLdouble p_;
	GLdouble m_;
};
//-------------------------------------------------------------------------
class Grid : public Abs_Entity {
public:
	explicit Grid(GLdouble l, GLuint nDiv);
	~Grid() {};
	virtual void render(glm::dmat4 const& modelViewMat)const;
};
//-------------------------------------------------------------------------
class GridCube : public CompoundEntity {
public:
	GridCube(GLdouble lado, GLuint nDiv, Texture* topTex, Texture* sideTex);
	~GridCube() {};
	virtual void render()const {};
};
#endif //_H_Entities_H_