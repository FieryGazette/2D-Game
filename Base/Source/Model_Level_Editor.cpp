#include "Model_Level_Editor.h"
/**/
/* 

Task: all class/data created in-function move to global
*/
/**/

string Model_Level_Editor::name;

/*********** constructor/destructor ***************/
Model_Level_Editor::Model_Level_Editor()
{
}

Model_Level_Editor::~Model_Level_Editor()
{
}

/*********** core functions ***************/
void Model_Level_Editor::Init()
{
	/*** Stuff that need to always re-init here ***/



	/*** Only init once stuff below here ***/
	Model::Init();

	/* Init local already? */
	if( initLocalAlready )		//yes, init alr
		return;

	initLocalAlready = true;	//no, then first time init

	/* Current map */
	currentMap = 0;	//points to map 0

	/* UI Vector resize */
	buttonList.resize(TOTAL_BUTTON);
	UI_Object_List.resize(TOTAL_UI);

	/** Utilities **/
	z = 1.f;
	InitUtilities();

	/** State Objects **/
	InitAddNewMap();
	InitAddNewLayer();
	InitEditMap();
	InitEditLayer();
	InitChooseTileMap();

	/** Blocks **/
	shiftBlock_Left = shiftBlock_Right = false;
	moveBlock.Set(20.f);	//accelerate/decelerate when shifting left/right

	/** Action **/
	currentAction = NONE;

	/**** Read from list and add maps ****/
	PopulateMapsFromTxt();

	/** Init everything of object origin in vectors **/
	for(std::vector<Object*>::iterator it = elementObject.begin(); it != elementObject.end(); ++it)
	{
		Object *go = (Object *)*it;
		go->Init();
	}

	/** States **/
	state = EDIT_LAYER;
	previousState = state;
}

void Model_Level_Editor::InitUtilities()
{
}

void Model_Level_Editor::InitAddNewMap()
{
	buttonList[BUTTON_ADD_NEW_MAP] = new Button;
	buttonList[BUTTON_ADD_NEW_MAP]->Set("Add new Map", Geometry::meshList[Geometry::GEO_BOTTOM], 32, 10, 17, 110, 1, true, 0.02f);

	new_map_textbox = new TextBox;
	new_map_textbox->Set(Geometry::meshList[Geometry::GEO_BACK], 32, 10, 50, 110, 1, true);
}

void Model_Level_Editor::InitAddNewLayer()
{
	buttonList[BUTTON_ADD_NEW_LAYER] = new Button;
	buttonList[BUTTON_ADD_NEW_LAYER]->Set("Add new Layer", Geometry::meshList[Geometry::GEO_BOTTOM], 32, 10, 17, 97, 1, true, 0.02f);
}

void Model_Level_Editor::InitEditLayer()
{
	/* blocks selector bar */
	UI_Object_List[UI_BLOCK_SELECTION_BAR] = new UI_Object;
	UI_Object_List[UI_BLOCK_SELECTION_BAR]->Set("", Geometry::meshList[Geometry::GEO_CUBE_BLUE], 
		m_2D_view_width, m_2D_view_height * 0.1f, m_2D_view_width * 0.5f, m_2D_view_height * 0.05f, z, true);
	z += 1.05f;

	/** Tilemap stuff **/
	current_TileMap = Geometry::TILEMAP_NATURE;
	tile_startPos.Set(25.f, 5.5f, z);
	currentBlock = 1;
	tileScale = 10.f;
	tileSpacing = 12.f;	//2 spaces btw each tile in display in editor
	z += 0.05f;

	/* Buttons for block */
	buttonList[BUTTON_PREVIOUS_BLOCK] = new Button;
	buttonList[BUTTON_PREVIOUS_BLOCK]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_RED], 
		15.f, 10.f, 8.f, 5.5f, z, true, 0.1f);
	z += 0.05f;

	buttonList[BUTTON_NEXT_BLOCK] = new Button;
	buttonList[BUTTON_NEXT_BLOCK]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_RED], 
		15.f, 10.f, 152.f, 5.5f, z, true, 0.1f);
	z += 0.05f;
}

void Model_Level_Editor::InitEditMap()
{
	/* side bar (select current map and layer) */
	UI_Object_List[UI_SIDE_BAR] = new UI_Object;
	UI_Object_List[UI_SIDE_BAR]->Set("", Geometry::meshList[Geometry::GEO_CUBE_RED], 
		18.f, m_2D_view_height * 0.9f, 9.f, m_2D_view_height * 0.55f, z, true);
	z += 0.05f;
}

