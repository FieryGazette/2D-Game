#include "Controller_3D_Game.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
double Controller_3D_Game::scrollxPos = 0.f;
double Controller_3D_Game::scrollyPos = 0.f;
bool Controller_3D_Game::myKeys[TOTAL_CONTROLS] = {false};
char Controller_3D_Game::inputChar[OPEN] = {0};

/********************** mouse **********************/
 Vector3 Controller_3D_Game::cursorPos;
int Controller_3D_Game::mouseRightButton;
int Controller_3D_Game::mouseLeftButton;

void scroll(GLFWwindow* window,double x,double y)
{
	Controller_3D_Game::setScrollX(x);
	Controller_3D_Game::setScrollY(y);
}

/**/
/*
	Controller for 2D Game. If first time come to a model, no matter in init or update function,
	will always init then. So if never even went to edit function, edit model will not even be init.
*/
/**/

/********************* constructor / destructor *********************/
Controller_3D_Game::Controller_3D_Game()
{
}

Controller_3D_Game::~Controller_3D_Game()
{
}

/******************** core functions **********************/
void Controller_3D_Game::Init()
{
	//mouse button
	mouseLeftButton = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT);
	mouseRightButton = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT);

	//hide the cursor
	glfwSetInputMode(currentView->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//controls
	InitControls();

	/*** Create views and models ***/
/********************** Models **********************/
	Gameplay = new Model_Gameplay;
	Level_Editor = new Model_Level_Editor;	
	mainMenu = new Model_MainMenu;

/********************** Views **********************/
	view_MainMenu = new View_Main_Menu(mainMenu, 975, 650, View::TWO_D);
	view_LevelEditor = new View_Level_Editor(Level_Editor, 975, 650, View::TWO_D);
	view_3D_Game = new View_3D_Game(Gameplay, 975, 650, View::TWO_D);

/********************** Initialize **********************/
	//init view
	currentView = view_3D_Game;
	InitCurrentView();

	//set model
	currentModel = Gameplay;
	InitCurrentModel();

	//call last since view and model needed to be initialized first
	Controller::Init();
}

void Controller_3D_Game::InitControls()
{
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

void Controller_3D_Game::InitCurrentModel()
{
	/* Init model and other related stuff */
	currentModel->Init();
}

void Controller_3D_Game::InitCurrentView()
{
	/* Init view and other related stuff */
	currentView->Init();
}

void Controller_3D_Game::setScrollX(double p)
{
	scrollxPos = p;
}

void Controller_3D_Game::setScrollY(double p)
{
	scrollyPos = p;
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
			SwitchModels();

			/* controls */
			UpdateMouse();
			UpdateKeys();

			/** model update **/
			currentModel->Update(m_dElapsedTime, myKeys, cursorPos);

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

void Controller_3D_Game::SwitchModels()
{
	/** Switch models based on states **/
	if( !Model::getSwitchState() )
		return;

	switch( Model::getCurrentState() )
	{
	case Model::IN_GAME:
		currentModel = Gameplay;
		currentModel->Init();
		currentView = view_3D_Game;
		//currentView->SetModel(currentModel);	//need set model since edit and game use same view update 2: no need already
		break;
	case Model::EDIT_LEVEL:
		currentModel = Level_Editor;
		currentModel->Init();
		currentView = view_LevelEditor;
		break;
	case Model::MAIN_MENU:
		currentModel = mainMenu;
		currentModel->Init();
		currentView = view_MainMenu;
		break;
	}

	Model::SetSwitchState(false);
}

void Controller_3D_Game::UpdateKeys()
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

void Controller_3D_Game::UpdateKeyPressed()
{
	/* If a key is pressed, do stuff */
}

void Controller_3D_Game::UpdateMouse()
{
	GetCursorPos(View::getWindow_view());
}

void Controller_3D_Game::GetCursorPos(GLFWwindow* const window)
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

bool* Controller_3D_Game::getKeyPressed()
{
	return myKeys;
}

void Controller_3D_Game::Exit()
{
	Controller::Exit();

	currentView->Exit();
	currentModel->Exit();
}

