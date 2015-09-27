#ifndef VIEW_LEVEL_EDITOR_H
#define VIEW_LEVEL_EDITOR_H
#include "View.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

/**
 Everything in view class will be using Objects class for TRS and other info
 **/
class View_Level_Editor : public View
{
/********************** model and view ptr **********************/
	Model_Level_Editor* model;
public:
/********************** constructor/destructor *****************************/
	View_Level_Editor();
	View_Level_Editor(Model_Level_Editor* model, unsigned short console_width, unsigned short console_height, MODE mode);
	~View_Level_Editor();

/********************** Core functions *****************************/
	virtual void Init();
	virtual void Render(const float fps);
	virtual void Exit();

/**************** render ****************/
	void RenderObject();
	void RenderCollideBox();

/**************** Utilites ******************/
	void SetModel(Model_Level_Editor* model);
};

#endif