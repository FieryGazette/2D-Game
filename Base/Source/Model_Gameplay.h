#ifndef MODEL_GAMEPLAY_H
#define MODEL_GAMEPLAY_H
#include "Model.h"

class Model_Gameplay : public Model
{
	Player player;	//set multiplayer
public:
/*********** constructor/destructor ***************/
	Model_Gameplay();
	~Model_Gameplay();

/*********** core functions ***************/
	virtual void Init();
	void InitObject();

	virtual void Update(double dt, bool* myKeys, Vector3& cursorPos);

	virtual void Exit();
};

#endif