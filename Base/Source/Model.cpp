#include "Model.h"
#include "GL\glew.h"
#include <sstream>
Camera Model::camera;
float Model::fovAngle;	//this angle is used for fov
bool Model::InitAlready = false;

/*********** constructor/destructor ***************/
Model::Model()
{
}

Model::~Model()
{
}

/*********** core functions ***************/
void Model::Init()
{
	if( InitAlready )	//init already no need init again
		return;

	/* Must Init */
	InitMesh();

	//2D: look to Z
	camera.Init(Vector3(0.f, 0.f, 5.f), Vector3(0.f, 0.f, 4.f), Vector3(0, 1, 0));


	bLightEnabled = true;

	InitAlready = true;
}

void Model::InitMesh()
{
	Geometry::Init();
}

void Model::Update(double dt, bool* myKeys, Vector3 cursorPos)
{
	/* openGL stuff */
	UpdateOpenGL(dt, myKeys);

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

/*********** getter / setters ***************/
bool Model::getbLightEnabled(){return bLightEnabled;}
float Model::getFOV(){return fovAngle;}
Camera* Model::getCamera(){return &camera;}
Vector3 Model::getWorldDimension(){return worldDimension;}
unsigned short Model::getViewWidth(){return m_view_width;}
unsigned short Model::getViewHeight(){return m_view_height;}

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
