#include "Controller_3D_Game.h"
#include "View_3D_Game.h"
#include "Model_Gameplay.h"

int main( void )
{
	/* Memory leak checker */
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );	//call this if program does not exit at same place everytime


	/* Create Model */
	Model_Gameplay* myModel;
	myModel = new Model_Gameplay;
	
	/* Create View and pass in address of model you want, console dimemsions and Mode */
	View_3D_Game myView(myModel, 975, 650, View::TWO_D);

	/* Pass in View into Controller and set mode (2D/3D) */
	Controller_3D_Game myController;

	/* Init, Run and Exit */
	myController.Init(myModel, &myView);
	myController.Run();
	myController.Exit();

	delete myModel;
}
