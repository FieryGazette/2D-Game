#include "Model_MainMenu.h"

#include "Model_MainMenu.h"
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
Model_MainMenu::Model_MainMenu()
{
}

Model_MainMenu::~Model_MainMenu()
{
}

/*********** core functions ***************/
void Model_MainMenu::Init()
{
	Model::Init();
}

void Model_MainMenu::InitObject()
{	
}

void Model_MainMenu::Update(double dt, bool* myKeys, Vector3 cursorPos)
{
	/* model update */
	Model::Update(dt, myKeys, cursorPos);
}

void Model_MainMenu::Exit()
{
	Model::Exit();
}