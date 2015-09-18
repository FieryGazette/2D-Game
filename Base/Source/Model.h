#ifndef MODEL_H
#define MODEL_H
#include "MeshList.h"
#include "MatrixStack.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "Light.h"
#include "MiniMap.h"
#include "Object.h"
#include "Camera3.h"
#include <sstream>
#include <vector>
using namespace std;

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

class Model
{
protected:
/********************** View size *****************************/
	unsigned short m_view_width;	//camera view size X
	unsigned short m_view_height;	//camera view size Y
	Vector3 worldDimension;	//max dimemsion for in-game world (eg. 1000 by 1000 by 1000 world space)

	/************* Camera *****************/
	static Camera3 camera;
	static float fovAngle;	//this angle is used for fov

	/************* Light *****************/
	bool bLightEnabled;
	float fps;

	/************ lights ************/
	const static unsigned TOTAL_LIGHTS = 2;
	Position lightPos[TOTAL_LIGHTS];

	/************ Game objects ************/ 
	vector<Object*> elementObject;	//sky, clouds stuff player cannot reach

	static bool InitStatic;	//have we init static stuff already?

public:
	/*********** constructor/destructor ***************/
	Model();
	virtual ~Model();

	/*********** core functions ***************/
	virtual void Init();
	void InitMesh();

	virtual void Update(double dt, bool* myKeys);
	void UpdateOpenGL(double dt, bool* myKeys);
	void UpdateFOV(double dt, bool* myKeys);

	virtual void Exit();


	/*********** getter / setters ***************/
	bool getbLightEnabled();
	float getFOV();
	Camera3* getCamera();
	float getFPS();
	Position getLightPos(int index);
	vector<Object*>* getObject();
	Object* getObject(int index);
	unsigned short getViewWidth();
	unsigned short getViewHeight();
	Vector3 getWorldDimension();

	/************* Minimap *****************/
	MiniMap* minimap;
};

#endif