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

	/* UI Vector resize */
	UI_Object_List.resize(TOTAL_UI);

	/** Compulsory **/
	UI_Object_List[UI_CURSOR] = cursor;

	
	/* UI Stuff */
	float z = 1.f;
	
	/* blocks selector bar */
	UI_Object_List[UI_BLOCK_SELECTION_BAR] = new UI_Object;
	UI_Object_List[UI_BLOCK_SELECTION_BAR]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_BLUE], 
		m_2D_view_width, m_2D_view_height * 0.1f, m_2D_view_width * 0.5f, m_2D_view_height * 0.05f, z, true);
	z += 1.05f;

	/** Tilemap stuff **/
	current_TileMap = Geometry::TILEMAP_NATURE;
	tile_startPos.Set(25.f, 5.5f, z);
	currentBlock = 1;
	tileScale = 10.f;
	z += 0.05f;

	/* Buttons for block */
	UI_Object_List[BUTTON_PREVIOUS_BLOCK] = new UI_Object;
	UI_Object_List[BUTTON_PREVIOUS_BLOCK]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_RED], 
		15.f, 10.f, 8.f, 5.5f, z, true);
	z += 0.05f;

	UI_Object_List[BUTTON_NEXT_BLOCK] = new UI_Object;
	UI_Object_List[BUTTON_NEXT_BLOCK]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_RED], 
		15.f, 10.f, 152.f, 5.5f, z, true);
	z += 0.05f;

	/* side bar (select current map and layer) */
	UI_Object_List[UI_SIDE_BAR] = new UI_Object;
	UI_Object_List[UI_SIDE_BAR]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_RED], 
		18.f, m_2D_view_height * 0.9f, 9.f, m_2D_view_height * 0.55f, z, true);
	z += 0.05f;

	/* pop-up for selecting tile map */
	UI_Object_List[UI_SELECT_TILEMAP_MENU] = new UI_Object;
	UI_Object_List[UI_SELECT_TILEMAP_MENU]->Set("ASD", Geometry::meshList[Geometry::GEO_CUBE_GREEN], 
		m_2D_view_width * 0.85f, m_2D_view_height * 0.85f, m_2D_view_width * 0.5f, m_2D_view_height * 0.5f, z, false);
	z += 0.05f;

	cout << UI_Object_List.size() << endl;
	/**** Read from list and add maps ****/


	/** Init everything of object origin in vectors **/
	for(std::vector<Object*>::iterator it = elementObject.begin(); it != elementObject.end(); ++it)
	{
		Object *go = (Object *)*it;
		go->Init();
	}

	for(std::vector<UI_Object*>::iterator it = UI_Object_List.begin(); it != UI_Object_List.end(); ++it)
	{
		UI_Object *go = (UI_Object *)*it;
		go->Init();
	}
}

void Model_Level_Editor::Update(double dt, bool* myKeys, Vector3& cursorPos)
{
	Model::Update(dt, myKeys, cursorPos);

	/* Switch state */
	if( myKeys[AIM] )
	{
		switchState = true;
		currentState = IN_GAME;
	}

	/** TESTING: add new map **/
	//testing only: adding new map and layer, remove if UI completed
	if( myKeys[SHOOT] )	//first time come this mode
	{
		//ADD_NEW_MAP
		state = DEFAULT;
		myKeys[SHOOT] = false;
	}

	switch ( state )
	{
	case ADD_NEW_MAP:
		{
			/* Name for map */
			cout << "Enter map name: ";
			getline(cin, name);

			/* Add to textfile */
			//check if it already exists
			if( !readFromFile( map_list, name ) )
			{
				/* create and add this map to list */
				writeToFile(map_list, name);

				/* Create new txt file for this map */
				ostringstream ss;
				ss.str("");
				ss << "Maps//" << name << ".txt";
				writeToFile(ss.str(), "");

				Map* map_ptr = new Map(name);

				mapList.push_back(map_ptr);
			

				cout << "Map created: " << name << endl;
			}
			else
				cout << "Map existed: " << name << endl;

			currentMapName = name;

			state = ADD_NEW_LAYER;
			break;
		}
	case ADD_NEW_LAYER:
		{
			/* Added one layer: at least have base layer */
			//create txt file for this map
			ostringstream ss;
			ostringstream ss1;

			ss.str("");
			ss << "Lvl: " << 0 << "  Tilesize: " << 32;
			ss1.str("");
			ss1 << "Maps//" << name << ".txt";
			writeToFile(ss1.str(), ss.str());

			state = EDIT_MAP;
			break;
		}
	case EDIT_MAP:
		{
			/** Add/Delete layers **/

			//cout << "hahahhaah" << endl;
			break;
		}
	case EDIT_LAYER:
		/** Edit tiles **/

		break;
	case CHOOSE_TILE_MAP:
		/** Choose the tile map **/

		break;
	}

	/************************ Default case ************************/

	/* If hit and click layer option, current layer selected */

	/* If hit and click checkbox beside layer option, layer turn invisible/not visible */

	/* If hit right arrow, scroll right, if hit left arrow, scroll left */

	/* If click on a tile, that tile is selected */

	/* Check cursor pos.x / tileSize and cursor pos.y / tileSize to get current tile */

	/* Left click == add tile */

	/* Right click == remove the tile */



}

void Model_Level_Editor::NewStateSetup()
{

}

void Model_Level_Editor::Exit()
{
}