#ifndef VIEW_3D_GAME_H
#define VIEW_3D_GAME_H
#include "View.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

/**
 Everything in view class will be using Objects class for TRS and other info
 **/
class View_3D_Game : public View
{
/********************** model and view ptr **********************/
	Model* model;
public:
/********************** constructor/destructor *****************************/
	View_3D_Game();
	View_3D_Game(Model* model, unsigned short console_width, unsigned short console_height, MODE mode);
	~View_3D_Game();

/********************** Core functions *****************************/
	virtual void Init();
	virtual void Render(const float fps);
	virtual void Exit();

/**************** render ****************/
	void RenderObject();
	void RenderCollideBox();
	void RenderHUD();
};

#endif