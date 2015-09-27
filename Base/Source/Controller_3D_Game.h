#ifndef CONTROLLER_3D_GAME_H
#define CONTROLLER_3D_GAME_H
#include "Controller.h"

/**************************************************
	For 3D Game with mouse control
**************************************************/

class Controller_3D_Game : public Controller
{
/********************** Models **********************/
	Model_Gameplay* Gameplay; 
	Model_Level_Editor* Level_Editor;
	Model_MainMenu* mainMenu;

/********************** Views **********************/
	View_Main_Menu* view_MainMenu;
	View_Level_Editor* view_LevelEditor;
	View_3D_Game* view_3D_Game;

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

public:
/*********************** For scrolling /**********************/
	static void setScrollX(double p);
	static void setScrollY(double p);

/******************** core functions **********************/
	/** Init **/
	void Init();

	//anything special to init for view and model?
	virtual void InitCurrentView();
	virtual void InitCurrentModel();
	void InitControls();	//all keys inputs

	/** Update **/
	virtual void Run();
		virtual void UpdateMouse();	//mouse stuff, cursor etc.
		virtual void UpdateKeys();	//keyboard and mouse button
		virtual void UpdateKeyPressed();	//if a key is pressed, update this function

		/** Switching models **/
		void SwitchModels();	//for update changing models, like main menu to game

	/** Mouse utilities **/
	static void GetCursorPos(GLFWwindow* const window);	//call to get cursor pos

	/** Exit **/
	virtual void Exit();

/********************* getter/setters *********************/
	bool* getKeyPressed();

/********************* constructor / destructor *********************/
	Controller_3D_Game();
	~Controller_3D_Game();
};

#endif