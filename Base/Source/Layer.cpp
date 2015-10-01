#include "Layer.h"
Collision Layer::collisionBox;

/* Constructor/destructor */
Layer::Layer()
{
	edited = false;
}

Layer::~Layer()
{
}

void Layer::Set(Geometry::TILE_MAP tileMap, int layer, bool collidable, float tileScale)
{
	this->tileMap;
	this->layer = layer;
	this->collidable = collidable;
	this->tileScale = tileScale;
}

bool Layer::LoadTileLayer(string& txt)
{
	TileMap.clear();
	int xSize, ySize;
	int yCounter = 0;	//at which y tile

	/* Find header */
	string header0 = "Layer: ";
	string header1 = "TileMap: ";
	string header2 = "TileScale: ";
	string header3 = "TilesX: ";
	string header4 = "TilesY: ";

	/* Utilities */
	//0: get layer
	//1: get tilemap
	//2: get tilescale
	//3: get tiles X
	//4: get tiles Y
	//5: load X and Y tiles
	int steps = 0;

	/* Open file */
	ifstream myfile(txt);	//overloaded constructor to open a text file imm. after declaration
	string sentence = "";

	if( myfile.is_open())
	{
		while( getline(myfile, sentence, '\n') )
		{
			switch ( steps )
			{
			case 0:
				if( searchTerm(sentence, header0) )
				{
					/* Get layer number */
					if( layer == getNumberFromRange(sentence) )
						steps++;
				}

				break;
			case 1:

				/* Get tilemap */
				if( searchTerm(sentence, header1) )
				{
					tileMap = static_cast<Geometry::TILE_MAP>(getNumberFromRange(sentence));
					steps++;
				}
				else
					return false;	//file corrupted
				break;
			case 2:

				/* Get tile scale */
				if( searchTerm(sentence, header2) )
				{
					tileScale = getNumberFromRange(sentence);
					steps++;
				}
				else
					return false;	//file corrupted
				break;
			case 3:

				/* Get tiles X */
				if( searchTerm(sentence, header3) )
				{
					xSize = getNumberFromRange(sentence);
					steps++;
				}
				else
					return false;	//file corrupted
				break;
			case 4:

				/* Get tiles Y */
				if( searchTerm(sentence, header4) )
				{
					ySize = getNumberFromRange(sentence);

					/* Resize tilemap */
					TileMap.resize(xSize);

					for(int i = 0; i < xSize; ++i)
						TileMap[i].resize(ySize);

					steps++;
				}
				else
					return false;	//file corrupted
				break;
			case 5:

				/** Read from x and y **/
				int counter = 0;	//count how many tiles taken (X)
				for(int i = 0; i < sentence.length(); ++i)	//x
				{
					int tileNum = getNumberFromRange(sentence, counter);

					TileMap[counter][yCounter] = tileNum;
				}
				yCounter++;	//go next row
				break;
			}
		}

		//reach end
		myfile.close();
	}
	else
	{
		return false;
	}

	return true;
}

void Layer::RecreateLayer(Geometry::TILE_MAP tileMap, int totalX, int totalY)
{
	TileMap.clear();

	this->tileMap = tileMap;

	TileMap.resize(totalX);

	for(int i = 0; i < totalX; ++i)
	{
		TileMap[i].resize(totalY);
	}
}

bool Layer::WriteToTxt(string& txt)
{
	return true;
}

void Layer::editTile(int& x, int& y, int TileType)
{
	if( TileType < 0 || TileType > Geometry::tileMap_List[tileMap].totalTiles )
		return;

	TileMap[x][y] = TileType;
}

void Layer::Clear()
{
	TileMap.clear();
}

bool Layer::checkCollision(Character* character)
{
	/* If is non-collision layer */
	if( !collidable )
		return false;

	bool b = false;

	for(int i = 0; i < TileMap.size(); ++i)	//X
	{
		for(int j = 0; j < TileMap[i].size(); ++j)	//Y
		{
			if( TileMap[i][j] == 0 )
				continue;

			/* Set shared collision box to current tile pos */
			collisionBox.SetForTile(i, j, tileScale);

			/* Check collision with this tile */
			b = Collision::CheckCollision(character->getObject()->collideBox, collisionBox);
		}
	}
	return b;
}

/* Getter/setter */
Geometry::TILE_MAP Layer::getTileMap(){return tileMap;}

void Layer::setLayer(int layer){this->layer = layer;}
int Layer::getLayer(){return layer;}

void Layer::SetCollidable(bool c){this->collidable = c;}
bool Layer::getCollidable(){return collidable;}

void Layer::SetTileScale(float s){this->tileScale = s;}
float Layer::getTileScale(){return tileScale;}