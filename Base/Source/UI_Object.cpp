#include "UI_Object.h"
#include "Controller.h"
#include "View.h"
Vector3 UI_Object::start, UI_Object::end, UI_Object::checkStart, UI_Object::checkEnd;

/*** constructor / destructor ***/
UI_Object::UI_Object()
{
}

UI_Object::~UI_Object()
{
}

/*** core ***/
void UI_Object::Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active)
{
	this->word = word;
	Entity::Set(mesh, Vector3(scaleX, scaleY, 1), Vector3(posX, posY, zHeight), active);
}

bool UI_Object::CollisionDetection(UI_Object* checkMe, bool clicked)
{
	/* Start and end */
	start = position - scale * 0.5f;
	end = position + scale * 0.5f;
	checkStart = checkMe->position - checkMe->scale * 0.5f;
	checkEnd = checkMe->position + checkMe->scale * 0.5f;

	return Collision::QuickAABBDetection2D(start, end, checkStart, checkEnd);
}

/* Getter setter */
void UI_Object::SetPosition(Vector3& pos)
{
	this->position.SetXY(pos.x, pos.y);
}

Vector3 UI_Object::getPosition()
{
	return position;
}

void UI_Object::SetScale(Vector3 scale)
{
	this->scale = scale;
}

Vector3 UI_Object::getScale()
{
	return scale;
}

Mesh* UI_Object::getMesh()
{
	return mesh;
}

bool UI_Object::getActive()
{
	return active;
}

void UI_Object::SetActive(bool active)
{
	this->active = active;
}

string UI_Object::getWord()
{
	return word;
}

float UI_Object::getWordScale()
{
	return wordScale * scale.y;
}

void UI_Object::Update(double dt)
{
}

void UI_Object::Draw()
{
	if( getActive() )
	{
		View::RenderMeshIn2D(mesh, false, scale.x, scale.y, position.x, position.y, position.z, 0);

		/** word **/
		if( word.length() > 0 )
		{
			View::RenderTextOnScreen(Geometry::meshList[Geometry::GEO_AR_CHRISTY], word, Color(1, 0, 1), getWordScale(), 
				position.x, position.y, position.z);
		}
	}
}

/** Button **/
float Button::wordScale = 0.4f;
double Button::depressionTime = 0.2f;

/*** constructor / destructor ***/
Button::Button()
{
	depressionTimer = 0.0;
	clicked = false;
}

Button::~Button()
{
}

/*** core ***/
void Button::Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active, float depression)
{
	UI_Object::Set(word, mesh, scaleX, scaleY, posX, posY, zHeight, active);
	this->depression = depression;
}

bool Button::CollisionDetection(UI_Object* checkMe, bool activate)
{
	/* If clicked before already, not considerd collide */
	if( clicked )
	{
		return false;
	}

	/* Start and end */
	bool b = false;
	if( activate )
	{
		b = UI_Object::CollisionDetection(checkMe, activate);

		if( b && !clicked )
		{
			clicked = true;
			position -= scale * depression;
		}
	}

	return b;
}

void Button::Update(double dt)
{
	if( clicked )
	{
		depressionTimer += dt;

		if( depressionTimer >= depressionTime )
		{
			depressionTimer = 0.f;
			position += scale * depression;
			clicked = false;
		}
	}
}

void Button::Draw()
{
	UI_Object::Draw();
}

bool Button::getClicked()
{
	return clicked;
}

/** Popup **/
/*** constructor / destructor ***/
Popup::Popup()
{
}

Popup::~Popup()
{
}

/*** core ***/
void Popup::Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active)
{
	UI_Object::Set("", mesh, scaleX, scaleY, posX, posY, zHeight, active);

	/* Button */
	quitButton = new UI_Object;
	quitButton->Set(word, Geometry::meshList[Geometry::GEO_CUBE_RED], scaleY * 0.05f, scaleY * 0.05f, posX + scaleX * 0.47f, posY + scaleY * 0.46f , zHeight + 0.01f, active);
}


bool Popup::CollisionDetection(UI_Object* checkMe, bool clicked)
{
	if( !clicked )	//if not clicked
		return false;

	bool b = quitButton->CollisionDetection(checkMe, clicked);

	if( b )
		active = !active;

	return b;
}

void Popup::Update(double dt)
{
	
}

void Popup::Draw()
{
	if( getActive() )
	{
		View::RenderMeshIn2D(mesh, false, scale.x, scale.y, position.x, position.y, position.z, 0);

		/* Button */
		Vector3 pos11 = quitButton->getPosition();
		Vector3 scale11 = quitButton->getScale();
		View::RenderMeshIn2D(quitButton->getMesh(), false, scale11.x, scale11.y, pos11.x, pos11.y, pos11.z, 0);
	}
}

/* Getter/setter */
UI_Object* Popup::getButton()
{
	return quitButton;
}


/** Selection menu **/
Vector3 Selection_Menu::s;

/*** constructor / destructor ***/
Selection_Menu::Selection_Menu()
{
	currentItem = totalItem = itemScale = 0;
	currentPos.SetZero();
}

Selection_Menu::~Selection_Menu()
{
}

/*** core ***/
void Selection_Menu::Set(float sc, float itemScale, float posX, float posY, float zHeight, bool active)
{
	UI_Object::Set("", mesh, sc, sc, posX, posY, zHeight, active);
	this->itemScale = itemScale;
}

