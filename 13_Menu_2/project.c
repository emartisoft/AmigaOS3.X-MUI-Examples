#include "project.h"

// MUI Objects
Object *app, *win1;

enum 
{
	MENU_FILE=1,
	MENU_OPEN,
	MENU_EXIT,
};

static struct NewMenu MenuStr[]=
{
    {NM_TITLE, "File",                         0 , 0, 0,  (APTR)MENU_FILE    },
    {NM_ITEM,  "Open",  		              "?", 0, 0,  (APTR)MENU_OPEN    },
    {NM_ITEM,  NM_BARLABEL,                    0 , 0, 0,  (APTR)0           },
    {NM_ITEM,  "Exit",                        "E", 0, 0,  (APTR)MENU_EXIT    },
    {NM_END,   NULL,                           0 , 0, 0,  (APTR)0           },
};

BOOL AreYouSure(void)
{
	BOOL sure= TRUE;
	if (MUI_RequestA(app, win1, 0, "Quit?", "_Yes|_No", "\33cAre you sure?", 0)==1)
		sure = FALSE;
	return sure;
}

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
		Child, CLabel("This is example for MUI MenuStrip"),
		Child, CLabel("on Amiga OS 3.X"),
		Child, CLabel(""),
		Child, CLabel("Please, click to right button on the mouse"),
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
		MUIA_Application_Menustrip  , MUI_MakeObject(MUIO_MenustripNM,MenuStr,0),
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
					running = AreYouSure();
					break;

				case MENU_OPEN:
					MUI_RequestA(app,win1,0,"Open...","*OK","File is opened...",NULL);
					break;
					
				case MENU_EXIT:
					running = AreYouSure();
					break;
				
		}
		if(running && signals) Wait(signals);
	}

	set(win1,MUIA_Window_Open,FALSE);

    if(app) MUI_DisposeObject(app);
	Close_Libs();
	exit(TRUE);
}
