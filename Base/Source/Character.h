#ifndef CHARACTER_H
#define CHARACTER_H
#include "Object.h"
#include "Weapon.h"
#include "SpriteAnimation.h"

/*******************************************************/
/*
Character class for all living things. Only for 2D.
*/
/*******************************************************/
class Character
{
public:
	/* Character can only go 8 diff. directions */
	enum DIRECTION
	{
		N,	//north
		S,	//south
		E,	//east (RIGHT)
		W,	//west (LEFT)
		N_E,
		N_W,
		s_E,
		S_W,
		TOTAL_DIRECTIONS,
	};

	/* Constructor/destructor */
	Character();
	~Character();

	/* Core */
	void Init(Vector3 pos, Vector3 scale, DIRECTION facingDir);
	void Update(double dt);

	/* Getter/Setter */
	Vector3 getPosition();
	Vector3 getScale();
	Mesh* getMesh();
	Object* getObject();
protected:
	/* Physical */
	Object object;

	/* Directions */
	DIRECTION facingDir;

	/* Sprite */
	SpriteAnimation* sprite;
	SpriteData directionSprites[TOTAL_DIRECTIONS];

	/* Physics */
	Vector3 vel;
};

#endif