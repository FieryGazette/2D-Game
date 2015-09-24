#ifndef MODEL_LEVEL_EDITOR_H
#define MODEL_LEVEL_EDITOR_H
#include "Model_Gameplay.h"

class Model_Level_Editor : public Model
{
	enum STATE
	{
		CHOOSE_TILE_MAP,
		EDIT_LAYER,
	};

	/* Path for map file and tile map */
	int currentLayer;
	Map* mapToEdit;
	char* tileMapPath;
	vector<string>* tileMapList;

	/* Internal */
	STATE state;
public:
/*********** constructor/destructor ***************/
	Model_Level_Editor();
	~Model_Level_Editor();

/*********** core functions ***************/
	virtual void Init();

	//Param 1: pass in the map file you want to edit
	//Param 2: pass in the array of tilemaps
	void EditNewMap(Map& mapToEdit, vector<string>* tileMapList);
	virtual void Update(double dt, bool* myKeys, Vector3 cursorPos);

	virtual void Exit();
};

#endif