void Model_Level_Editor::InitChooseTileMap()
{
	/* Button for selecting tilemap */
	buttonList[BUTTON_CHANGE_TILE_MAP] = new Button;
	buttonList[BUTTON_CHANGE_TILE_MAP]->Set("Select TileMap", Geometry::meshList[Geometry::GEO_CUBE_GREEN], 
		35.f, 10.f, 18.f, 55.5f, z, true, 0.1f);

	/* pop-up for selecting tile map */
	tileMap_Menu = new Popup;
	tileMap_Menu->Set("", Geometry::meshList[Geometry::GEO_CUBE_GREEN], 
		m_2D_view_width * 0.85f, m_2D_view_height * 0.85f, m_2D_view_width * 0.5f, m_2D_view_height * 0.5f, z, false);
	z += 0.5f;

	/* Selection menu */
	tileSelectionMenu = new Selection_Menu;
	tileSelectionMenu->Set(m_2D_view_height * 0.75f, m_2D_view_height * 0.7f, m_2D_view_width * 0.5f, m_2D_view_height * 0.5f, z, false);

	for(int i = 0; i < Geometry::TOTAL_TILEMAP; ++i)
	{
		tileSelectionMenu->AddItem(Geometry::tileMap_List[i].previewMesh);
	}

	tileSelectionMenu->Init();
	z += 0.5f;
}

void Model_Level_Editor::PopulateMapsFromTxt()
{
}

void Model_Level_Editor::Update(double dt, bool* myKeys)
{
	Model::Update(dt, myKeys);

	/************************************* Switching state *************************************/
	if( myKeys[AIM] )
	{
		switchState = true;
		currentState = IN_GAME;
	}

	/** Selecting new tilemap **/
	/** select new tileMap **/
	if( buttonList[BUTTON_CHANGE_TILE_MAP]->CollisionDetection(cursor, myKeys[SHOOT]) )
	{
		//change to edit map, if click again, when button cools down then change back to previous state
		if( state != CHOOSE_TILE_MAP )
		{
			previousState = state;
			state = CHOOSE_TILE_MAP;
			NewStateSetup();
		}
	}

	/** Selecting/Adding map **/
	if( buttonList[BUTTON_ADD_NEW_MAP]->CollisionDetection(cursor, myKeys[SHOOT]) )
	{
		state = ADD_NEW_MAP;
	}
	if( buttonList[BUTTON_ADD_NEW_LAYER]->CollisionDetection(cursor, myKeys[SHOOT]) )
	{
	}

	/** Type something **/
	new_map_textbox->CollisionDetection(cursor, myKeys[SHOOT]);

	new_map_textbox->Update(dt);

	/************************************* Update state *************************************/
	switch ( state )
	{
	case ADD_NEW_MAP:
		{
			UpdateAddNewMap(dt, myKeys);
			break;
		}
	case ADD_NEW_LAYER:
		{
			UpdateAddNewLayer(dt, myKeys);
			break;
		}
	case EDIT_MAP:
		{
			UpdateEditMap(dt, myKeys);
			break;
		}
	case EDIT_LAYER:
		{
			UpdateEditLayer(dt, myKeys);
			break;
		}
	case CHOOSE_TILE_MAP:
		{
			UpdateChooseTileMap(dt, myKeys);
			break;
		}
	}

	/******************************** Update any neccessary stuff ********************************/
	for(int i = 0; i < UI_Object_List.size(); ++i)
	{
		UI_Object_List[i]->Update(dt);
	}
}

void Model_Level_Editor::UpdateAddNewMap(double dt, bool* myKeys)
{
	/* Name for map */
	cout << "Enter map name: ";
	getline(cin, name);

	/* Add to textfile */
	//check if it already exists
	if( !readFromFile( map_list, name ) )
	{
		ostringstream ss;

		/* create and add this map to list */
		ss.str("");
		ss << mapList.size() + 1 << ": " << name;
		writeToFile(map_list, ss.str());

		/* Create new txt file for this map, name is index of this map */
		ss.str("");
		ss << "Maps//" << mapList.size() + 1 << ".txt";
		writeToFile(ss.str(), "");

		Map* map_ptr = new Map(name, mapList.size());

		mapList.push_back(map_ptr);

		/* current map is now this newly created map */
		currentMap = mapList.back()->getIndex();	

		cout << "Map created: " << mapList.back()->getName() << endl;
	}
	else
		cout << "Map existed: " << name << endl;

	currentMapName = name;

	state = ADD_NEW_LAYER;
}