void Selection_Menu::Init()
{
	/** Fit items into perfect square grid **/
	itemPos.resize( totalItem );

	float sq = static_cast<float>(itemPos.size());
	sq = sqrt( sq );
	int len = static_cast<int>(sq);	//to test 0

	if( sq - len >= 0.f )	//if is not zero
		sq = ++len;

	itemScale *= (1.f / sq);

	float scaleVal = scale.x * ( 1.f / sq );	//scale val per
	float posX = (position.x - scale.x * 0.5f) + (scaleVal * 0.5f);
	float posY = (position.y + scale.y * 0.5f) - (scaleVal * 0.5f);
	float posZ = position.z + 0.05f;
	int counter = 0;

	for(int i = 0; i < itemPos.size(); ++i, ++counter)
	{
		itemPos[i].Set( posX, posY, posZ);
		posX += scaleVal;

		if( counter >= len )
		{
			counter = 0;
			posX = (position.x - scale.x * 0.5f) + (scaleVal * 0.5f);
			posY -= scaleVal;
		}
	}
}

void Selection_Menu::AddItem(Mesh* mesh)
{
	itemList.push_back(mesh);
	++totalItem;
}

bool Selection_Menu::CollisionDetection(UI_Object* checkMe, bool clicked)
{
	/* Start and end */
	checkStart = checkMe->getPosition() - checkMe->getScale() * 0.5f;
	checkEnd = checkMe->getPosition() + checkMe->getScale() * 0.5f;
	s.Set(itemScale, itemScale, 1);

	for(int i = 0; i < totalItem; ++i)
	{
		start = itemPos[i] - s * 0.5f;
		end = itemPos[i] + s * 0.5f;

		if( Collision::QuickAABBDetection2D(start, end, checkStart, checkEnd) )
		{
			if( clicked )
				currentItem = i;
			return true;
		}
	}

	return false;
}

void Selection_Menu::Draw()
{
	/** selection menu **/
	if( getActive() )
	{
		/** Popup mesh */


		/* Quit button */

		Vector3 pos11;
		for(int i = 0; i < totalItem; ++i)
		{
			/* So that tile sets final scale will match given scale */
			//float t_scale = model->tileSelectionMenu->getItemScale();
			pos11 = getItemPos(i);
			View::RenderMeshIn2D(getItemMesh(i), false, itemScale, itemScale, pos11.x, pos11.y, pos11.z, 0);

			/* Selected */
			if( currentItem == i )	//selected this block
			{
				View::RenderMeshIn2D(Geometry::meshList[Geometry::GEO_SELECTOR], false, itemScale * 1.1f, itemScale * 1.1f, pos11.x, pos11.y, pos11.z, 0);
			}
		}
	}
}

Vector3 Selection_Menu::getItemPos(int index)
{
	if( index < 0 || index >= totalItem )
		return Vector3(0, 0, 0);
	return itemPos[index];
}

Mesh* Selection_Menu::getItemMesh(int index)
{
	if( index < 0 || index >= totalItem )
		return NULL;
	return itemList[index];
}

int Selection_Menu::getTotalItem()
{
	return totalItem;
}

float Selection_Menu::getItemScale()
{
	return itemScale;
}

void Selection_Menu::Update(double dt)
{
}

int Selection_Menu::getCurrentItem()
{
	return currentItem;
}

/** Textbox **/
float TextBox::max_wordWidth = 0.9f;

/*** constructor / destructor ***/
TextBox::TextBox()
{
	typed = false;
	word = returnText = "";
}

TextBox::~TextBox()
{
}

/*** core ***/
void TextBox::Set(Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active)
{
	UI_Object::Set("", mesh, scaleX, scaleY, posX, posY, zHeight, active);
}


bool TextBox::CollisionDetection(UI_Object* checkMe, bool clicked)
{

	bool b = UI_Object::CollisionDetection(checkMe, clicked);

	if( b && clicked)
	{
		activated = !activated;
	}

	/* click anywhere else will deactivate textbox */
	if( clicked && activated && !b )
	{
		activated = false;
	}

	/* Backspace clears all */

	return b;
}

void TextBox::Update(double dt)
{
	if( !activated )
		return;

	/* Type */
	char a = Controller::characterPressed();

	if( a != '/' )
	{
		word += a;
		typed = true;
	}

	/* Backspace */
	/*else if( Controller::IsKeyPressed(VK_BACK) )
	{
		if(word.length() > 0)
			word.pop_back();
	}*/
}

void TextBox::Draw()
{
	/* Type */
	if( getActive() )
	{
		/* Box */
		View::RenderMeshIn2D(mesh, false, scale.x, scale.y, position.x, position.y, position.z, 0);


		/* Text */
		View::RenderTextOnScreenStart0(Geometry::meshList[Geometry::GEO_AR_CHRISTY], 
			getWord(), Color(1, 0, 1), getWordScale(), getStartPosX(), position.y, position.z);
	}
}

string TextBox::getWord()
{
	if( typed )
	{
		returnText = word;
		int stopAt = 0;
		float len = 0.f;

		float sc = wordScale * scale.y;

		/* Total text length */
		for(int i = word.length() - 1; i >= 0; --i)
		{
			len += View::FontData[word[i]] * sc;
			++stopAt;

			/* Exceed length */
			if( len > scale.x * max_wordWidth )
			{
				--stopAt;
				returnText = word.substr(word.length() - stopAt);	//get from stopAt till end
			}
		}
		typed = false;
		return returnText;
	}
	return 
		returnText;
}

float TextBox::getStartPosX()
{
	return position.x - ( (scale.x * max_wordWidth) * 0.5f);
}