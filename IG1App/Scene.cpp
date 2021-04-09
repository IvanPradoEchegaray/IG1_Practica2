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
	// Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));

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
	glClearColor(0.7, 0.8, 0.9, 1.0);  // background color (alpha=1 -> opaque)
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
	glm::fvec4 ambient = { 0, 0, 0, 1 }; glm::fvec4 diffuse = { 1, 1, 1, 1 }; 
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 }; glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient)); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse)); glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular)); 
}
//-------------------------------------------------------------------------


