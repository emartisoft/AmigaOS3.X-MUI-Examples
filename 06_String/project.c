#include "project.h"
#include "support2.h"

#define PRESS	11

// MUI Objects
Object *app, *win1, *closeButton, *bButton, *stringObj0, *stringObj1;
Object *stringObj2, *stringObj3, *stringObj4, *stringObj4, *stringObj5;

ShowContent(void)
{
	MUI_RequestA(app,win1,0,"Selected Items","*OK",getstr(stringObj0),NULL);
}

int main(int argc,char *argv[])
{
	APTR	GROUP_ROOT_0, obj_aux0, obj_aux1, obj_aux2, obj_aux3, obj_aux4, obj_aux5;
	APTR	obj_aux6, obj_aux7, obj_aux8, obj_aux9;

	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	stringObj0 = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_label_0",
		MUIA_String_Contents, "String Content",
	End;

	stringObj1 = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_label_1",
		MUIA_String_Contents, "String Content",
	End;

	obj_aux1 = Label2("string title");

	obj_aux0 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux1,
		Child, stringObj1,
	End;

	stringObj2 = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_label_2",
		MUIA_String_Contents, "String Content",
		MUIA_String_Format, MUIV_String_Format_Center,
	End;

	obj_aux3 = Label2("string title");

	obj_aux2 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux3,
		Child, stringObj2,
	End;

	stringObj3 = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_label_3",
		MUIA_String_Contents, "1000",
		MUIA_String_Accept, "-0123456789",
		MUIA_String_Format, MUIV_String_Format_Right,
	End;

	obj_aux5 = Label2("Sale");

	obj_aux4 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux5,
		Child, stringObj3,
	End;

	stringObj4 = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_label_4",
		MUIA_String_Contents, "123456",
		MUIA_String_Secret, TRUE,
	End;

	obj_aux7 = Label2("Password");

	obj_aux6 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux7,
		Child, stringObj4,
	End;

	stringObj5 = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "STR_label_5",
		MUIA_String_Contents, "A",
		MUIA_String_Accept, "ABCDE",
		MUIA_String_Reject, "0123456789",
	End;

	obj_aux9 = Label2("Accept string ABCDE");

	obj_aux8 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux9,
		Child, stringObj5,
	End;

	GROUP_ROOT_0 = GroupObject,
		Child, stringObj0,
		Child, obj_aux0,
		Child, obj_aux2,
		Child, obj_aux4,
		Child, obj_aux6,
		Child, obj_aux8,
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, bButton= MakeButton("Show first string object content"),
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
			app,2,MUIM_Application_ReturnID,PRESS);//

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
					ShowContent();
					break;
		}
		if(running && signals) Wait(signals);
	}

	set(win1,MUIA_Window_Open,FALSE);

    if(app) MUI_DisposeObject(app);
	Close_Libs();
	exit(TRUE);
}
