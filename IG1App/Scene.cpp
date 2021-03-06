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

	//Lights
	if (!IG1App::s_ig1app.lightsCreated()) {
		setLights();
		IG1App::s_ig1app.setLightsCreated(true);
	}

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
	else if (mId == 1) {
		glClearColor(0.5, 0.7, 1.0, 1.0);
		//Ejes de coordenadas
		gObjects.push_back(new EjesRGB(400.0));

		AnilloCuadrado* cuadrado = new AnilloCuadrado();
	    gObjects.push_back(cuadrado);

	}
	else if (mId == 2)
	{
		glClearColor(0.5, 0.5, 0.5, 1.0);
		gObjects.push_back(new EjesRGB(400.0));

		Cubo* cubo = new Cubo(50);
		gObjects.push_back(cubo);
	}
	else if (mId == 3) {
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
	else if (mId == 4)
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
	else if (mId == 5) {
		//Lights
		tieFighterL1 = new SpotLight();
		tieFighterL2 = new SpotLight();
		tieFighterL3 = new SpotLight();

		//Texturas
		Texture* nocheTex = new Texture();
		nocheTex->load("../Bmps/noche.bmp", 200);
		gTextures.push_back(nocheTex);
		
		//Materiales
		Material* mat = new Material();
		mat->setCopper();

		// Graphics objects (entities) of the scene
		gObjects.push_back(new EjesRGB(1000.0));
		//Sphere
		Esfera* planeta = new Esfera(400, 300, 300);
		planeta->setMaterial(mat);
		gObjects.push_back(planeta);
		////TIE-FIGHTERs
		//Caza1
		CompoundEntity* flota = new CompoundEntity();
		//Luz caza 1
		TieFighter* tie_fighter1 = new TieFighter(nocheTex);
		tie_fighter1->setModelMat(scale(dmat4(1), dvec3(0.1, 0.1, 0.1)));
		flota->addEntity(tie_fighter1);
		tieFighterL1->setPosDir(dvec3(0, 420, 0));
		tieFighterL1->setAmb(fvec4(0, 0, 0, 1));
		tieFighterL1->setDiff(fvec4(1, 1, 1, 1));
		tieFighterL1->setSpec(fvec4(0.5, 0.5, 0.5, 1));
		tieFighterL1->setSpot(fvec3(0.0, -1.0, 0.0), 1.0, 100.0);
		flota->addLight(tieFighterL1);

		//Caza2
		TieFighter* tie_fighter2 = new TieFighter(nocheTex);
		tie_fighter2->setModelMat(translate(dmat4(1), dvec3(20, 0, -40)));
		tie_fighter2->setModelMat(scale(tie_fighter2->modelMat(), dvec3(0.1, 0.1, 0.1)));
		flota->addEntity(tie_fighter2);
		//Luz caza 2
		tieFighterL2->setPosDir(dvec3(20, 420, -40));
		tieFighterL2->setAmb(fvec4(0, 0, 0, 1));
		tieFighterL2->setDiff(fvec4(1, 1, 1, 1));
		tieFighterL2->setSpec(fvec4(0.5, 0.5, 0.5, 1));
		tieFighterL2->setSpot(fvec3(0.0, -1.0, 0.0), 1.0, 100.0);
		flota->addLight(tieFighterL2);

		//Caza3
		TieFighter* tie_fighter3 = new TieFighter(nocheTex);
		tie_fighter3->setModelMat(translate(dmat4(1), dvec3(20, 0, 40)));
		tie_fighter3->setModelMat(scale(tie_fighter3->modelMat(), dvec3(0.1, 0.1, 0.1)));
		flota->addEntity(tie_fighter3);
		//Luz caza 3
		tieFighterL3->setPosDir(dvec3(20, 420, 40));
		tieFighterL3->setAmb(fvec4(1, 1, 0, 1));
		tieFighterL3->setDiff(fvec4(1, 1, 1, 1));
		tieFighterL3->setSpec(fvec4(0.5, 0.5, 0.5, 1));
		tieFighterL3->setSpot(fvec3(0.0, -1.0, 0.0), 1.0, 100.0);
		flota->addLight(tieFighterL3);

		//Flota translate
		flota->setModelMat(translate(dmat4(1), dvec3(0, 420.0, 0)));
		gObjects.push_back(flota);
		
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
void Scene::setLights() {
	glEnable(GL_LIGHTING);
	dirLight = new DirLight();
	posLight = new PosLight();
	spotLight = new SpotLight();

	dirLight->setPosDir(fvec3(1, 1, 1));
	posLight->setPosDir(fvec3(300, 300, 300));
	spotLight->setPosDir(fvec3(0, 1, 1000));

	posLight->setAtte(0.4, 0.0, 0.0);
	spotLight->setSpot(fvec3(0, 0, -1), 5.0, 180.0);
}
//-------------------------------------------------------------------------
void Scene::render(Camera const& cam) const 
{
	//Luz de la escena
	//sceneDirLight(cam);
	dirLight->upload(cam.viewMat());
	posLight->upload(cam.viewMat());
	spotLight->upload(cam.viewMat());

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
void Scene::orbita()
{
	//Devolvemos el objeto al origen
	gObjects.back()->setModelMat(translate(gObjects.back()->modelMat(), dvec3(0, -420, 0)));
	//Lo rotamos
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), -radians(5.0), dvec3(0, 0, 1)));
	//Lo situamos de nuevo en orbita
	gObjects.back()->setModelMat(translate(gObjects.back()->modelMat(), dvec3(0, 420.0, 0)));
}
void Scene::rota()
{
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(5.0), dvec3(0, 1, 0)));
}
void Scene::TIELightsOn()
{
	tieFighterL1->enable();
	tieFighterL2->enable();
	tieFighterL3->enable();
}
void Scene::TIELightsOff()
{
	tieFighterL1->disable();
	tieFighterL2->disable();
	tieFighterL3->disable();
}
//-------------------------------------------------------------------------
void Scene::setID(int id) {
	mId = id;
}