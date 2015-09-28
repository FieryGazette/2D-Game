#include "View_LevelEditor.h"

View_Level_Editor::View_Level_Editor(){}

View_Level_Editor::View_Level_Editor(Model_Level_Editor* model, unsigned short console_width, unsigned short console_height, MODE mode) :
	View(model, console_width, console_height, mode)
{
	this->model = model;
}

View_Level_Editor::~View_Level_Editor()
{
}

/********************** Core functions *****************************/
void View_Level_Editor::Init()
{
	/* Set up basic stuff */
	View::StartInit();
}

void View_Level_Editor::Render(const float fps)
{
	Vector3 pos11, scale11;

	/* Set up basic stuff */
	View::StartRendering(fps);

	/** UI **/
	RenderUI();

	/** Button **/
	RenderButton();

	/*************** Render TileMap ***************/
	//Geometry::TILE_MAP current_TileMap;	//current tilemap to use
	//Vector3 tile_startPos, tileScale;
	//pos11, scale11;
	pos11 = model->tile_startPos;
	Vector3 selector;
	float t_scale = (1.f / Geometry::tileMap_List[model->current_TileMap].tileScale) * model->tileScale;

	for(int i = 1; i <= Geometry::tileMap_List[model->current_TileMap].totalTiles; ++i)	//loop thru all tiles
	{
		Render2DTile(Geometry::tileMap_List[model->current_TileMap].mesh, false, t_scale, pos11.x, pos11.y, pos11.z, i);

		if( model->currentBlock == i )	//selected this block
		{
			RenderMeshIn2D(Geometry::meshList[Geometry::GEO_SELECTOR], false, model->tileScale * 1.1f, model->tileScale * 1.1f, 1, pos11.x, pos11.y, pos11.z, 0);
		}

		pos11.x += model->tileSpacing;	//go towards x positive
	}
}

void View_Level_Editor::RenderCollideBox()
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

void View_Level_Editor::RenderObject()
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

void View_Level_Editor::SetModel(Model_Level_Editor* model)
{
	this->model = model;
}

void View_Level_Editor::Exit()
{
	View::Exit();
}