void Model_Level_Editor::UpdateAddNewLayer(double dt, bool* myKeys)
{
	/* Added one layer: at least have base layer */
	//create txt file for this map
	ostringstream ss;
	ostringstream ss1;

	ss.str("");
	ss << "Lvl: " << 0 << "  Tilesize: " << 32;
	ss1.str("");
	ss1 << "Maps//" << mapList[currentMap]->getIndex() + 1 << ".txt";
	writeToFile(ss1.str(), ss.str());

	state = EDIT_MAP;
}

void Model_Level_Editor::UpdateEditLayer(double dt, bool* myKeys)
{
	/** Edit tiles **/
	start = cursor->getPosition() - cursor->getScale() * 0.5f;
	end = cursor->getPosition() + cursor->getScale() * 0.5f;

	/******************************** If hit and click layer option, current layer selected ********************************/

	/******************************** If hit and click checkbox beside layer option, layer turn invisible/not visible ********************************/

	/******************************** If hit right arrow, scroll right, if hit left arrow, scroll left ********************************/
	if( currentAction != SELECTING_TILES )
	{
		//right
		if( buttonList[BUTTON_NEXT_BLOCK]->CollisionDetection(cursor, myKeys[SHOOT]) )
		{
			if( tile_startPos.x <= 0.f )
			{
				currentAction = SELECTING_TILES;
				newPos = tile_startPos;
				newPos.x += 60;
			}
		}

		//left
		else if( buttonList[BUTTON_PREVIOUS_BLOCK]->CollisionDetection(cursor, myKeys[SHOOT]) )
		{
			currentAction = SELECTING_TILES;
			newPos = tile_startPos;
			newPos.x -= 60;
		}
	
		/* Not clicking a button, then able to select tiles */
		else if(myKeys[SHOOT])
		{
			/** If check is not SELECTING_TILES again in case in this frame click button and a tile together **/

			/******************************** If click on a tile, that tile is selected ********************************/
			Collision::setStartEnd2D(tile_startPos, Vector3(tileScale, tileScale, tileScale), checkStart, checkEnd);

			/** Check collide with all blocks **/
			for(int i = 1; i <= Geometry::tileMap_List[current_TileMap].totalTiles; ++i)
			{
				if( Collision::QuickAABBDetection2D(start, end, checkStart, checkEnd) )
				{
					currentBlock = i;
					break;
				}

				/** If no collide, go further to next block **/
				checkStart.x += tileSpacing;
				checkEnd.x += tileSpacing;
			}
		}
	}
	/******************************** Check cursor pos.x / tileSize and cursor pos.y / tileSize to get current tile ********************************/

	/******************************** Left click == add tile ********************************/

	/******************************** Right click == remove the tile ********************************/

	/******************************** Shift blocks ********************************/
	if( currentAction == SELECTING_TILES )
	{
		//opp. since move function returns false when still moving and true if reached
		if( moveBlock.Move(tile_startPos, 220.5f, newPos, dt) )
		{
			currentAction = NONE;
		}
	}
}

void Model_Level_Editor::UpdateEditMap(double dt, bool* myKey)
{
	/** Add/Delete layers **/

	//cout << "hahahhaah" << endl;
}

void Model_Level_Editor::UpdateChooseTileMap(double dt, bool* myKeys)
{
	/** Check if quit selection menu **/
	if( tileMap_Menu->CollisionDetection(cursor, myKeys[SHOOT]) )
	{
		state = previousState;
		previousState = CHOOSE_TILE_MAP;
		NewStateSetup();
	}

	/** Check select which tile map **/
	if( tileSelectionMenu->CollisionDetection(cursor, myKeys[SHOOT]) )
	{
		current_TileMap = static_cast<Geometry::TILE_MAP>( tileSelectionMenu->getCurrentItem() );
	}
}

void Model_Level_Editor::NewStateSetup()
{
	/* Exit previous state */
	OldStateExit();

	/* Init new state */
	switch ( state )
	{
	case CHOOSE_TILE_MAP:
		tileMap_Menu->SetActive(true);
		tileSelectionMenu->SetActive(true);
		break;
	case EDIT_LAYER:
		tile_startPos.SetXY(25.f, 5.5f);
		break;
	}
}

void Model_Level_Editor::OldStateExit()
{
	switch ( previousState )
	{
	case CHOOSE_TILE_MAP:
		tileSelectionMenu->SetActive(false);
		tileMap_Menu->SetActive(false);
		break;
	case EDIT_LAYER:
		break;
	}
}

void Model_Level_Editor::Exit()
{
}