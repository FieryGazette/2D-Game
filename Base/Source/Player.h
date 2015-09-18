#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"

/** Put here for controller and model and character to access, got better way? **/
enum CONTROLS
{
	/* using ascii table */
	FORWARD,	//w
	BACKWARD,	//s
	LEFT,	//a
	RIGHT,	//d
	CROUCH,	//c
	RELOAD,	//r
	JUMP,	//space bar
	FLY_UP,	//k
	FLY_DOWN,	//l
	PAUSE,	//p
	OPEN,	//o

	/* using mouse/controller... */
	SHOOT,	//mouse left
	AIM,	//mouse right
	TOGGLE_SPRINT,	//shift
	SCROLL_UP,	//mouse scroll
	SCROLL_DOWN,	//mouse scroll
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,

	TOTAL_CONTROL,
};

class Player : public Character
{
	/* Basics */
	float health;
	float staminia;
	Weapon weapon;
	float speed;
public:
	/* constructor / destrutor */
	Player();
	~Player();

	/* Core */
	void Init(Vector3 pos, Vector3 scale, DIRECTION facingDir, float health, float staminia, float speed);
	void Update(double dt, bool* myKeys, vector<Object*>& objectLists);
	Mesh* getMesh();
};

#endif