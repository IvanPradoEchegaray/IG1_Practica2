//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Light.h"

#include <vector>

//-------------------------------------------------------------------------

class IG1App;

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment

	void init();
	void render(Camera const& cam) const;
	void update();

	int mId = 0;
	void changeScene(int id);
	void screenShot();
	void setID(int id);
	void sceneDirLight(Camera const& cam) const;
	void orbita();
	void rota();
	void TIELightsOn();
	void TIELightsOff();

	DirLight* dirLight;
	PosLight* posLight;
	SpotLight* spotLight;
	
	SpotLight* tieFighterL1;
	SpotLight* tieFighterL2;
	SpotLight* tieFighterL3;
protected:
	void free();
	void setGL();
	void resetGL();
	void setLights();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

