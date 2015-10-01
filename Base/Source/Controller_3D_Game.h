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

public:
/******************** core functions **********************/
	/** Init **/
	void Init();

	//anything special to init for view and model?
	virtual void InitCurrentView();
	virtual void InitCurrentModel();
	void InitControls();	//all keys inputs

	/** Update **/
	virtual void Run();

		/** Switching models **/
		virtual void SwitchModels();	//for update changing models, like main menu to game

	/** Exit **/
	virtual void Exit();

/********************* getter/setters *********************/
	bool* getKeyPressed();

/********************* constructor / destructor *********************/
	Controller_3D_Game();
	~Controller_3D_Game();
};

#endif