﻿#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings
	// allocate memory and load resources

	// Lights
	// Textures
	if (mId == 0) {
		Texture* nocheTex = new Texture();
		nocheTex->load("../Bmps/noche.bmp", 200);
		gTextures.push_back(nocheTex);
		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(400.0));
		//--Esfera--
		gObjects.push_back(new Sphere(50.0));
		//Cilindro Ancho
		Cylinder* c = new Cylinder(35.0, 35.0, 20.0);
		dvec3 posC = dvec3(30, 0, 0);
		c->setModelMat(translate(dmat4(1), posC));
		c->setModelMat(rotate(c->modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0)));
		gObjects.push_back(c);
		//Tapa Cilindro
		Disk* tapa = new Disk(0, 35.0);
		dvec3 posTapa = dvec3(50, 0, 0);
		tapa->setModelMat(translate(dmat4(1), posTapa));
		tapa->setModelMat(rotate(tapa->modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0)));
		gObjects.push_back(tapa);
		//Cilindro Alas
		Cylinder* c2 = new Cylinder(15.0, 15.0, 200.0);
		dvec3 posC2 = dvec3(0, 0, -100);
		c2->setModelMat(translate(dmat4(1), posC2));
		gObjects.push_back(c2);
		//--Ala 1--
		Polygon3D* wing1 = new Polygon3D(160.0, 6);
		wing1->setTexture(nocheTex);
		dvec3 poswing1 = dvec3(0, 0, 100.0);
		wing1->setModelMat(translate(dmat4(1), poswing1));
		gObjects.push_back(wing1);
		//--Ala 2--
		Polygon3D* wing2 = new Polygon3D(160.0, 6);
		wing2->setTexture(nocheTex);
		dvec3 poswing2 = dvec3(0, 0, -100.0);
		wing2->setModelMat(translate(dmat4(1), poswing2));
		gObjects.push_back(wing2);
	}
	if (mId == 1) {
		glClearColor(0.5, 0.7, 1.0, 1.0);
		//Ejes de coordenadas
		gObjects.push_back(new EjesRGB(400.0));

		AnilloCuadrado* cuadrado = new AnilloCuadrado();
		Cubo* cubo = new Cubo(50);
		
		gObjects.push_back(cubo);
	    //gObjects.push_back(cuadrado);
	}
}

void Scene::update()
{
	for (Abs_Entity* g : gObjects) {
		g->update();
	}
}

void Scene::changeScene(int id)
{
	mId = id;
	free();
	resetGL();
	init();
}

void Scene::screenShot() {
	Texture* tex = new Texture();
	tex->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winHeight(), GL_FRONT);
	tex->save("screenshot.bmp");
	delete tex;
}

//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	//Luz de la escena
	//sceneDirLight(cam);
	//Actualiza la/s camaras
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}

void Scene::sceneDirLight(Camera const& cam) const { 
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0); 
	glm::fvec4 posDir = { 1, 1, 1, 0 }; 
	glMatrixMode(GL_MODELVIEW); 
	glLoadMatrixd(value_ptr(cam.viewMat())); 
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir)); 
	glm::fvec4 ambient = { 0, 0, 0, 1 }; 
	glm::fvec4 diffuse = { 1, 1, 1, 1 }; 
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient)); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse)); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular)); 
}
//-------------------------------------------------------------------------


