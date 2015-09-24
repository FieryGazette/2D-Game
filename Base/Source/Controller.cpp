#include "Controller.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

const unsigned char Controller::FPS = 60; // FPS of this game (ONLY RELEASE MODE CAN RUN SMOOTHLY AT 170FPS MAX)
const unsigned int Controller::frameTime = 1000 / FPS; // time for each frame

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

void Controller::UpdateKeys()
{
}

void Controller::UpdateKeyPressed()
{
}

void Controller::UpdateMouse()
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

/********************** getter setter **********************/
float Controller::getFPS(){return fps;}
