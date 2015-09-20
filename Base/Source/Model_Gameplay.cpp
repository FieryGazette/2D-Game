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
	//!! COLLISION BUG: IF SCALE IS 50 BY 50 AND WALL IS EXACTLY 12 SCALE THICK, WILL GO THRU
	//WARNING: DO NOT GO BEYOND 1000 speed since sweep AABB bug not solved yet
	player.Init(Vector3(800, 800, 1), Vector3(50, 50, 1), Character::E, 100, 100, 150);
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

	/* WALL 1 */
	//for now Z will be 100 as z collision check not removed yet
	//top
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);

	//RIGHT
	obj_ptr->translateObject(2000, 950, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(6, 1200, 100);	

	elementObject.push_back(obj_ptr);

	/* WALL 2 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	//TOP
	obj_ptr->translateObject(m_view_width * 0.5f, 1500, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(1800, 6, 100);

	elementObject.push_back(obj_ptr);


	/* WALL 3 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	//LEFT
	obj_ptr->translateObject(400, 950, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(6, 1200, 100);	

	elementObject.push_back(obj_ptr);


	/* WALL 4 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	//BOTTOM
	obj_ptr->translateObject(m_view_width * 0.5f, 400, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(1800, 6, 100);	

	elementObject.push_back(obj_ptr);

	/* WALL 5 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_GREEN], NULL, false, false);

	//BOTTOM
	obj_ptr->translateObject(396.40192, 1222.2026, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(130, 170, 50);	

	elementObject.push_back(obj_ptr);


	/* WALL 6 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_CUBE_BLUE], NULL, false, false);
	
	obj_ptr->translateObject(800, 800, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(50, 50, 100);	

	elementObject.push_back(obj_ptr);


	/* WALL 7 */
	obj_ptr = new Object;
	obj_ptr->Set("character", Geometry::meshList[Geometry::GEO_BACK], NULL, false, false);
	
	obj_ptr->translateObject(800, 800, -1.f);	//start at right side of box (going top left initially)
	obj_ptr->scaleObject(50, 50, 100);	

	elementObject.push_back(obj_ptr);
}

void Model_Gameplay::Update(double dt, bool* myKeys)
{
	/* model update */
	Model::Update(dt, myKeys);

	/* Update Ammo */
	//Weapon::UpdateAmmos(elementObject);


	/* Update test wall */
	if( myKeys[ARROW_UP] )
		elementObject[4]->translateObject(0, 300 * dt, 0);

	if( myKeys[ARROW_DOWN] )
		elementObject[4]->translateObject(0, -300 * dt, 0);

	if( myKeys[ARROW_LEFT] )
		elementObject[4]->translateObject(-300 * dt, 0, 0);

	if( myKeys[ARROW_RIGHT] )
		elementObject[4]->translateObject(300 * dt, 0, 0);

	elementObject[4]->collideBox.position = elementObject[4]->position;

	//cout << "Pos: " << elementObject[4]->position << endl;
	/* Update player */
	player.Update(dt, myKeys, elementObject);

	/* Update */
	elementObject[6]->translate(Collision2::noSlidePos);
}

void Model_Gameplay::Exit()
{
	Model::Exit();
}