#ifndef MODEL_LEVEL_EDITOR_H
#define MODEL_LEVEL_EDITOR_H
#include "Model_Gameplay.h"

class Model_Level_Editor : public Model
{
	/** UI List **/
	enum UI_LIST
	{
		/* Buttons */
		/*BUTTON_PREVIOUS_BLOCK,
		BUTTON_NEXT_BLOCK,
		BUTTON_PREVIOUS_LVL,
		BUTTON_NEXT_LVL,
		BUTTON_SELECT_NEW_MAP,
		BUTTON_CHANGE_TILE_MAP,*/

		/* UIs */
		UI_BLOCK_SELECTION_BAR,
		/*UI_SIDE_BAR,
		UI_TOP_BAR,*/
		TOTAL_UI,
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

	/* Path for map file and tile map */
	int currentLayer;	//current layer index of current map
	string currentMapName;	//curent map
	vector<Map*> mapList;
	char* tileMapPath;
	
	/* Internal */
	STATE state;

	/* Utilities */
	static string name;
public:
/*********** vectors ***********/
	vector<UI_Object*> UI_Object_List;

/*********** constructor/destructor ***************/
	Model_Level_Editor();
	~Model_Level_Editor();

/*********** core functions ***************/
	virtual void Init();
	virtual void Update(double dt, bool* myKeys, Vector3 cursorPos);

	virtual void Exit();

/*********** Utilities ***************/
	
};

#endif