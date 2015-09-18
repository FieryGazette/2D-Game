#include "Model_Gameplay.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Controller.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadHmap.h"
#include "SpriteAnimation.h"
#include <sstream>

float zTime = 0.1f;
float zTimer = zTime;
bool up = false;

/*********** constructor/destructor ***************/
Model_Gameplay::Model_Gameplay()
{
	minimap = NULL;
}

Model_Gameplay::~Model_Gameplay()
{
}

/*********** core functions ***************/
void Model_Gameplay::Init()
{
	Model::Init();

	/* Coord of screen */
	//3 : 2 (Follow screen dimension)
	m_view_width = 2400.f;
	m_view_height = 1600.f;

	/* World boundaries */
	worldDimension.Set(800, 800, 100);

	//perspective
	fovAngle = 45;

	//light
	lightPos[0].Set(1000.f, 500.f, 0.f);
	lightPos[1].Set(0.f, 800.f, 0.f);

	//object
	InitObject();
}

void Model_Gameplay::InitObject()
{	
	/** Default pos : 0, 0, 0
		Default scale: 1, 1, 1
	**/

	Object* obj_ptr;

	/** Player **/
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	obj_ptr->translateObject(m_view_width / 2, m_view_height / 2, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(175, 75, 75);
	elementObject.push_back(obj_ptr);

	/** init **/
	for(std::vector<Object*>::iterator it = elementObject.begin(); it != elementObject.end(); ++it)
	{
		Object *go = (Object *)*it;
		go->Init();
	}
}

void Model_Gameplay::Update(double dt, bool* myKeys)
{
	/* model update */
	Model::Update(dt, myKeys);

	//Vector3 vel;
	//vel.SetZero();

	///* Set up collision */
	//elementObject[0]->StartChecking(vel);

	///* Check collision */
	//elementObject[0]->checkCollision2(*elementObject[68]);
	//elementObject[0]->checkCollision2(*elementObject[69]);
	//elementObject[0]->checkCollision2(*elementObject[2]);
	//elementObject[0]->checkCollision2(*elementObject[1]);

	//for(int i = 4; i < 68; ++i)
	//{
	//	elementObject[0]->checkCollision2(*elementObject[i]);
	//}

	///* Reset */
	//elementObject[0]->collideBox.Reset();

	///* collision response */
	//elementObject[0]->Response(vel);
}

void Model_Gameplay::Exit()
{
	Model::Exit();
}