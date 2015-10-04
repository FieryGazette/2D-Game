#ifndef UI_OBJECT_H
#define UI_OBJECT_H
#include "Entity.h"
#include "MeshList.h"

/********************************************************/
/*
	Create general UI stuff.
*/
/********************************************************/
class UI_Object : public Entity
{
protected:
	string word;
	static float wordScale;	//percentage in regards to button scale
public:
	/*** constructor / destructor ***/
	UI_Object();
	~UI_Object();

	/*** core ***/
	void Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active);

	virtual void Update(double dt);
	virtual void Draw();
	virtual bool CollisionDetection(UI_Object* checkMe, bool clicked);
	void Init();

	/* Getter setter */
	void SetPosition(Vector3& pos);
	Vector3 getPosition();

	void SetScale(Vector3 scale);
	Vector3 getScale();

	bool getActive();
	void SetActive(bool active);

	virtual string getWord();

	float getWordScale();

	Mesh* getMesh();

protected:
	static Vector3 start, end, checkStart, checkEnd;
};

/********************************************************/
/*
	Button. Click on it will 'depress' it for a certain amount of time before
	popping back up.
*/
/********************************************************/
class Button : public UI_Object
{
public:
	/*** constructor / destructor ***/
	Button();
	~Button();

	/*** core ***/
	void Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active, float depression);
	virtual void Update(double dt);
	virtual void Draw();
	virtual bool CollisionDetection(UI_Object* checkMe, bool clicked);

	/*** Getter/setter ***/
	bool getClicked();
private:
	static double depressionTime;
	float depression;
	bool clicked;
	double depressionTimer;
};


/********************************************************/
/*
	Button. Click on it will 'depress' it for a certain amount of time before
	popping back up.
*/
/********************************************************/
class Popup : public UI_Object
{
	UI_Object* quitButton;
public:
	/*** constructor / destructor ***/
	Popup();
	~Popup();

	/*** core ***/
	void Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active);

	virtual void Update(double dt);
	virtual void Draw();
	virtual bool CollisionDetection(UI_Object* checkMe, bool clicked);

	/* Getter/setter */
	UI_Object* getButton();
};

/********************************************************/
/*
	Selection menu. Items are displayed in square. So if you pushed in 16 meshes,
	display will put them in 4 rows. Clicking on an item will select it. Hovering over it
	will show a full-sized preview.
	Passed in items should be part of an array.

	Can only be square shape.
*/
/********************************************************/
class Selection_Menu : public UI_Object
{
	vector<Mesh*> itemList;
	vector<Vector3> itemPos;

	int currentItem;	//index of current item
	Vector3 currentPos;
	float itemScale;
	int totalItem;
	static Vector3 s;	//for collision detection check
public:
	/*** constructor / destructor ***/
	Selection_Menu();
	~Selection_Menu();

	/*** core ***/
	void Set(float sc, float itemScale, float posX, float posY, float zHeight, bool active);
	void AddItem(Mesh* mesh);
	void Init();

	virtual void Update(double dt);
	virtual void Draw();
	virtual bool CollisionDetection(UI_Object* checkMe, bool clicked);

	/*** Getter/setter ***/
	int getCurrentItem();
	Vector3 getItemPos(int index);
	Mesh* getItemMesh(int index);
	int getTotalItem();
	float getItemScale();
};

/********************************************************/
/*
	Textbox, type your message here.
	Entering/confirming your text means that that text is registered with this textbox.
	If text too long, will shift to right.
*/
/********************************************************/
class TextBox : public UI_Object
{
	string returnText;
	bool activated;
	bool typed;	//a letter has benn typed inside
	static float max_wordWidth;	//max word width percentage
public:
	/*** constructor / destructor ***/
	TextBox();
	~TextBox();

	/*** core ***/
	void Set(Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active);

	virtual void Update(double dt);
	virtual void Draw();
	virtual bool CollisionDetection(UI_Object* checkMe, bool clicked);

	/** Getter/setter **/
	virtual string getWord();
	float getStartPosX();	//get start pos for word X
};

#endif