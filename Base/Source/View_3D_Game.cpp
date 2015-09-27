#include "View_3D_Game.h"

View_3D_Game::View_3D_Game(){}

View_3D_Game::View_3D_Game(Model_Gameplay* model, unsigned short console_width, unsigned short console_height, MODE mode) :
	View(model, console_width, console_height, mode)
{
	this->model = model;
}

View_3D_Game::~View_3D_Game()
{
}

/********************** Core functions *****************************/
void View_3D_Game::Init()
{
	/* Set up basic stuff */
	View::StartInit();
}

void View_3D_Game::Render(const float fps)
{
	/* Set up basic stuff */
	View::StartRendering(fps);

	RenderCollideBox();
	RenderObject();
	RenderHUD();
}

void View_3D_Game::RenderCollideBox()
{
	for(vector<Object*>::iterator it = model->getObject()->begin(); it != model->getObject()->end(); ++it)
	{
		Object* o = (Object*)*it;

		if( !o->active )
			continue;

		modelStack.PushMatrix();
		Vector3 pos = o->getBbox()->position;
		modelStack.Translate(pos.x, pos.y, pos.z);
		modelStack.Scale(o->getBbox()->scale.x, o->getBbox()->scale.y, o->getBbox()->scale.z);
		RenderMesh(Geometry::meshList[Geometry::GEO_DEBUG_CUBE], false);
		modelStack.PopMatrix();
	}
}

void View_3D_Game::RenderHUD()
{
	//On screen text
	if(Geometry::meshList[Geometry::GEO_AR_CHRISTY] != NULL)
	{
		std::ostringstream ss;	//universal
		
		/* FPS */
		ss.precision(5);
		ss << "FPS: " << fps;
		RenderTextOnScreen(Geometry::meshList[Geometry::GEO_AR_CHRISTY], ss.str(), Color(1, 1, 0), 6, 18, 8);
		ss.str("");

		/* Pos */
		ss << "Pos: " << model->getCamera()->position;
		RenderTextOnScreen(Geometry::meshList[Geometry::GEO_AR_CHRISTY], ss.str(), Color(1, 0, 1), 6, 28, 4);
	}
}

void View_3D_Game::RenderObject()
{
	/* Renders all objects */
	for(vector<Object*>::iterator it = model->getObject()->begin(); it != model->getObject()->end(); ++it)
	{
		Object* o = (Object*)*it;

		if(o->getActive())
		{
			modelStack.PushMatrix();
			modelStack.LoadMatrix( *(o->getTRS()) );
			RenderMesh(o->getMesh(), o->getLight());
			modelStack.PopMatrix();
		}
	}
}

void View_3D_Game::SetModel(Model_Gameplay* model)
{
	this->model = model;
}

void View_3D_Game::Exit()
{
	View::Exit();
}
