#include "project.h"
#include "support2.h"

#define PRESS	11

// MUI Objects
Object *app, *win1, *closeButton, *bButton, *cyc1, *cyc2;
char cMessage[100];
STRPTR	CycleItems[6];

static const char *ColorList[] =
	{
	   "Black",
	   "White",
	   "Yellow",
	   NULL
	};

BOOL ShowSelectedItems(void)
{	
	IPTR selectedCyc1ItemIndex = 0;
	IPTR selectedCyc2ItemIndex = getcycleindex(cyc2);
	
	get(cyc1, MUIA_Cycle_Active, &selectedCyc1ItemIndex);
	//get(cyc2, MUIA_Cycle_Active, &selectedCyc2ItemIndex);
	
	stpcpy(cMessage, "");
	strcat(cMessage, "Selected Color is ");
	strcat(cMessage, ColorList[selectedCyc1ItemIndex]);
	strcat(cMessage, ".\n");
	strcat(cMessage, "Selected Programming Language is ");
	strcat(cMessage, CycleItems[selectedCyc2ItemIndex]);
	strcat(cMessage, ".\n");
	
	return (MUI_RequestA(app,win1,0,"Selected Items","*OK",cMessage,NULL));
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
	
	CycleItems[0] = "C/C++";
	CycleItems[1] = "Pascal";
	CycleItems[2] = "C#";
	CycleItems[3] = "AMOS Basic";
	CycleItems[4] = "Assembler";
	CycleItems[5] = NULL;

	cyc1 = CycleObject,
		MUIA_HelpNode, "cyc1",
		MUIA_Frame, MUIV_Frame_Button,
		MUIA_Cycle_Entries, ColorList,
	End;
	
	GROUP_ROOT_0 = GroupObject,	
		Child, LLabel("Select Color:"),
		Child, cyc1,
		Child, LLabel("Select Programming Language:"),
		Child, cyc2= MakeCycle(CycleItems),
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, bButton= MakeButton("Show selected items"),
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
		  
		DoMethod(bButton,MUIM_Notify,MUIA_Pressed,FALSE,
			app,2,MUIM_Application_ReturnID,PRESS);// CheckInfo button

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
				
				case PRESS:
					ShowSelectedItems();
					break;
		}
		if(running && signals) Wait(signals);
	}

	set(win1,MUIA_Window_Open,FALSE);

    if(app) MUI_DisposeObject(app);
	Close_Libs();
	exit(TRUE);
}
