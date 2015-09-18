#include "Controller.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

const unsigned char Controller::FPS = 60; // FPS of this game (ONLY RELEASE MODE CAN RUN SMOOTHLY AT 170FPS MAX)
const unsigned int Controller::frameTime = 1000 / FPS; // time for each frame

//mouse
double Controller::mouse_last_x = 0.0, Controller::mouse_last_y = 0.0,
Controller::mouse_current_x = 0.0, Controller::mouse_current_y = 0.0,
Controller::mouse_diff_x = 0.0, Controller::mouse_diff_y = 0.0;
int Controller::mouseRightButton = 0, Controller::mouseLeftButton = 0;
double Controller::camera_yaw = 0.0, Controller::camera_pitch = 0.0;

//yaw and pitch angle
double Controller::yawAngle = 0.0;
double Controller::pitchAngle = 0.0;

/********************* constructor / destructor *********************/
Controller::Controller() : currentModel(NULL), currentView(NULL), myKeys(NULL)
{
}

Controller::~Controller()
{
	currentModel = NULL;
	currentView = NULL;
	myKeys = NULL;
}

/******************** core functions **********************/
void Controller::Init()
{
	//set both timers to 0
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_thread1 = 0.0;
	m_dAccumulatedTime_thread2 = 0.0;

	//mouse button
	mouseLeftButton = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT);
	mouseRightButton = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT);

	//hide the cursor
	glfwSetInputMode(currentView->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Controller::RunGameLoop(bool* myKeys)
{
}

void Controller::Exit()
{
}

/********************** controller functions **********************/
bool Controller::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/********************** mouse **********************/
bool Controller::GetMouseUpdate()
{
	glfwGetCursorPos(currentView->getWindow(), &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;
	//Calculate the yaw and pitch
	camera_yaw = (float) mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
	camera_pitch = (float) mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );
	
	// Do a wraparound if the mouse cursor has gone out of the deadzone
	if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > currentView->getScreenWidth() - m_window_deadzone))
	{
		mouse_current_x = currentView->getScreenWidth() >> 1;
		glfwSetCursorPos(currentView->getWindow(), mouse_current_x, mouse_current_y);
	}
	if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > currentView->getScreenHeight() - m_window_deadzone))
	{
		mouse_current_y = currentView->getScreenHeight() >> 1;
		glfwSetCursorPos(currentView->getWindow(), mouse_current_x, mouse_current_y);
	}
	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;
	 return false;
}

double Controller::getCameraYaw()
{
	return camera_yaw;
}

double Controller::getCameraPitch()
{
	return camera_pitch;
}

void Controller::InitCurrentModel()
{
	currentModel->Init();
}

void Controller::InitCurrentView()
{
	currentView->Init();
}

/********************** getter setter **********************/
bool* Controller::getKeyPressed(){return myKeys;}
double Controller::getYawAngle(){return yawAngle;}
double  Controller::getPitchAngle(){return pitchAngle;}
void Controller::incrementPitchAngle(float i){pitchAngle += i;}
void Controller::incrementYawAngle(float i){yawAngle += i;}
void Controller::setYawAngle(float y){yawAngle = y;}
void Controller::setPitchAngle(float p){pitchAngle = p;}
float Controller::getFPS(){return fps;}
