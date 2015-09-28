#include "View_MainMenu.h"

View_Main_Menu::View_Main_Menu(){}

View_Main_Menu::View_Main_Menu(Model_MainMenu* model, unsigned short console_width, unsigned short console_height, MODE mode) :
	View(model, console_width, console_height, mode)
{
	this->model = model;
}

View_Main_Menu::~View_Main_Menu()
{
}

/********************** Core functions *****************************/
void View_Main_Menu::Init()
{
	/* Set up basic stuff */
	View::StartInit();
}

void View_Main_Menu::Render(const float fps)
{
	/* Set up basic stuff */
	View::StartRendering(fps);

	RenderCollideBox();
	RenderObject();
	RenderHUD();
}

void View_Main_Menu::RenderCollideBox()
{
	for(vector<Object*>::iterator it = model->getObject()->begin(); it != model->getObject()->end(); ++it)
	{
		Object* o = (Object*)*it;

		if( !o->getActive() )
			continue;

		modelStack.PushMatrix();
		Vector3 pos = o->getBbox()->position;
		modelStack.Translate(pos.x, pos.y, pos.z);
		modelStack.Scale(o->getBbox()->scale.x, o->getBbox()->scale.y, o->getBbox()->scale.z);
		RenderMesh(Geometry::meshList[Geometry::GEO_DEBUG_CUBE], false);
		modelStack.PopMatrix();
	}
}

void View_Main_Menu::RenderHUD()
{
	//On screen text
	if(Geometry::meshList[Geometry::GEO_AR_CHRISTY] != NULL)
	{
		std::ostringstream ss;	//universal
		
		/* FPS */
		ss.precision(5);
		ss << "FPS: " << fps;
		RenderTextOnScreen(Geometry::meshList[Geometry::GEO_AR_CHRISTY], ss.str(), Color(1, 1, 0), 76, 55, 66);
		ss.str("");

		/* Pos */
		ss << "Pos: " << model->getCamera()->position;
		RenderTextOnScreen(Geometry::meshList[Geometry::GEO_AR_CHRISTY], ss.str(), Color(1, 0, 1), 76, 55, 32);
	}
}

void View_Main_Menu::RenderObject()
{
	/* Renders all objects */
	for(vector<Object*>::iterator it = model->getObject()->begin(); it != model->getObject()->end(); ++it)
	{
		Object* o = (Object*)*it;

		if(o->getActive())
		{
			modelStack.PushMatrix();
			modelStack.LoadMatrix( *(o->getTRS()) );
			RenderMesh(o->getMesh(), false);
			modelStack.PopMatrix();
		}
	}
}

void View_Main_Menu::SetModel(Model_MainMenu* model)
{
	this->model = model;
}

void View_Main_Menu::Exit()
{
	View::Exit();
}
