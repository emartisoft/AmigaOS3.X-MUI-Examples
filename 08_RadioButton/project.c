#include "project.h"
#include "support2.h"

#define PRESS	11

// MUI Objects
Object *app, *win1, *closeButton, *bButton, *radioButton;
char cMessage[100];
STRPTR	radioItems[6];

BOOL ShowSelectedItems(void)
{	
	stpcpy(cMessage, "Selected Item is ");
	strcat(cMessage, radioItems[getradioindex(radioButton)]);
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
	
	radioItems[0] = "C/C++";
	radioItems[1] = "Pascal";
	radioItems[2] = "C#";
	radioItems[3] = "AMOS Basic";
	radioItems[4] = "Assembler";
	radioItems[5] = NULL;

	radioButton = RadioObject,
		MUIA_Frame, MUIV_Frame_Group,
		MUIA_FrameTitle, "RadioButton Title",
		MUIA_HelpNode, "radioButton",
		MUIA_Radio_Entries, radioItems,
	End;
	
	GROUP_ROOT_0 = GroupObject,	
		Child, LLabel("Select Programming Language:"),
		Child, radioButton,
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, bButton= MakeButton("Show selected items"),
		Child, closeButton= MakeButton("Close"),
	End;
	
	MUIA_Application_Window, win1 = WindowObject,
			MUIA_Window_Title, "My Window Title",
			MUIA_Window_ID   , MAKE_ID('E','M','R','T'),
			MUIA_Window_Width, 480,
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
			app,2,MUIM_Application_ReturnID,PRESS);// button

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
