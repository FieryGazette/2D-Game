#include "Model_Level_Editor.h"

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
}

//Param 1: pass in the map file you want to edit
//Param 2: pass in the array of tilemaps
void Model_Level_Editor::EditNewMap(Map& mapToEdit, vector<string>* tileMapList)
{
	/* Current layer to edit is layer 0 */
	currentLayer = 0;

	this->mapToEdit = &mapToEdit;
}

void Model_Level_Editor::Update(double dt, bool* myKeys, Vector3 cursorPos)
{
	/* If hit and click layer option, current layer selected */

	/* If hit and click checkbox beside layer option, layer turn invisible/not visible */

	/* If hit right arrow, scroll right, if hit left arrow, scroll left */

	/* If click on a tile, that tile is selectewd */

	/* Check cursor pos.x / tileSize and cursor pos.y / tileSize to get current tile */

	/* Left click == add tile */

	/* Right click == remove the tile */

}

void Model_Level_Editor::Exit()
{
}