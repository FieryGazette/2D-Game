#ifndef CONTROLLER_3D_GAME_H
#define CONTROLLER_3D_GAME_H
#include "Controller.h"

/**************************************************
	For 3D Game with mouse control
**************************************************/

class Controller_3D_Game : public Controller
{
	/* mouse scroll */
	static double scrollxPos;
	static double scrollyPos;

	static bool myKeys[TOTAL_CONTROL];
	static char inputChar[PAUSE + 1];
public:
/******************** core functions **********************/
	void Init(Model* model, View_3D_Game* view);
		void InitControls();

	virtual void Run();
		void UpdateKeys();
	virtual void Exit();

	static void setScrollX(double p);
	static void setScrollY(double p);

/********************* constructor / destructor *********************/
	Controller_3D_Game();
	~Controller_3D_Game();
};

#endif