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

	/** Popup **/
	if( model->tileMap_Menu->getActive() )
	{
		RenderMeshIn2D(model->tileMap_Menu->getMesh(), false, *model->tileMap_Menu->getTRS());

		/* Button */
		RenderMeshIn2D(model->tileMap_Menu->getButton()->getMesh(), false, *model->tileMap_Menu->getButton()->getTRS());
	}

	/** Utility UI **/
	if( model->useMe.getActive() )
	{
		pos11 = model->useMe.getPosition();
		scale11 = model->useMe.getScale();
		RenderMeshIn2D(model->useMe.getMesh(), false, scale11.x, scale11.y, pos11.x, pos11.y, pos11.z, 0);
	}

	/** selection menu **/
	if( model->tileSelectionMenu->getActive() )
	{
		for(int i = 0; i < model->tileSelectionMenu->getTotalItem(); ++i)
		{
			/* So that tile sets final scale will match given scale */
			float t_scale = model->tileSelectionMenu->getItemScale();
			pos11 = model->tileSelectionMenu->getItemPos(i);
			RenderMeshIn2D(model->tileSelectionMenu->getItemMesh(i), false, t_scale, t_scale, pos11.x, pos11.y, pos11.z, 0);

			/* Selected */
			if( model->tileSelectionMenu->getCurrentItem() == i )	//selected this block
			{
				RenderMeshIn2D(Geometry::meshList[Geometry::GEO_SELECTOR], false, t_scale * 1.1f, t_scale * 1.1f, pos11.x, pos11.y, pos11.z, 0);
			}
		}
	}

	/*************** Render TileMap ***************/
	float start = model->getCamera()->position.x;
	float end = start + model->get2DViewWidth();
	pos11 = model->tile_startPos;
	Vector3 selector;

	/* So that tile sets final scale will match given scale */
	float t_scale = (1.f / Geometry::tileMap_List[model->current_TileMap].tileScale) * model->tileScale;
	
	for(int i = 1; i <= Geometry::tileMap_List[model->current_TileMap].totalTiles; ++i)	//loop thru all tiles
	{
		if( pos11.x >= start && pos11.x <= end )
		{
			Render2DTile(Geometry::tileMap_List[model->current_TileMap].mesh, false, t_scale, pos11.x, pos11.y, pos11.z, i);

			if( model->currentBlock == i )	//selected this block
			{
				RenderMeshIn2D(Geometry::meshList[Geometry::GEO_SELECTOR], false, model->tileScale * 1.1f, model->tileScale * 1.1f, pos11.x, pos11.y, pos11.z, 0);
			}
		}

		pos11.x += model->tileSpacing;	//go towards x positive
		if( pos11.x > end )
			break;
	}

	/* Test string */
	RenderTextOnScreen(Geometry::meshList[Geometry::GEO_AR_CHRISTY], "FUCK U", Color(1, 0, 1), 5, 50, 50, 2);
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
