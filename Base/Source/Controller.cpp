#include "Controller.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

const unsigned char Controller::FPS = 60; // FPS of this game (ONLY RELEASE MODE CAN RUN SMOOTHLY AT 170FPS MAX)
const unsigned int Controller::frameTime = 1000 / FPS; // time for each frame
double Controller::scrollxPos = 0.f;
double Controller::scrollyPos = 0.f;
bool Controller::myKeys[TOTAL_CONTROLS] = {false};
char Controller::inputChar[OPEN] = {0};

/********************** mouse **********************/
 Vector3 Controller::cursorPos;
int Controller::mouseRightButton;
int Controller::mouseLeftButton;

/********************* constructor / destructor *********************/
Controller::Controller() : currentModel(NULL), currentView(NULL)
{
}

Controller::~Controller()
{
	currentModel = NULL;
	currentView = NULL;
}

/******************** core functions **********************/
void Controller::Init()
{
	//set both timers to 0
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_thread1 = 0.0;
	m_dAccumulatedTime_thread2 = 0.0;
}

void Controller::RunGameLoop()
{
	/* Any stuff to set up? */
}

void Controller::Exit()
{
}

void scroll(GLFWwindow* window,double x,double y)
{
	Controller::setScrollX(x);
	Controller::setScrollY(y);
}

void Controller::setScrollX(double p)
{
	scrollxPos = p;
}

void Controller::setScrollY(double p)
{
	scrollyPos = p;
}


void Controller::UpdateKeys()
{
	/** Set all keys to false **/
	for(unsigned i = 0; i < TOTAL_CONTROLS; ++i)
		myKeys[i] = false;

	/**** See which keys are pressed ****/
	/** Keyboard **/
	for(int i = 0; i <= OPEN; ++i)
	{
		if(IsKeyPressed(inputChar[i]))
			myKeys[i] = true;
	}

	/** non-keyboard(mouse) **/
	mouseLeftButton = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT);
	mouseRightButton = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT);

	if(mouseLeftButton == GLFW_PRESS)
		myKeys[SHOOT] = true;
	if(mouseRightButton == GLFW_PRESS)
		myKeys[AIM] = true;

	/** Arrow key **/
	if( IsKeyPressed(VK_UP) )
		myKeys[ARROW_UP] = true;

	if( IsKeyPressed(VK_DOWN) )
		myKeys[ARROW_DOWN] = true;

	if( IsKeyPressed(VK_LEFT) )
		myKeys[ARROW_LEFT] = true;

	if( IsKeyPressed(VK_RIGHT) )
		myKeys[ARROW_RIGHT] = true;

	/** Scrolling **/
	GLFWwindow* glfwGetCurrentContext(void);
	glfwSetScrollCallback(glfwGetCurrentContext(), scroll);

	if(scrollyPos > 0.0)
	{
		myKeys[SCROLL_UP] = true;
	}
	else if(scrollyPos < 0.0)
	{
		myKeys[SCROLL_DOWN] = true;
	}
	
	if(scrollyPos != 0.0)
	{
		scrollyPos = 0.0;
	}
}

void Controller::UpdateKeyPressed()
{
	/* If a key is pressed, do stuff */
}

void Controller::UpdateMouse()
{
	GetCursorPos(View::getWindow_view());
}

void Controller::GetCursorPos(GLFWwindow* const window)
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);

	int w = View::getScreenWidth();
	int h = View::getScreenHeight();

	float posX = static_cast<float>(x) / w * Model::get2DViewWidth();
	float posY = (h - static_cast<float>(y)) / h * Model::get2DViewHeight();
	cursorPos.Set(posX, posY, 0);
}

/********************** controller functions **********************/
bool Controller::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/********************** getter setter **********************/
float Controller::getFPS(){return fps;}
