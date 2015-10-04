#ifndef MODEL_H
#define MODEL_H
#include "Player.h"
#include "MeshList.h"
#include "MatrixStack.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "Light.h"
#include "MiniMap.h"
#include "UI_Object.h"
#include "Camera3.h"
#include "readFrom.h"
#include "writeTo.h"
#include "Physics.h"
#include <sstream>
#include <vector>
using namespace std;


/*************************************************************/
/*
	Controller for models.

	Contains:
		vectors of various game objects.
		individual game objects.
		other info.

	Function:
		Manipulates the active state of game objects based on key inputs, events etc.
*/
/*************************************************************/
class Model
{
public:

	/********************** states **********************/
	//each state is 1 model
	enum STATES
	{
		MAIN_MENU,
		IN_GAME,
		EDIT_LEVEL,
		TOTAL_STATES,
	};

/*********** vectors ***********/
	vector<UI_Object*> UI_Object_List;
	vector<Object*> elementObject;
	static UI_Object* cursor;

	/*********** constructor/destructor ***************/
	Model();
	virtual ~Model();

	/*********** Set-up ***************/
	virtual void Init();

	/*********** Runtime ***************/
	virtual void Update(double dt, bool* myKeys);

	/*********** Quit ***************/
	virtual void Exit();


	/*********** getter / setters ***************/
	Vector3 getCursorPos(Vector2 posOnScreen);
	bool getbLightEnabled();
	float getFOV();
	static Camera* getCamera();
	float getFPS();
	Position getLightPos(int index);
	vector<Object*>* getObject();
	Object* getObject(int index);
	static unsigned short getViewWidth();
	static unsigned short getViewHeight();
	static unsigned short getViewWidth2D();
	static unsigned short getViewHeight2D();
	static bool getSwitchState();
	bool getInitLocal();
	static STATES getCurrentState();
	static void SetSwitchState(bool b);
	Vector3 getWorldDimension();

protected:
	/********************** View size *****************************/
	static unsigned short m_view_width;	//camera view size X
	static unsigned short m_view_height;	//camera view size Y

	/* For UI */
	static unsigned short m_2D_view_width;	//camera view size X 2D
	static unsigned short m_2D_view_height;	//camera view size Y 2D

	/************* Camera *****************/
	static Camera camera;	//2D camera

	/************* Light *****************/
	bool bLightEnabled;
	float fps;

	/************ lights ************/
	const static unsigned TOTAL_LIGHTS = 2;
	Position lightPos[TOTAL_LIGHTS];

	/************ Flags ************/ 
	static bool InitAlready;	//have we init all global stuff already?
	bool initLocalAlready;	//have we init these local stuff already?

	/*** Switch state? ***/
	static bool switchState;	//do we switch to another model?
	static STATES currentState;

	/*********** Text files ************/
	static string map_list;	//store all existing maps name

	/*********** Utilities ************/
	void InitMesh();
	/* Use only if this model will be having enum */
	virtual void NewStateSetup() = 0;	//if changing LOCAL state, call this function so new state can init stuff
	virtual void OldStateExit() = 0;	//if changing LOCAL state, call this function so previous state can exit
};

#endif