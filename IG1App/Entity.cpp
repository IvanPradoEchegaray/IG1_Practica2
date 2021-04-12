#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//Practica 1
//------------------------------------------------------------------------
#pragma region Practica1

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);	//Grosor de la linea del objeto
		//glColor3d -> 3  = 3elem(RGB) & d = double, glColor4fv -> 4 = 4 elem (RGBA) & fv = float
		mMesh->render();
		glLineWidth(1);	//Reseteamos el grosor para el siguiente objeto que utilize GL_LINES, en caso de que utilice un grosor diferente
	}
}
//-------------------------------------------------------------------------
 
TriangleRGB::TriangleRGB(GLdouble rd) {	//Creacion del objeto
	//Se llama a la malla del objeto
	mMesh = Mesh::createTriangleRGB(rd);
}

TriangleRGB::~TriangleRGB() {
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void TriangleRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);	//Grosor solo de la LINEA/PUNTO del objeto
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		mMesh->render();
		glLineWidth(1);	//Reseteamos el grosor para el siguiente objeto que utilize lineas o puntos, en caso de que utilice un grosor diferente
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void TriangleRGB::update() {
	if (mMesh != nullptr) {
		//IMPORTANTE: PRIMERO TRANSLACION LUEGO ROTACION
		//traslacion
		GLdouble x = 200 * cos(radians(mTranslation));
		GLdouble y = 200 * sin(radians(mTranslation));
		mModelMat = translate(dmat4(1), dvec3(x, y, 0.0));
		//rotacion
		mModelMat = rotate(mModelMat, -radians(mRotation), dvec3(0.0, 0.0, 1.0));
		mRotation++;
		mTranslation++;
	}
}

//------------------------------------------------------------------------

PolygonLine::PolygonLine(GLuint numL, GLdouble rd, glm::dvec4 color)
{
	//Se llama a la malla del objeto
	mMesh = Mesh::generaPoligono(numL, rd);
	changemColor(color);
}

PolygonLine::~PolygonLine()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void PolygonLine::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; //glm marix duplicate
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		mMesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1);
	}
}

Sierpinkski::Sierpinkski( GLdouble rd, GLuint numP, glm::dvec4 color)
{
	//Se llama a la malla del objeto
	mMesh = Mesh::generaSierpinski(rd, numP);
	changemColor(color);
}

Sierpinkski::~Sierpinkski()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Sierpinkski::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; //glm marix duplicate
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPointSize(2);
		mMesh->render();
		glColor3d(1.0,1.0,1.0);
		glPointSize(1);
	}
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h)
{
	//Se llama a la malla del objeto
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);	//Grosor solo de la LINEA/PUNTO del objeto
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
		mMesh->render();
		glLineWidth(1);	//Reseteamos el grosor para el siguiente objeto que utilize lineas o puntos, en caso de que utilice un grosor diferente
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//Practica2
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h)
{
	mMesh = Mesh::generaEstrellaTexCor(re, np, h);
}

Star3D::~Star3D()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Star3D::render(glm::dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPEAT);
		mMesh->render();
		//Mirror
		aMat = rotate(aMat, radians(180.0),dvec3(1.0,0.0,0.0));
		upload(aMat);
		mMesh->render();
		mTexture->unbind();
	}
}

void Star3D::update()
{
	if (mMesh != nullptr) {
		//Rotacion
		mModelMat = translate(dmat4(1), mPos);
		mModelMat = rotate(mModelMat, radians(yRotation), dvec3(0.0, 1.0, 0.0));
		mModelMat = rotate(mModelMat, radians(zRotation), dvec3(0.0, 0.0, 1.0));
		yRotation++;
		zRotation++;
	}
}

Caja::Caja(GLdouble ld, Texture* inTex)
{
	mMesh = Mesh::generaContCuboTexCor(ld);
	inTex_ = inTex;
}

Caja::~Caja()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT/GL_BACK);
		mTexture->bind(GL_REPEAT);
		mMesh->render();
		mTexture->unbind();
		glDisable(GL_CULL_FACE);
		inTex_->bind(GL_REPEAT);
		mMesh->render();
		inTex_->unbind();
	}
}

CajaconFondo::CajaconFondo(GLdouble ld, Texture* inTex)
{
	mMesh = Mesh::generaContCuboTexCor(ld);
	mesh_fondo = Mesh::generaRectanguloTexCor(ld, ld, 1, 1);

	mModelMat = translate(dmat4(1), mPos);

	mat_fondo = rotate(mat_fondo, radians(90.0), dvec3(1.0, 0.0, 0.0));
	mat_fondo = translate(mat_fondo, mPos);
	ldl = ld;

	inTex_ = inTex;
}

