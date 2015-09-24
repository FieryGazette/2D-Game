#ifndef VIEW_MAIN_MENU_H
#define VIEW_MAIN_MENU_H
#include "View.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

/**
 Everything in view class will be using Objects class for TRS and other info
 **/
class View_Main_Menu : public View
{
/********************** model and view ptr **********************/
	Model_MainMenu* model;
public:
/********************** constructor/destructor *****************************/
	View_Main_Menu();
	View_Main_Menu(Model_MainMenu* model, unsigned short console_width, unsigned short console_height, MODE mode);
	~View_Main_Menu();

/********************** Core functions *****************************/
	virtual void Init();
	virtual void Render(const float fps);
	virtual void Exit();

/**************** render ****************/
	void RenderObject();
	void RenderCollideBox();
	void RenderHUD();

/**************** Utilites ******************/
	void SetModel(Model_MainMenu* model);
};

#endif