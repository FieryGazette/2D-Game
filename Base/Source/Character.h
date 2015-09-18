#ifndef CHARACTER_H
#define CHARACTER_H
#include "Entity.h"

/*******************************************************/
/*
Character class for all living things.
*/
/*******************************************************/
class Character : public Entity
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

	/* Getter/Setter */
	Vector3 getPosition();
	Vector3 getScale();
protected:

private:
	Collision collideBox;	//collision box
	DIRECTION facingDir;
};

#endif