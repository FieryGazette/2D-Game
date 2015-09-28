#ifndef UI_OBJECT_H
#define UI_OBJECT_H
#include "Object.h"

/**/
/*
	Create general UI stuff.
*/
/**/
class UI_Object
{
public:
	/*** constructor / destructor ***/
	UI_Object();
	~UI_Object();

	/*** core ***/
	void Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active);
	void Init();

	virtual bool CollisionDetection(UI_Object* checkMe);

	/* particle */
	void Update(const double& dt, Vector3& playerPos);

	/* Getter setter */
	void SetPosition(Vector3& pos);
	Vector3 getPosition();

	void SetScale(Vector3 scale);
	Vector3 getScale();

	void SetWord(string word);
	string getWord();

	bool getActive();
	void SetActive(bool active);

	Mesh* getMesh();

protected:
	bool active;
	string word;
	Vector3 position, scale;
	Mesh* mesh;

	static Vector3 start, end, checkStart, checkEnd;
};

/**/
/*
	Button. Click on it will 'depress' it for a certain amount of time before
	popping back up.
*/
/**/
class Button : public UI_Object
{
public:
	/*** constructor / destructor ***/
	Button();
	~Button();

	/*** core ***/
	virtual bool CollisionDetection(UI_Object* checkMe);
	void UpdateButton(double dt);

private:
	static double depressionTime;
	static Vector3 depressionPercentage;
	bool clicked;
	double depressionTimer;
};

#endif