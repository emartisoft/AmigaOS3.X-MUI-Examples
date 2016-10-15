#include "project.h"
#include "support3.h"

// MUI Objects
Object *app, *win1, *closeButton, *img;

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
	
	img = ImageObject,
		MUIA_Image_Spec, (long)"5:PROGDIR:ball.png",
		MUIA_Frame, MUIV_Frame_ImageButton,
		MUIA_FixWidth, 120,
		MUIA_FixHeight, 114,
		MUIA_Image_FreeVert, TRUE,
		MUIA_Image_FreeHoriz, TRUE,
	End;

	GROUP_ROOT_0 = GroupObject,	
		Child, img,
		Child, CLabel("     Amiga  Boing  Ball     "),
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, closeButton= MakeButton("Close"),
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
		  
        DoMethod(closeButton, MUIM_Notify, MUIA_Pressed, FALSE,
          app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);// closeButton

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
