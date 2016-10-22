#include "project.h"

// MUI Objects
Object *app, *win1;

int main(int argc,char *argv[])
{
	APTR	MNlabel0File, MNlabel0New, MNlabel0Open, MNlabel0Save, MNlabel0BarLabel0;
	APTR	MNlabel0Exit, MNlabel0Settings, MNlabel0AM, MNlabel0A12, MNlabel0A45;
	APTR	MNlabel0A76, MNlabel0M98, MNlabel0NZ, GROUP_ROOT_0, REC_label_0, menu;
	
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

REC_label_0 = RectangleObject,
		MUIA_FixHeight, 8,
	End;

	GROUP_ROOT_0 = GroupObject,
		Child, REC_label_0,
	End;

	win1 = WindowObject,
		MUIA_Window_Title, "window_title",
		MUIA_Window_ID, MAKE_ID('E', 'M', 'R', 'T'),
		WindowContents, GROUP_ROOT_0,
	End;

	MNlabel0New = MenuitemObject,
		MUIA_Menuitem_Title, "New",
		MUIA_Menuitem_Shortcut, "N",
	End;

	MNlabel0Open = MenuitemObject,
		MUIA_Menuitem_Title, "Open",
	End;

	MNlabel0Save = MenuitemObject,
		MUIA_Menuitem_Title, "Save",
	End;

	MNlabel0BarLabel0 = MUI_MakeObject(MUIO_Menuitem, NM_BARLABEL, 0, 0, 0);

	MNlabel0Exit = MenuitemObject,
		MUIA_Menuitem_Title, "Exit",
	End;

	MNlabel0File = MenuitemObject,
		MUIA_Menuitem_Title, "File",
		MUIA_Family_Child, MNlabel0New,
		MUIA_Family_Child, MNlabel0Open,
		MUIA_Family_Child, MNlabel0Save,
		MUIA_Family_Child, MNlabel0BarLabel0,
		MUIA_Family_Child, MNlabel0Exit,
	End;

	MNlabel0A12 = MenuitemObject,
		MUIA_Menuitem_Title, "A12",
		MUIA_Menuitem_Checkit, TRUE,
	End;

	MNlabel0A45 = MenuitemObject,
		MUIA_Menuitem_Title, "A45",
	End;

	MNlabel0A76 = MenuitemObject,
		MUIA_Menuitem_Title, "A76",
		MUIA_Menuitem_Toggle, TRUE,
	End;

	MNlabel0M98 = MenuitemObject,
		MUIA_Menuitem_Title, "M98",
		MUIA_Menuitem_Shortcut, "M",
	End;

	MNlabel0AM = MenuitemObject,
		MUIA_Menuitem_Title, "A-M",
		MUIA_Family_Child, MNlabel0A12,
		MUIA_Family_Child, MNlabel0A45,
		MUIA_Family_Child, MNlabel0A76,
		MUIA_Family_Child, MNlabel0M98,
	End;

	MNlabel0NZ = MenuitemObject,
		MUIA_Menuitem_Title, "N-Z",
	End;

	MNlabel0Settings = MenuitemObject,
		MUIA_Menuitem_Title, "Settings",
		MUIA_Family_Child, MNlabel0AM,
		MUIA_Family_Child, MNlabel0NZ,
	End;

	menu = MenustripObject,
		MUIA_Family_Child, MNlabel0File,
		MUIA_Family_Child, MNlabel0Settings,
	End;
	
	app = ApplicationObject,
		MUIA_Application_Title      , "Project",
		MUIA_Application_Version    , "$VER: Project X.X (XX.XX.XX)",
		MUIA_Application_Copyright  , " ",
		MUIA_Application_Author     , " ",
		MUIA_Application_Description, " ", 
		MUIA_Application_Base       , " ",
		MUIA_Application_Author, "NONE",
		MUIA_Application_Menustrip, menu,
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
