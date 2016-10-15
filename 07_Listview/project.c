#include "project.h"
#include "support.h"

#define PRESSADD	11
#define	PRESSREMOVE	12

// MUI Objects
Object *app, *win1, *closeButton, *bAddButton, *bRemoveButton, *lv;

char *listviewItems[] = {"Amiga 500", "Amiga 1200", "C64", NULL}; 
int i;		

int main(int argc,char *argv[])
{
	APTR	GROUP_ROOT_0 ;
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}
	
	lv = ListviewObject,
	MUIA_Listview_Input, TRUE,
	MUIA_Listview_List , ListObject,
		InputListFrame,
		MUIA_List_ConstructHook, MUIV_List_ConstructHook_String,
		MUIA_List_DestructHook , MUIV_List_DestructHook_String,
		End,
	End;
	
	GROUP_ROOT_0 = GroupObject,
		Child, LLabel1("ListviewObject"),
		Child, lv,
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, bAddButton= MakeButton("Add Item"),
		Child, bRemoveButton= MakeButton("Remove Item"),
		
		Child, closeButton= MakeButton("Close"),
	End;
	
	MUIA_Application_Window, win1 = WindowObject,
			MUIA_Window_Title, "My Window Title",
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

        DoMethod(win1, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
          app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
		  
        DoMethod(closeButton, MUIM_Notify, MUIA_Pressed, FALSE,
          app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);// closeButton
		  
		DoMethod(bAddButton,MUIM_Notify,MUIA_Pressed,FALSE,
			app,2,MUIM_Application_ReturnID,PRESSADD);//
		DoMethod(bRemoveButton,MUIM_Notify,MUIA_Pressed,FALSE,
			app,2,MUIM_Application_ReturnID,PRESSREMOVE);//	
		
		for (i=0; listviewItems[i] != NULL; i++)
		{
			DoMethod (lv, MUIM_List_InsertSingle, listviewItems[i], MUIV_List_Insert_Bottom);
		}
		
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
				
				case PRESSADD:
					DoMethod (lv, MUIM_List_InsertSingle, "Amiga 4000", MUIV_List_Insert_Bottom);
					break;
					
				case PRESSREMOVE:
					if (getlistindex(lv)>=0)
						DoMethod (lv, MUIM_List_Remove, getlistindex(lv));
					break;
		}
		if(running && signals) Wait(signals);
	}

	set(win1,MUIA_Window_Open,FALSE);

    if(app) MUI_DisposeObject(app);
	Close_Libs();
	exit(TRUE);
}
