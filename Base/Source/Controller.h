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
	void Run();
	void Exit();

/********************** controller functions **********************/
	static bool IsKeyPressed(unsigned short key);
	static char characterPressed();

/********************** getter setter **********************/
	float getFPS();
	bool* getKeyPressed();
	static Vector2 GetCursorPos();

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
	void InitCurrentView();
	void InitCurrentModel();
	void InitControls();


	/** Switching models **/
	void SwitchModels();	//for update changing models, like main menu to game

	/* Call only when needed: if your program needs key and mouse press */
	void UpdateKeys();
	void UpdateMouse();
	void UpdateKeyPressed();	//if a key is pressed, update this function
	static Vector2 GetCursor(GLFWwindow* const window);	//call to get cursor pos

/********************** Input **********************/
	MODE type;	//mode

/********************** model and view ptr **********************/
	Model* currentModel; //points to the current model to run
	View* currentView;	//points to the current vuew to run

/********************** Models **********************/
	Model_Gameplay* Gameplay; 
	Model_Level_Editor* Level_Editor;
	Model_MainMenu* mainMenu;

/********************** Views **********************/
	View_Main_Menu* view_MainMenu;
	View_Level_Editor* view_LevelEditor;
	View_3D_Game* view_3D_Game;

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
	static vector<char> typableCharacters;	//char keys that are valid text inputs

/********************** mouse **********************/
	static int mouseRightButton;
	static int mouseLeftButton;

/********************** mouse scroll **********************/
	static double scrollxPos;
	static double scrollyPos;

/********************** cursor **********************/
	static Vector2 cursorPos;
};

#endif