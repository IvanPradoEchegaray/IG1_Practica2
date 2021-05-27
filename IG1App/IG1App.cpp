#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mCamera2 = new Camera(mViewPort);
	mScene = new Scene;
	mScene->setID(0);
	mScene2 = new Scene;
	mScene2->setID(1);

	mCamera->set3D();
	mCamera2->set3D();
	mScene->init();
	mScene2->init();
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL()
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free()
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display()
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	if (display2V_)
		display2V();
	else if (display2S_)
		display2Scenes();
	else
		mScene->render(*mCamera);  // uploads the viewport and camera to the GPU

	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display2V()
{
	// para renderizar las vistas utilizamos una cámara auxiliar:
	Camera auxCam = *mCamera; // copiando mCamera
	// el puerto de vista queda compartido (se copia el puntero)
	Viewport auxVP = *mViewPort; // lo copiamos en una var. aux. para
	// el tamaño de los 4 puertos de vista es el mismo, lo configuramos
	mViewPort->setSize(mWinW / 2, mWinH);
	// igual que en resize, para que no cambie la escala,
	// tenemos que cambiar el tamaño de la ventana de vista de la cámara
	auxCam.setSize(mViewPort->width(), mViewPort->height());
	// vista Usuario
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);
	// vista Cenital
	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	mScene->render(auxCam);
	*mViewPort = auxVP; // restaurar el puerto de vista
}

void IG1App::display2Scenes() {
	// para renderizar las vistas utilizamos una cámara auxiliar:
	Camera auxCam = *mCamera; // copiando mCamera
	Camera auxCam2 = *mCamera2;
	// el puerto de vista queda compartido (se copia el puntero)
	Viewport auxVP = *mViewPort; // lo copiamos en una var. aux. para
	// el tamaño de los 4 puertos de vista es el mismo, lo configuramos
	mViewPort->setSize(mWinW / 2, mWinH);
	// igual que en resize, para que no cambie la escala,
	// tenemos que cambiar el tamaño de la ventana de vista de la cámara
	auxCam.setSize(mViewPort->width(), mViewPort->height());
	auxCam2.setSize(mViewPort->width(), mViewPort->height());

	// vista Usuario
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);

	// vista Cenital
	mViewPort->setPos(mWinW / 2, 0);
	mScene2->render(auxCam2);
	*mViewPort = auxVP; // restaurar el puerto de vista
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case 'd':
		mCamera->orbit(-5.0, 0.0); // Clockwise horizontal orbit
		break;
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'q':
		mScene->dirLight->enable();
		break;
	case 'w':
		mScene->dirLight->disable();
		break;
	case 'a':
		mScene->posLight->enable();
		break;
	case 's':
		mScene->posLight->disable();
		break;
	case 'z':
		mScene->spotLight->enable();
		break;
	case 'x':
		mScene->spotLight->disable();
		break;
	case 'e': {
		GLfloat amb[] = { 0.0, 0.0, 0.0, 1.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
		mScene->spotLight->disable();
		mScene->posLight->disable();
		mScene->dirLight->disable();
		break; 
	}
	case 'r': {
		GLfloat amb[] = { 0.5, 0.5, 0.5, 1.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
		mScene->spotLight->enable();
		mScene->posLight->enable();
		mScene->dirLight->enable();
		break;
	}
	case 'k':
		display2V_ = !display2V_;  // toggles 2 viewport display
		break;
	case 'j':
		display2S_ = !display2S_;
		break;
	case 'p':
		mCamera->changePrj();	//toggles between orthogonal and perspective view
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		toggleAnimation = !toggleAnimation; // activar/desactivar la animacion con la tecla U		
		//mScene->update();
		break;
	case 'y':
		if(mScene->mId == 5)
			mScene->orbita();
		break;
	case 'b':
		if (mScene->mId == 5)
			mScene->rota();
		break;
	case '0':
		mScene->changeScene(0);
		break;
	case '1':
		mScene->changeScene(1);
		break;
	case '2':
		mScene->changeScene(2);
		break;
	case '3':
		mScene->changeScene(3);
		break;
	case '4':
		mScene->changeScene(4);
		break;
	case '5':
		mScene->changeScene(5);
		break;
	case 'f':
		mScene->screenShot();
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		mCamera->moveLR(15);   // move right
		break;
	case GLUT_KEY_LEFT:
		mCamera->moveLR(-15);  // move left
		break;
	case GLUT_KEY_UP:
		mCamera->moveUD(15);    // move up
		break;
	case GLUT_KEY_DOWN:
		mCamera->moveUD(-15);   // move down
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}

void IG1App::mouse(int b, int s, int x, int y) {
	mBot = b;
	dvec2 coord(x, y);
	mCoord = coord;
}

void IG1App::motion(int x, int y) {
	dvec2 mp(mCoord.x - x, mCoord.y - y);

	dvec2 coord(x, y);
	mCoord = coord;

	if (mBot == GLUT_LEFT_BUTTON)
		mCamera->orbit(mp.x * 0.05, -mp.y);

	else if (mBot == GLUT_RIGHT_BUTTON) {
		mCamera->moveUD(mp.y);
		mCamera->moveLR(mp.y);
	}

	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y) {
	int keyPress = glutGetModifiers();

	if (keyPress == 0) {
		mCamera->moveFB(-d * 10.0);
	}

	else if (GLUT_ACTIVE_CTRL) {
		mCamera->setScale(d);
	}

	glutPostRedisplay();
}
//-------------------------------------------------------------------------

void IG1App::update() {
	mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
	if (toggleAnimation)
	{
		mScene->update();
		glutPostRedisplay();
		Sleep(30);
	}
}
//-------------------------------------------------------------------------