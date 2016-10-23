#include "project.h"

// MUI Objects
Object *app, *win1, *bTop, *bBottom;

int main(int argc,char *argv[])
{
	APTR	GROUP_ROOT_0;
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}
	
	GROUP_ROOT_0 = GroupObject,	
		Child, CLabel2("Notify MUI Example (Button enable/disable)"),
		Child, bTop= SimpleButton("Click to me"),
		Child, bBottom= SimpleButton("Click to me"),
	End;
	
	MUIA_Application_Window, win1 = WindowObject,
			MUIA_Window_Title, "Notify Example",
			MUIA_Window_ID   , MAKE_ID('E','M','R','T'),
			MUIA_Window_Width, 320,
			WindowContents, GROUP_ROOT_0,
	End;
	
	app = ApplicationObject,
		MUIA_Application_Title      , "Project",
		MUIA_Application_Version    , "$VER: Project X.X (XX.XX.XX)",
		MUIA_Application_Copyright  , " ",
		MUIA_Application_Author     , " ",
		MUIA_Application_Description, " ", 
		MUIA_Application_Base       , " ",
		SubWindow, win1,
		
	End;

	if (!app)
	{
		printf("Cannot create application.\n");
		return(0);
	}
		/* Notifies */
		
		// Closing Application
        DoMethod(win1, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
          app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
		
		// Button enable/disable notifies
		DoMethod(bTop,
			MUIM_Notify, MUIA_Pressed, FALSE,
			bTop,
			3,
			MUIM_Set, MUIA_Disabled, TRUE
			);

		DoMethod(bTop,
			MUIM_Notify, MUIA_Pressed, FALSE,
			bBottom,
			3,
			MUIM_Set, MUIA_Disabled, FALSE
			);

		DoMethod(bBottom,
			MUIM_Notify, MUIA_Pressed, FALSE,
			bTop,
			3,
			MUIM_Set, MUIA_Disabled, FALSE
			);

		DoMethod(bBottom,
			MUIM_Notify, MUIA_Pressed, FALSE,
			bBottom,
			3,
			MUIM_Set, MUIA_Disabled, TRUE
			);		
			
		// Set cycle chain
		DoMethod(win1,
			MUIM_Window_SetCycleChain, bTop,
			bBottom,
			0
			);
		  
		/* End of Notifies */  
		set(bBottom, MUIA_Disabled, TRUE);// bBottom is disable on startup
    	set(win1,MUIA_Window_Open,TRUE);// open window
    
	while(running)
	{
		ULONG id = DoMethod(app,MUIM_Application_Input,&signals);

		switch(id)
		{
				case MUIV_Application_ReturnID_Quit:
					if((MUI_RequestA(app, win1, 0, "Quit?", "_Yes|_No", "\33cAre you sure?", 0)) == 1)
							running = FALSE;
					break;	
		}
		if(running && signals) Wait(signals);
	}

	set(win1,MUIA_Window_Open,FALSE);

    if(app) MUI_DisposeObject(app);
	Close_Libs();
	exit(TRUE);
}