CajaconFondo::~CajaconFondo()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void CajaconFondo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		//Caja normal
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		mTexture->bind(GL_REPEAT);
		mMesh->render();
		mTexture->unbind();
		glCullFace(GL_FRONT);
		inTex_->bind(GL_REPEAT);
		mMesh->render();
		inTex_->unbind();
		//Fondo de caja
		dmat4 aMat_fondo = modelViewMat * mat_fondo;
		upload(aMat_fondo);
		glCullFace(GL_BACK);
		mTexture->bind(GL_REPEAT);
		mesh_fondo->render();
		mTexture->unbind();
		glCullFace(GL_FRONT);
		inTex_->bind(GL_REPEAT);
		mesh_fondo->render();
		inTex_->unbind();
		glDisable(GL_CULL_FACE);
		//Reseteamos el grosor para el siguiente objeto que utilize lineas o puntos, en caso de que utilice un grosor diferente
	}
}

void CajaconFondo::update()
{
	if (mMesh != nullptr) {
		//Rotacion
		mModelMat = translate(dmat4(1), mPos);
		mModelMat = rotate(mModelMat, radians(zRotation), dvec3(0.0, 0.0, 1.0));
		mat_fondo = translate(mModelMat, dvec3(0.0,0.0,0.0));
		mat_fondo = rotate(mat_fondo, radians(90.0), dvec3(1.0, 0.0, 0.0));
		zRotation++;
	}
}

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh, Texture* tex_window)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	mMeshWindow = Mesh::generaContCuboSueloTexCor(w,100);

	mModelMat = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));
	mModelMat = translate(mModelMat, dvec3(-w / 2.0, -h / 2.0, 0.0));
	mMatWindow = translate(dmat4(1), dvec3(-w / 2.0, 0.0, -h / 2.0));

	mTex_window = tex_window;

}

Suelo::~Suelo()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		//Suelo
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPEAT);
		mMesh->render();
		mTexture->unbind();
		//CONTORNO
		dmat4 aMat_window = modelViewMat * mMatWindow;
		upload(aMat_window);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mTex_window->bind(GL_REPEAT);
		mMeshWindow->render();
		mTex_window->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

Foto::Foto(GLdouble w, GLdouble h) {
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	mModelMat = rotate(dmat4(1), radians(-90.0), dvec3(1.0, 0.0, 0.0));
	mModelMat = translate(mModelMat, dvec3(-w / 2.0, -h / 2.0, 0.01));
}

Foto::~Foto() {
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

void Foto::update()
{
	mTexture->loadColorBuffer(IG1App::s_ig1app.winWidth(),
		IG1App::s_ig1app.winHeight(),
		GL_FRONT);
}

Grass::Grass(GLuint r, GLdouble w, GLdouble h, dvec3 pos)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h,1,1);
	mModelMat = translate(dmat4(1), pos);
	mMats_.push_back(mModelMat);
	for (int i = 0; i < r - 1; i++) {
		dmat4 mMat = translate(mModelMat, dvec3(0.0,0.0,0.0));
		mMat = translate(mMat, dvec3(w / 2, 0.0, 0.0));
		mMat = rotate(mMat, radians(180.0 / r *(i+1)), dvec3(0.0, 1.0, 0.0));
		mMat = translate(mMat, dvec3(-w/2, 0.0, 0.0));
		mMats_.push_back(mMat);
	}
}

Grass::~Grass()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Grass::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		for (int i = 0; i < mMats_.size(); i++) {
			dmat4 aMat = modelViewMat * mMats_[i];
			upload(aMat);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5);
			mTexture->bind(GL_REPEAT);
			mMesh->render();
			mTexture->unbind();
			glDisable(GL_ALPHA_TEST);
		}
	}
}
#pragma endregion
//-------------------------------------------------------------------------
//Practica 2
//------------------------------------------------------------------------
#pragma region Practica2
//---Sphere

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.15, 0.28, 0.59);
	//Dibujado
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, slices_, stacks_);
	//Reset
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//---Partial Cylinder

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.15, 0.28, 0.59);
	//Dibujado
	gluCylinder(q, baseR, topR, h, slices_, stacks_);
	gluQuadricDrawStyle(q, GLU_FILL);
	//Reset
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//--- Disk
void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.15, 0.28, 0.59);
	//Dibujado
	gluQuadricDrawStyle(q, GLU_FILL);
	gluDisk(q, inR, outR, slices_, stacks_);
	//Reset
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}

//---Partial Disk
void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	//Color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.15, 0.28, 0.59);
	//Dibujado
	gluQuadricDrawStyle(q, GLU_FILL);
	gluPartialDisk(q, inR, outR, slices_, stacks_, startAng, sweepAng);
	//Reset
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}


Polygon3D::Polygon3D(GLdouble re, GLuint np)
{
	mMesh = Mesh::generaPolygonTexCor(re, np);
}

Polygon3D::~Polygon3D()
{
	//destruye el contenido de la malla y lo pone a nullptr
	delete mMesh; mMesh = nullptr;
}

void Polygon3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mTexture->bind(GL_REPEAT);
		mMesh->render();
		mTexture->unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}
#pragma endregion
