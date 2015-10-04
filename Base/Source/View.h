#ifndef VIEW_H
#define VIEW_H
/* Model */
#include "Model_Gameplay.h"
#include "Model_Level_Editor.h"
#include "Model_MainMenu.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

/*************************************************************/
/*
	Contains:
		Model pointer to point to current model to render

	Function:
		Render and object if active.
		Custom render specific stuff dictated by the model
*/
/*************************************************************/
class View
{
private:
/********************** openGL *********************************/
	static GLFWwindow* m_window_view;

/********************** Window screen size *****************************/
	//dimension on computer screen
	static unsigned short m_screen_width;
	static unsigned short m_screen_height;

/********************** model and view ptr **********************/
	Model* model;
public:
/********************** Light *****************************/
	const static unsigned short m_total_lights = 2;

/********************* Uniform parameters ***********************/
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,

		/* material */
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		/* light */
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		/* texture */
		U_COLOR_TEXTURE_ENABLED,	//multitexture: texture enabled
		U_COLOR_TEXTURE_ENABLED_1,
		U_COLOR_TEXTURE,			//multitexture:	color enabled
		U_COLOR_TEXTURE_1,

		/* TEXT */
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		/* FOG */
		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,

		U_TOTAL,
	};

	enum MODE
	{
		TWO_D,
		THREE_D,
	};

	enum FONT_DATA
	{
		TOTAL_FONT_TYPE,
	};

/********************** constructor/destructor *****************************/
	View();
	View(Model* model, unsigned short console_width, unsigned short console_height, MODE mode);
	~View();

/********************** Core functions *****************************/
	virtual void Init() = 0;
	void InitLight();
	void InitFontData();
	virtual void InitProjection();
	virtual void Render(const float fps) = 0;
	virtual void Exit();

/**************** render utilities ****************/
	/* Light */
	void RenderLight();

	/* 3D */
	static void RenderMesh(Mesh *mesh, bool enableLight);
	static void RenderMeshInLines(Mesh* mesh, const Vector3& position, const Vector3& scale);

	/* External loading of matrix */
	static void RenderMesh(Mtx44& TRS, Mesh* mesh, bool light);	//includes push and pop and render

	/* 2D */
	static void RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizex=1.0f, float sizey = 1.0f, float x=0.0f, float y=0.0f, float z = 0.f, float angle = 0.f);
	static void Render2DTile(Mesh *mesh, bool enableLight, float size, float x, float y, float z, int tileType);
	static void RenderMeshIn2D(Mesh *mesh, bool enableLight, Mtx44& TRS);
	
	/* Text */
	//3D
	static void RenderText(Mesh* mesh, std::string text, Color color);

	//2D
	//render text with cutoff: add slash to part where supposed to go to next line
	static void RenderTextOnScreenCutOff(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z = 1.f);
	static void RenderTextOnScreenStart0(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z = 1.f);
	static void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z = 1.f);

	/* General */
	void RenderObject(Object* o);
	void RenderUI(UI_Object* u);

/********************** Getter/setter *****************************/
	static unsigned short getScreenHeight();
	static unsigned short getScreenWidth();
	Model* getModel();
	void SetModel(Model* model);
	static GLFWwindow* getWindow_view();

/********************** openGL *********************************/
	static GLFWwindow* getWindow();

/********************** text **********************/
	static float FontData[256];
protected:
/**************** set up initstuff, call this FIRST at Init(); ****************/
	void StartInit();

/**************** set up projection, Call this FIRST at Render(); ****************/
	void StartRendering(const float fps);

/************* mode *****************/
	MODE mode;

/************* matrix *****************/
	static MS modelStack;
	static MS viewStack;
	static MS projectionStack;

/************* lights *****************/
	static Light lights[m_total_lights];	//for model, use the lights provided in view

/********************** openGL *********************************/
	static unsigned m_vertexArrayID;
	static unsigned m_programID;
	static unsigned m_parameters[U_TOTAL];
	static float fps;
	
/********************** Flags **********************/
	static bool InitAlready;
};

#endif