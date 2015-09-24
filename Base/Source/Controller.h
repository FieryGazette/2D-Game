#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


#ifndef CONTROLLER_H
#define CONTROLLER_H
/* View */
#include "View_3D_Game.h"
#include "View_MainMenu.h"
#include "View_LevelEditor.h"

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

/********************** getter setter **********************/
	float getFPS();

/********************* constructor / destructor *********************/
	Controller();
	~Controller();

protected:
	const static unsigned char Controller::FPS; // FPS of this game (ONLY RELEASE MODE CAN RUN SMOOTHLY AT 170FPS MAX)
	const static unsigned int Controller::frameTime; // time for each frame

/********************* Core *********************/
	/** Init **/
	virtual void InitCurrentView() = 0;
	virtual void InitCurrentModel() = 0;

	/** Update **/
	virtual void RunGameLoop();
		virtual void UpdateKeys();
		virtual void UpdateMouse();
		virtual void UpdateKeyPressed();	//if a key is pressed, update this function

/********************** Input **********************/
	MODE type;	//mode

/********************** model and view ptr **********************/
	Model* currentModel; //points to the current model to run
	View* currentView;	//points to the current vuew to run

/********************** Declare a window object **********************/
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_thread1;
	double m_dAccumulatedTime_thread2;

	float fps;
};

#endif