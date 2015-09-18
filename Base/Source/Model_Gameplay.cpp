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


/*********** constructor/destructor ***************/
Model_Gameplay::Model_Gameplay()
{
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

	//weapon
	Weapon::InitAmmo(elementObject);

	//object
	InitObject();

	//player
	//!! COLLISION BUG: IF SCALE IS 50 BY 50 AND WALL IS EXACTLY 12 SCALE THICK, WILL GO THRU
	//WARNING: DO NOT GO BEYOND 1000 speed since sweep AABB bug not solved yet
	player.Init(Vector3(200, 220, 1), Vector3(50, 50, 1), Character::E, 100, 100, 5000);
	elementObject.push_back(&player);

	/* Init all game objects */
	for(std::vector<Object*>::iterator it = elementObject.begin(); it != elementObject.end(); ++it)
	{
		Object *go = (Object *)*it;
		go->Init();
	}
}

void Model_Gameplay::InitObject()
{	
	/** Default pos : 0, 0, 0
		Default scale: 1, 1, 1
		m_view_width = 2400.f;
		m_view_height = 1600.f;
	**/

	Object* obj_ptr;

	/** Walls **/
	//for now Z will be 100 as z collision check not removed yet
	//top
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	obj_ptr->translateObject(m_view_width * 0.5f, 1590, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(m_view_width, 12, 100);	
	elementObject.push_back(obj_ptr);

	//bottom
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	obj_ptr->translateObject(m_view_width * 0.5f, 10, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(m_view_width, 12, 100);	
	elementObject.push_back(obj_ptr);

	//left
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	obj_ptr->translateObject(10, m_view_height * 0.5f, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(12, m_view_height, 100);	
	elementObject.push_back(obj_ptr);

	//right
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	obj_ptr->translateObject(2390, m_view_height * 0.5f, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(12, m_view_height, 100);	
	elementObject.push_back(obj_ptr);
}

void Model_Gameplay::Update(double dt, bool* myKeys)
{
	/* model update */
	Model::Update(dt, myKeys);

	/* Update Ammo */
	Weapon::UpdateAmmos(elementObject);

	/* Update player */
	player.Update(dt, myKeys, elementObject);
}

void Model_Gameplay::Exit()
{
	Model::Exit();
}