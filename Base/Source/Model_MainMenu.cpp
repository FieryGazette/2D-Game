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

	/* Init local already? */
	if( initLocalAlready )		//yes, init alr
		return;

	initLocalAlready = true;	//no, then first time init
}

void Model_MainMenu::InitObject()
{	
}

void Model_MainMenu::Update(double dt, bool* myKeys)
{
	/* model update */
	Model::Update(dt, myKeys);
}

void Model_MainMenu::NewStateSetup()
{
}

void Model_MainMenu::OldStateExit()
{
}

void Model_MainMenu::Exit()
{
	Model::Exit();
}