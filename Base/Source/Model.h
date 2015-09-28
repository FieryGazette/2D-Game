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
	vector<Button*> Button_List;
	vector<Object*> elementObject;	//sky, clouds stuff player cannot reach
	static UI_Object* cursor;

protected:
/********************** View size *****************************/
	unsigned short m_view_width;	//camera view size X
	unsigned short m_view_height;	//camera view size Y

	static unsigned short m_2D_view_width;
	static unsigned short m_2D_view_height;

	Vector3 worldDimension;	//max dimemsion for in-game world (eg. 1000 by 1000 by 1000 world space)

	/************* Camera *****************/
	static Camera camera;
	static float fovAngle;	//this angle is used for fov

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
	static bool switchState;
	static STATES currentState;

	/*********** Text files ************/
	static string map_list;	//store all existing maps name
public:

	/*********** constructor/destructor ***************/
	Model();
	virtual ~Model();

	/*********** core functions ***************/
	virtual void Init();
	void InitMesh();

	virtual void NewStateSetup();	//if changing state, call this function so new state can init stuff
	virtual void Update(double dt, bool* myKeys, Vector3& cursorPos);
	void UpdateOpenGL(double dt, bool* myKeys);
	void UpdateFOV(double dt, bool* myKeys);

	virtual void Exit();


	/*********** getter / setters ***************/
	bool getbLightEnabled();
	float getFOV();
	static Camera* getCamera();
	float getFPS();
	Position getLightPos(int index);
	vector<Object*>* getObject();
	Object* getObject(int index);
	unsigned short getViewWidth();
	unsigned short getViewHeight();
	static bool getSwitchState();
	static unsigned short get2DViewWidth();
	static unsigned short get2DViewHeight();
	bool getInitLocal();
	static STATES getCurrentState();
	static void SetSwitchState(bool b);
	Vector3 getWorldDimension();
};

#endif