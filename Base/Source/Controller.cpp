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
vector<char> Controller::typableCharacters;

/********************** mouse **********************/
 Vector2 Controller::cursorPos;
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
	/** Timers: set both timers to 0 **/
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_thread1 = 0.0;
	m_dAccumulatedTime_thread2 = 0.0;

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
}

void Controller::InitControls()
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

	/* Typable characters */
	for(char a = 'A'; a <= 'Z'; ++a)
	{
		typableCharacters.push_back(a);
	}

	typableCharacters.push_back(' ');
}

void Controller::InitCurrentModel()
{
	/* Init model and other related stuff */
	currentModel->Init();
}

void Controller::InitCurrentView()
{
	/* Init view and other related stuff */
	currentView->Init();
}

void Controller::Run()
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

void Controller::Exit()
{
	currentView->Exit();
	currentModel->Exit();
}

void Controller::SwitchModels()
{
	/** Switch models based on states **/
	if( !Model::getSwitchState() )	//if switch model flag is false, no need to switch
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

	/* Set switch state flag to false */
	Model::SetSwitchState(false);
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
	cursorPos = GetCursor(View::getWindow());
}

Vector2 Controller::GetCursorPos()
{
	return cursorPos;
}

Vector2 Controller::GetCursor(GLFWwindow* const window)
{
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);

	return Vector2(x, y);
}

/********************** controller functions **********************/
bool Controller::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

char Controller::characterPressed()
{
	for(int i = 0; i < typableCharacters.size(); ++i)
	{
		if( IsKeyPressed(typableCharacters[i]) )
		{
			return typableCharacters[i];
		}
	}

	return '/';	//return backslash for nothing pressed
}

bool* Controller::getKeyPressed()
{
	return myKeys;
}

/********************** getter setter **********************/
float Controller::getFPS(){return fps;}
