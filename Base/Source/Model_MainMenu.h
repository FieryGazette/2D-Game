#ifndef MODEL_MAINMENU_H
#define MODEL_MAINMENU_H
#include "Model.h"

class Model_MainMenu : public Model
{
public:
/*********** constructor/destructor ***************/
	Model_MainMenu();
	~Model_MainMenu();

/*********** core functions ***************/
	virtual void Init();
	void InitObject();

	virtual void NewStateSetup();
	virtual void OldStateExit();
	virtual void Update(double dt, bool* myKeys, Vector3& cursorPos);

	virtual void Exit();
};

#endif