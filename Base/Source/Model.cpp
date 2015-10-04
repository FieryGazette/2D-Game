#include "Model.h"
#include "Controller.h"
#include "GL\glew.h"
#include <sstream>
Camera Model::camera;
bool Model::InitAlready = false;
bool Model::switchState = false;
UI_Object* Model::cursor;
string Model::map_list = "";
Model::STATES Model::currentState = IN_GAME;
unsigned short Model::m_2D_view_width = 160.f;	//camera view size X
unsigned short Model::m_2D_view_height = 120.f;	//camera view size Y
unsigned short Model::m_view_width = 2400.f;	//camera view size X
unsigned short Model::m_view_height = 1600.f;	//camera view size Y

/*********** constructor/destructor ***************/
Model::Model()
{
	initLocalAlready = false;
}

Model::~Model()
{
}

/*********** core functions ***************/
void Model::Init()
{
	/*** Stuff that need to always re-init here ***/

	/*** Only init once stuff below here ***/
	if( InitAlready )	//init already no need init again
		return;

	/* Must Init */
	InitMesh();

	//2D: look to Z
	camera.Init(Vector3(0.f, 0.f, 5.f), Vector3(0.f, 0.f, 4.f), Vector3(0, 1, 0));

	bLightEnabled = true;

	InitAlready = true;

	/* UI Object */
	cursor = new UI_Object;
	cursor->Set("", Geometry::meshList[Geometry::GEO_CUBE_GREEN], 
		3.f, 3.f, 0.f, 0.f, 9.f, true);
	
	/* Name of map list .txt */
	map_list = "Maps//map_list.txt";
}

void Model::InitMesh()
{
	Geometry::Init();
}

void Model::Update(double dt, bool* myKeys)
{
	cursor->Translate(getCursorPos(Controller::GetCursorPos()));

	/* Sprite animation */
	for(std::vector<SpriteAnimation*>::iterator it = Geometry::animation.begin(); it != Geometry::animation.end(); ++it)
	{
		SpriteAnimation *go = (SpriteAnimation *)*it;
		go->Update(dt);
	}

	fps = (float)(1.f / dt);

	/* Framerate checker: if drop below 57, performance issues */
	if(fps < 58.f)
		cout << "Framerate dropped to: " << fps << endl;
}

void Model::Exit()
{
	Geometry::Exit();

	/* Delete all objects */
	for(int i = 0; i < elementObject.size(); ++i)
	{
		delete elementObject[i];
	}

	elementObject.clear();
}

void Model::NewStateSetup()
{
}

void Model::OldStateExit()
{
}

/*********** getter / setters ***************/
bool Model::getbLightEnabled(){return bLightEnabled;}
Camera* Model::getCamera(){return &camera;}
unsigned short Model::getViewWidth(){return m_view_width;}
unsigned short Model::getViewHeight(){return m_view_height;}
unsigned short Model::getViewWidth2D(){return m_2D_view_width;}
unsigned short Model::getViewHeight2D(){return m_2D_view_height;}
bool Model::getInitLocal(){return initLocalAlready;}

Vector3 Model::getCursorPos(Vector2 posOnScreen)
{
	int w = View::getScreenWidth();
	int h = View::getScreenHeight();

	float posX = static_cast<float>(posOnScreen.x) / w * m_2D_view_width;
	float posY = (h - static_cast<float>(posOnScreen.y)) / h * m_2D_view_height;
	return Vector3(posX, posY, 0);
}

Position Model::getLightPos(int index)
{
	//if index exceeds
	if(index < 0 || index >= TOTAL_LIGHTS)
		return Position(0, 0, 0);
	else
		return lightPos[index];
}

vector<Object*>* Model::getObject(){return &elementObject;}

Object* Model::getObject(int index)
{
	return elementObject[index];
}

bool Model::getSwitchState()
{
	return switchState;
}

void Model::SetSwitchState(bool b)
{
	switchState = b;
}

Model::STATES Model::getCurrentState()
{
	return currentState;
}
