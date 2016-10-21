#include "project.h"

// MUI Objects
Object *app, *win1;

int main(int argc,char *argv[])
{
	APTR	GROUP_ROOT_0, GR_grp_0;
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	GR_grp_0 = GroupObject,
		MUIA_HelpNode, "GR_grp_0",
		MUIA_Group_Horiz, TRUE,
		Child, SimpleButton("button title 5"),
		Child, HSpace(50),
		Child, SimpleButton("button title 4"),
	End;

	GROUP_ROOT_0 = GroupObject,
		Child, SimpleButton("button title 3"),
		Child, HVSpace,
		Child, SimpleButton("button title 2"),
		Child, SimpleButton("button title 1"),
		Child, GR_grp_0,
	End;
	
	MUIA_Application_Window, win1 = WindowObject,
			MUIA_Window_Title, "My Window Title",
			MUIA_Window_ID   , MAKE_ID('E','M','R','T'),
			MUIA_Window_AppWindow, TRUE,
			MUIA_Window_SizeGadget, TRUE,
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

	DoMethod(win1, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
	  app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
	
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
