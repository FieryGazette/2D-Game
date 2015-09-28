#ifndef UI_OBJECT_H
#define UI_OBJECT_H
#include "Object.h"

class UI_Object
{
public:
	/*** constructor / destructor ***/
	UI_Object();
	~UI_Object();

	/*** core ***/
	void Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY, float zHeight, bool active);
	void Init();

	bool CollisionDetection(UI_Object* checkMe);

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

private:
	bool active;
	string word;
	Vector3 position, scale;
	Mesh* mesh;

	static Vector3 start, end, checkStart, checkEnd;
};

#endif