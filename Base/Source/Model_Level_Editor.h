#ifndef MODEL_LEVEL_EDITOR_H
#define MODEL_LEVEL_EDITOR_H
#include "Model_Gameplay.h"

class Model_Level_Editor : public Model
{
public:

	/** UI List **/
	enum UI_LIST
	{
		/* UIs */
		UI_BLOCK_SELECTION_BAR,
		UI_SIDE_BAR,
		UI_SELECT_TILEMAP_MENU,

		/* Model stuff (Compulsory, must add this section to all enums concerning UI_Object_List) */
		UI_CURSOR,

		TOTAL_UI,
	};

	enum BUTTON_LIST
	{
		/* Buttons */
		BUTTON_PREVIOUS_BLOCK,	//left
		BUTTON_NEXT_BLOCK,	//right
		/*BUTTON_PREVIOUS_LVL,
		BUTTON_NEXT_LVL,
		BUTTON_SELECT_NEW_MAP,
		BUTTON_CHANGE_TILE_MAP,*/

		TOTAL_BUTTON,
	};

	/** States **/
	enum STATE
	{
		ADD_NEW_MAP,
		//add new map to list of maps

		ADD_NEW_LAYER,
		//add new layer to current map

		EDIT_MAP,
		//open current map in edit mode

		EDIT_LAYER,
		//open current layer of current map in edit mode

		CHOOSE_TILE_MAP,
		//choose tile map to load, once map and layer selected

		DEFAULT,
	};

	/* If doing action, certain other stuff need to stop */
	enum ACTIONS
	{
		SELECTING_TILES,
		NONE,
		TOTAL_ACTIONS,
	};

	ACTIONS currentAction;

	/* TileMap stuff */
	Geometry::TILE_MAP current_TileMap;	//current tilemap to use
	int currentBlock;	//current block to add
	Vector3 tile_startPos;	//starting pos of tiles
	float tileSpacing;	//spacing for displaying tiles in editor
	float tileScale;	//scale of tiles

	/* Path for map file and tile map */
	int currentLayer;	//current layer index of current map
	string currentMapName;	//curent map
	vector<Map*> mapList;
	char* tileMapPath;

	/* blocks */
	Physics moveBlock;	//physics to move blocks
	bool shiftBlock_Left, shiftBlock_Right;
	Vector3 newPos;	//new pos to reach
	
	/* Internal */
	STATE state;

	/* Utilities */
	static string name;
	Vector3 start, end, checkStart, checkEnd;	//for collision
	Vector3 pos, scale;

/*********** constructor/destructor ***************/
	Model_Level_Editor();
	~Model_Level_Editor();

/*********** core functions ***************/
	virtual void Init();
	virtual void NewStateSetup();
	virtual void Update(double dt, bool* myKeys, Vector3& cursorPos);

	virtual void Exit();

/*********** Utilities ***************/
	
};

#endif