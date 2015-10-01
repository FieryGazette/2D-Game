#include "Controller_3D_Game.h"
#include "View_3D_Game.h"
#include "Model_Gameplay.h"

int main( void )
{
	/* Memory leak checker */
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );	//call this if program does not exit at same place everytime

	/* Pass in View into Controller and set mode (2D/3D) */
	Controller_3D_Game myController;

	/* Init, Run and Exit */
	myController.Init();
	myController.Run();
	myController.Exit();
}
