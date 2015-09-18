#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "View_3D_Game.h"
#include "timer.h"

class Controller
{
public:
/********************** enums **********************/
	enum MODE
	{
		TWO_D,
		THREE_D,
	};

/******************** core functions **********************/
	void Init();

	virtual void Run() = 0;

	virtual void Exit();

/********************** controller functions **********************/
	static bool IsKeyPressed(unsigned short key);
	static bool getKeyboardUpdate();

/********************** mouse **********************/
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;

	bool GetMouseUpdate();
	static double getCameraYaw();
	static double getCameraPitch();

/********************** getter setter **********************/
	bool* getKeyPressed();
	static double getYawAngle();
	static double  getPitchAngle();
	static void incrementPitchAngle(float i);
	static void incrementYawAngle(float i);
	static void setYawAngle(float y);
	static  void setPitchAngle(float p);
	float getFPS();

/********************* constructor / destructor *********************/
	Controller();
	~Controller();

protected:
	const static unsigned char Controller::FPS; // FPS of this game (ONLY RELEASE MODE CAN RUN SMOOTHLY AT 170FPS MAX)
	const static unsigned int Controller::frameTime; // time for each frame

/********************* Core *********************/
	void InitCurrentView();
	void InitCurrentModel();
	void RunGameLoop(bool* myKeys);

/********************** Input **********************/
	MODE type;	//mode

/********************** model and view ptr **********************/
	Model* currentModel; 
	View* currentView;
	bool* myKeys;	//if theres a control array, not NULL

/********************** mouse **********************/
	static double camera_yaw, camera_pitch;
	const static int m_window_deadzone = 100;
	static double yawAngle, pitchAngle;
	static int mouseRightButton;
	static int mouseLeftButton;

/********************** Declare a window object **********************/
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_thread1;
	double m_dAccumulatedTime_thread2;

	float fps;
};

#endif