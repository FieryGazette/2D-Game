#include "Character.h"

/* Constructor/destructor */
Character::Character()
{

}

Character::~Character()
{
	delete sprite;
}

/* Core */
void Character::Init(Vector3 pos, Vector3 scale, DIRECTION facingDir)
{

}

void Character::Update(double dt)
{
	/* Mesh */
	sprite->Update(dt);
}

/* Getter/Setter */
Vector3 Character::getPosition()
{
	return object.position;
}

Vector3 Character::getScale()
{
	return object.scale;
}

Mesh* Character::getMesh()
{
	return sprite;
}

Object* Character::getObject()
{
	return &object;
}