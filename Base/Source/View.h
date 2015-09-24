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

/**
 Everything in view class will be using Objects class for TRS and other info
 **/
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
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderLight();
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size=1.0f, float x=0.0f, float y=0.0f, float z = 0.f, float angle = 0.f);
	void RenderMeshInLines(Mesh* mesh, const Vector3& position, const Vector3& scale);
	void Render2DMesh(Mesh *mesh, bool enableLight, float sizeX, float sizeY, float x, float y);
	void Render2DTile(Mesh *mesh, bool enableLight, float size, float x, float y, int tileType);

/********************** Getter/setter *****************************/
	unsigned short getScreenHeight();
	unsigned short getScreenWidth();
	Model* getModel();
	void SetModel(Model* model);

/********************** openGL *********************************/
	static GLFWwindow* getWindow();

protected:
/**************** set up initstuff, call this FIRST at Init(); ****************/
	void StartInit();

/**************** set up projection, Call this FIRST at Render(); ****************/
	void StartRendering(const float fps);

/************* mode *****************/
	MODE mode;

/************* matrix *****************/
	MS modelStack;
	MS viewStack;
	MS projectionStack;

/************* lights *****************/
	Light lights[m_total_lights];	//for model, use the lights provided in view

/********************** openGL *********************************/
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	float fps;

/********************** text **********************/
	static float FontData[256];
	
/********************** Flags **********************/
	static bool InitAlready;
};

#endif