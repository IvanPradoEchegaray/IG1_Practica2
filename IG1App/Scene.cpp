#include "Scene.h"
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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	if (mId == 0) {
		Texture* nocheTex = new Texture();
		nocheTex->load("../Bmps/noche.bmp", 200);
		gTextures.push_back(nocheTex);
		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(400.0));

		////TIE-FIGHTER
		TieFighter* tie_fighter = new TieFighter(nocheTex);
		gObjects.push_back(tie_fighter);
	}
	if (mId == 1) {
		glClearColor(0.5, 0.7, 1.0, 1.0);
		//Ejes de coordenadas
		gObjects.push_back(new EjesRGB(400.0));

		AnilloCuadrado* cuadrado = new AnilloCuadrado();
	    gObjects.push_back(cuadrado);

	}
	if (mId == 2)
	{
		glClearColor(0.5, 0.5, 0.5, 1.0);
		gObjects.push_back(new EjesRGB(400.0));

		Cubo* cubo = new Cubo(50);
		gObjects.push_back(cubo);
	}
	if (mId == 3) {
		glClearColor(0.8, 0.5, 0.5, 1.0);
		//Ejes de coordenadas
		gObjects.push_back(new EjesRGB(400.0));
		//Sphere
		Sphere* sphere = new Sphere(25);
		sphere->setModelMat(translate(dmat4(1), dvec3(75.0, 0.0, 0.0)));
		gObjects.push_back(sphere);
		//Esfera
		Esfera* esfera = new Esfera(25, 8, 50);
		gObjects.push_back(esfera);
	}
	if (mId == 4)
	{
		glClearColor(0.5, 0.8, 0.5, 1.0);
		Texture* top_bot_tex = new Texture();
		top_bot_tex->load("../Bmps/checker.bmp");
		gTextures.push_back(top_bot_tex);
		Texture* side_tex = new Texture();
		side_tex->load("../Bmps/stones.bmp");
		gTextures.push_back(side_tex);

		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(400.0));

		//Cubo
		GridCube* cube = new GridCube(200.0, 10, top_bot_tex, side_tex);
		gObjects.push_back(cube);
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
	sceneDirLight(cam);
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
void Scene::setID(int id) {
	mId = id;
}