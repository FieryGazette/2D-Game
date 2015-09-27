#include "UI_Object.h"

/*** constructor / destructor ***/
UI_Object::UI_Object()
{
}

UI_Object::~UI_Object()
{
}

/*** core ***/
void UI_Object::Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active)
{
	this->word = word;
	this->position.Set(posX, posY, zHeight);
	this->scale.Set(scaleX, scaleY, 1.f);
	this->mesh = mesh;
	this->active = active;
}

void UI_Object::Init()
{
	//anything?
}

/* particle */
void UI_Object::Update(const double& dt, Vector3& playerPos)
{
}

/* Getter setter */
void UI_Object::SetPosition(Vector3& pos)
{
	this->position.SetXY(pos.x, pos.y);
}

Vector3 UI_Object::getPosition()
{
	return position;
}

void UI_Object::SetScale(Vector3 scale)
{
	this->scale = scale;
}

Vector3 UI_Object::getScale()
{
	return scale;
}

void UI_Object::SetWord(string word)
{
	this->word = word;
}

string UI_Object::getWord()
{
	return word;
}

Mesh* UI_Object::getMesh()
{
	return mesh;
}

bool UI_Object::getActive()
{
	return active;
}

void UI_Object::SetActive(bool active)
{
	this->active = active;
}