#ifndef MESHLIST_H
#define MESHLIST_H
#include "Mesh.h"
#include "MeshBuilder.h"
#include "DepthFBO.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Utility.h"
#include "LoadOBJ.h"
#include "LoadHmap.h"
#include "LoadTGA.h"
#include <vector>
using std::vector;

/**/
/*
	Tile map class. Contains mesh as well as total tiles.
*/
/**/
struct TileMap
{
	Mesh* mesh;
	Mesh* previewMesh;
	string name;
	int totalTiles;
	float tileScale;
};

class Geometry
{
public:
	enum TILE_MAP
	{
		TILEMAP_NATURE,
		TILEMAP_MARKET,
		TOTAL_TILEMAP,
	};

	enum GEOMETRY_TYPE
	{
		/* basic ABC */
		GEO_AXES,
		GEO_DEBUG_CUBE,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CUBE_BLUE,
		GEO_CUBE_RED,
		GEO_CUBE_GREEN,
		GEO_RING,
		GEO_CONE,

		/* sky boxxxxxxxxxxx */
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		/* UI */
		GEO_AR_CHRISTY,	//font
		GEO_CROSSHAIR,
		GEO_SELECTOR,

		/* terrain */
		GEO_SKYPLANE,
		GEO_TERRAIN,
		GEO_ICE_RINK,

		/* animation */
		GEO_GIRL,
		GEO_RUNNING_CAT,


		/* world objects */
		GEO_BUILDING,
		GEO_OBJECT,
		GEO_PAVEMENT,
		GEO_SIGNBOARD,
		GEO_LAMPPOST,
		GEO_SNOWFLAKE,

		/* police car */
		GEO_CAR_MAIN_PART,
		GEO_CAR_GLASS,
		GEO_CAR_SIREN,

		/* building */
		GEO_DERELICT_BUILDING_01,

		NUM_GEOMETRY,
	};

	/************ meshlsit ************/ 
	static Mesh* meshList[NUM_GEOMETRY];	//dynamic array for Mesh*

	/************ animation ************/ 
	static vector<SpriteAnimation*> animation;

	/************ terrain ************/
	static vector<unsigned char> m_heightMap;

	/************ TileMap ************/
	static TileMap tileMap_List[TOTAL_TILEMAP]; 

	/* core */
	static void Init();	//MUST BE CALLED ONCE: ANYWHERE
	static void Exit();
};


#endif