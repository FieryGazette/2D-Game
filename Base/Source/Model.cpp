#include "Model.h"
#include "GL\glew.h"
#include <sstream>
Camera Model::camera;
float Model::fovAngle;	//this angle is used for fov
bool Model::InitAlready = false;
bool Model::switchState = false;
unsigned short Model::m_2D_view_width;
unsigned short Model::m_2D_view_height;
UI_Object* Model::cursor;
string Model::map_list = "";
Model::STATES Model::currentState = IN_GAME;

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

	/* Coord for UI */
	m_2D_view_width = 160.f;
	m_2D_view_height = 120.f;

	bLightEnabled = true;

	InitAlready = true;

	/* UI Object */
	cursor = new UI_Object;
	cursor->Set("Cursor", Geometry::meshList[Geometry::GEO_BACK], 
		3.f, 3.f, 0.f, 0.f, 9.f, true);
	
	/* Name of map list .txt */
	map_list = "Maps//map_list.txt";
}

void Model::InitMesh()
{
	Geometry::Init();
}

void Model::Update(double dt, bool* myKeys, Vector3& cursorPos)
{
	/* openGL stuff */
	UpdateOpenGL(dt, myKeys);

	cursor->SetPosition(cursorPos);

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

void Model::UpdateOpenGL(double dt, bool* myKeys)
{
	/*if(myKeys[KEY_1])
		glEnable(GL_CULL_FACE);
	if(myKeys[KEY_2])
		glDisable(GL_CULL_FACE);
	if(myKeys[KEY_3])
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(myKeys[KEY_4])
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
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

/*********** getter / setters ***************/
bool Model::getbLightEnabled(){return bLightEnabled;}
float Model::getFOV(){return fovAngle;}
Camera* Model::getCamera(){return &camera;}
Vector3 Model::getWorldDimension(){return worldDimension;}
unsigned short Model::getViewWidth(){return m_view_width;}
unsigned short Model::getViewHeight(){return m_view_height;}
unsigned short Model::get2DViewWidth(){return m_2D_view_width;}
unsigned short Model::get2DViewHeight(){return m_2D_view_height;}
bool Model::getInitLocal(){return initLocalAlready;}

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
