#include "project.h"

// MUI Objects
Object *app, *win1;

int main(int argc,char *argv[])
{
	APTR	GROUP_ROOT_0, REC_label_1, REC_label_0, REC_label_2;
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	REC_label_1 = RectangleObject,
		MUIA_Rectangle_HBar, TRUE,
		MUIA_FixHeight, 8,
	End;

	REC_label_0 = RectangleObject,
		MUIA_FixWidth, 180,
		MUIA_FixHeight, 80,
	End;

	REC_label_2 = RectangleObject,
		MUIA_Rectangle_VBar, TRUE,
		MUIA_FixHeight, 8,
	End;

	GROUP_ROOT_0 = GroupObject,
		Child, REC_label_1,
		Child, REC_label_0,
		Child, REC_label_2,
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
