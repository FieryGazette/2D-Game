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

/*************************************************************/
/*
	Contains:
		Pointer to current view and current model.
		A set of pointers of all models and views.

	Function:
		
*/
/*************************************************************/
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

/*********************** For scrolling **********************/
	static void setScrollX(double p);
	static void setScrollY(double p);

protected:
	const static unsigned char Controller::FPS; // FPS of this game (ONLY RELEASE MODE CAN RUN SMOOTHLY AT 170FPS MAX)
	const static unsigned int Controller::frameTime; // time for each frame

/********************* Core *********************/
	/** Init **/
	virtual void InitCurrentView() = 0;
	virtual void InitCurrentModel() = 0;

	/** Update **/
	virtual void RunGameLoop();

		/** Switching models **/
		virtual void SwitchModels() = 0;	//for update changing models, like main menu to game

		/* Call only when needed: if your program needs key and mouse press */
		void UpdateKeys();
		void UpdateMouse();
		void UpdateKeyPressed();	//if a key is pressed, update this function
		static void GetCursorPos(GLFWwindow* const window);	//call to get cursor pos

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

/********************** FPS **********************/
	float fps;

/********************** Keyboard **********************/
	static bool myKeys[TOTAL_CONTROLS];	//all keys
	static char inputChar[OPEN];	//for char keys

/********************** mouse **********************/
	static int mouseRightButton;
	static int mouseLeftButton;

/********************** mouse scroll **********************/
	static double scrollxPos;
	static double scrollyPos;

/********************** cursor **********************/
	static Vector3 cursorPos;
};

#endif