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
	//Weapon::InitAmmo(elementObject);

	//object
	InitObject();

	//player
	//!! COLLISION BUG: IF SCALE IS 50 BY 50 , WILL GO THRU
	//WARNING: DO NOT GO BEYOND 1000 speed since sweep AABB bug not solved yet
	player.Init(Vector3(800, 800, 1), Vector3(230, 230, 1), Character::E, 100, 100, 350);
	elementObject.push_back(player.getObject());

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

	/* WALL 1 */
	//for now Z will be 100 as z collision check not removed yet
	//top
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);

	//RIGHT
	obj_ptr->translateObject(2200, 750, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(12, 1600, 100);	

	elementObject.push_back(obj_ptr);

	/* WALL 2 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	//TOP
	obj_ptr->translateObject(m_view_width * 0.5f, 1500, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(2000, 12, 100);

	elementObject.push_back(obj_ptr);


	/* WALL 3 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	//LEFT
	obj_ptr->translateObject(200, 750, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(12, 1600, 100);	

	elementObject.push_back(obj_ptr);


	/* WALL 4 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	//BOTTOM
	obj_ptr->translateObject(m_view_width * 0.5f, 50, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(2000, 12, 100);	

	elementObject.push_back(obj_ptr);

	/* WALL 5 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_GREEN], NULL, false, false);

	//BOTTOM
	obj_ptr->translateObject(696.40192, 1222.2026, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(12, 250, 50);	

	elementObject.push_back(obj_ptr);

	/* WALL 6 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_GREEN], NULL, false, false);

	//BOTTOM
	obj_ptr->translateObject(849.0, 1222.2026, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(12, 250, 50);	

	elementObject.push_back(obj_ptr);
}

void Model_Gameplay::Update(double dt, bool* myKeys, Vector3 cursorPos)
{
	/* Switch state */
	if( myKeys[SHOOT] )
	{
		switchState = true;
		currentState = EDIT_LEVEL;
	}

	/* model update */
	Model::Update(dt, myKeys, cursorPos);

	/* Update player */
	player.Update(dt, myKeys, elementObject);

	/* Update Ammo */
	//Weapon::UpdateAmmos(elementObject);

}

void Model_Gameplay::Exit()
{
	Model::Exit();
}