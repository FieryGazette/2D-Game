#ifndef UI_OBJECT_H
#define UI_OBJECT_H
#include "Object.h"

class UI_Object : public Object
{
public:
	/*** constructor / destructor ***/
	UI_Object();
	virtual ~UI_Object();

	/*** core ***/
	void Set(string word, Mesh* mesh, float scaleX, float scaleY, float posX, float posY);
	void AddParent(UI_Object* parent);
	void Init();

	/* particle */
	void Update(const double& dt, Vector3& playerPos);

private:
	string word;
};

#endif