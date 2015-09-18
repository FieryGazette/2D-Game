#include "Controller_3D_Game.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
bool Controller_3D_Game::myKeys[TOTAL_CONTROL] = {false};
char Controller_3D_Game::inputChar[PAUSE + 1] = {0};
double Controller_3D_Game::scrollxPos = 0.f;
double Controller_3D_Game::scrollyPos = 0.f;

//Scroll
void scroll(GLFWwindow* window,double x,double y)
{
	Controller_3D_Game::setScrollX(x);
	Controller_3D_Game::setScrollY(y);
}

/********************* constructor / destructor *********************/
Controller_3D_Game::Controller_3D_Game()
{
}

Controller_3D_Game::~Controller_3D_Game()
{
}

/******************** core functions **********************/
void Controller_3D_Game::Init(Model* model, View_3D_Game* view)
{
	//controls
	InitControls();

	//init view
	currentView = view;
	InitCurrentView();

	//set model
	currentModel = model;
	InitCurrentModel();

	//call last since view and model needed to be initialized first
	Controller::Init();
}

void Controller_3D_Game::InitControls()
{
	Controller::myKeys = myKeys;

	//keys
	for(int i = 0; i <= OPEN; ++i) //all 256 chars
		myKeys[i] = false;

	inputChar[FORWARD] = 'W';
	inputChar[LEFT] = 'A';
	inputChar[BACKWARD] = 'S';
	inputChar[RIGHT] = 'D';
	inputChar[CROUCH] = 'C';
	inputChar[PAUSE] = 'P';
	inputChar[OPEN] = 'O';
	inputChar[JUMP] = ' ';
	inputChar[RELOAD] = 'R';
	inputChar[FLY_UP] = 'K';
	inputChar[FLY_DOWN] = 'L';
}

void Controller_3D_Game::Run()
{
	//Main Loop
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame

	while (!glfwWindowShouldClose(currentView->getWindow()) && !IsKeyPressed(VK_ESCAPE))
	{
		//get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_thread1 += m_dElapsedTime;
		m_dAccumulatedTime_thread2 += m_dElapsedTime;

		/* fps */
		fps = (float)(1.f / m_dElapsedTime);

		/* twin threaded approach */
		if(m_dAccumulatedTime_thread1 > 0.01)	//update: update fps is _dAccumulatedTime_thread1 > fps
		{
			/* Init new model etc... */

			/* controls */
			UpdateKeys();

			/** model update **/
			currentModel->Update(m_dElapsedTime, myKeys);

			m_dAccumulatedTime_thread1 = 0.0;
		}
		if(m_dAccumulatedTime_thread2 > 0.003)	//render: render fps is _dAccumulatedTime_thread1 > fps
		{
			/** View update(rendering) **/
			currentView->Render(fps);	//or switch to pause screen

			m_dAccumulatedTime_thread2 = 0.0;
		}

		//Swap buffers
		glfwSwapBuffers(currentView->getWindow());
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();

		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
}

void Controller_3D_Game::UpdateKeys()
{
	/** Set all keys to false **/
	for(unsigned i = 0; i < TOTAL_CONTROL; ++i)
		myKeys[i] = false;

	/**** See which keys are pressed ****/
	/** Keyboard **/
	for(int i = 0; i <= OPEN; ++i) //all 256 chars
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

 void Controller_3D_Game::setScrollX(double p)
 {
	 scrollxPos = p;
 }

void Controller_3D_Game::setScrollY(double p)
{
	 scrollyPos = p;
}

void Controller_3D_Game::Exit()
{
	Controller::Exit();

	currentView->Exit();
	currentModel->Exit();
}

