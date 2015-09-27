#include "UI_Object.h"

/*** constructor / destructor ***/
UI_Object::UI_Object()
{
}

UI_Object::~UI_Object()
{
}

/*** core ***/
void UI_Object::Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY)
{
	this->word = word;
	Object::Set("", mesh, NULL, false, false);
	Object::translateObject(posX, posY, 1);
	Object::scaleObject(scaleX, scaleY, 1);
}

void UI_Object::AddParent(UI_Object* parent)
{
	Object::AddParent(parent);
}

void UI_Object::Init()
{
	Object::Init();
}

/* particle */
void UI_Object::Update(const double& dt, Vector3& playerPos)
{
}