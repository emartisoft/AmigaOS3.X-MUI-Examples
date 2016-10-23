#include "project.h"



int main(int argc,char *argv[])
{
	Object *app,*win1;
	ULONG signals;
	BOOL running = TRUE;
	STRPTR	tabPageNames[4];
	
	APTR	GROUP_ROOT_0, LA_label_2, GR_grp_3, LA_label_3, GR_grp_4, LA_label_4;
	APTR	REC_label_0, GR_grp_5, REC_label_0CC, LA_label_4CC;
	APTR	GR_grp_2;
	APTR	BT_label_2CCa;
	APTR	BT_label_2;
	APTR	BT_label_2CCb;
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}
	
	// RegisterObject Entries
	tabPageNames[0] = "Option 1";
	tabPageNames[1] = "Option 2";
	tabPageNames[2] = "Option 3";
	tabPageNames[3] = NULL;

	LA_label_2 = LLabel("Welcome to option tabbed form :)");

	LA_label_3 = TextObject,
		MUIA_Text_PreParse, "\033r",
		MUIA_Text_Contents, "Hi, I am option 1 & disable ",
		MUIA_InnerLeft, 0,
		MUIA_InnerRight, 0,
	End;

	BT_label_2CCa = SimpleButton("No operation");

	GR_grp_3 = VirtgroupObject,
		VirtualFrame,
		MUIA_HelpNode, "GR_grp_3",
		MUIA_Disabled, TRUE,
		Child, LA_label_3,
		Child, BT_label_2CCa,
	End;

	GR_grp_3 = ScrollgroupObject,
		MUIA_Scrollgroup_Contents, GR_grp_3,
	End;

	LA_label_4 = LLabel("Hi, I am option 2");

	BT_label_2 = SimpleButton("No operation");

	REC_label_0 = RectangleObject,
	End;

	GR_grp_4 = VirtgroupObject,
		VirtualFrame,
		MUIA_HelpNode, "GR_grp_4",
		Child, LA_label_4,
		Child, BT_label_2,
		Child, REC_label_0,
	End;

	GR_grp_4 = ScrollgroupObject,
		MUIA_Scrollgroup_Contents, GR_grp_4,
	End;

	REC_label_0CC = RectangleObject,
	End;

	LA_label_4CC = LLabel("Hi, I am option 3");

	BT_label_2CCb = SimpleButton("No operation");

	GR_grp_5 = VirtgroupObject,
		VirtualFrame,
		MUIA_HelpNode, "GR_grp_5",
		Child, REC_label_0CC,
		Child, LA_label_4CC,
		Child, BT_label_2CCb,
	End;

	GR_grp_5 = ScrollgroupObject,
		MUIA_Scrollgroup_Contents, GR_grp_5,
	End;

	/* RegisterObject [tabpages] */
	GR_grp_2 = RegisterObject,
		MUIA_Register_Titles, tabPageNames,
		MUIA_HelpNode, "GR_grp_2",
		Child, GR_grp_3,
		Child, GR_grp_4,
		Child, GR_grp_5,
	End;

	GROUP_ROOT_0 = GroupObject,
		MUIA_Group_SameWidth, TRUE,
		MUIA_Group_HorizSpacing, 20,
		Child, LA_label_2,
		Child, GR_grp_2,
	End;
	
	win1 = WindowObject,
		MUIA_Window_Title, "Option Pages",
		MUIA_Window_ID, MAKE_ID('E', 'M', 'R', 'T'),
		MUIA_Window_NoMenus, TRUE,
		WindowContents, GROUP_ROOT_0,
	End;

	app = ApplicationObject,
		MUIA_Application_Author, "NONE",
		MUIA_Application_Base, "NONE",
		MUIA_Application_Title, "NONE",
		MUIA_Application_Version, "$VER: NONE XX.XX (XX.XX.XX)",
		MUIA_Application_Copyright, "NOBODY",
		MUIA_Application_Description, "NONE",
		SubWindow, win1,
	End;


	if (!app)
	{
	printf("Cannot create application.\n");
	return(0);
	}
	
	DoMethod(win1,
		MUIM_Window_SetCycleChain, GR_grp_2,
		BT_label_2CCa,
		BT_label_2,
		BT_label_2CCb,
		0
		);

	DoMethod(win1, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
	  app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

	set(win1,MUIA_Window_Open,TRUE);// open window
    
	while(running)
	{
		ULONG id = DoMethod(app,MUIM_Application_Input,&signals);

		switch(id)
		{
				case MUIV_Application_ReturnID_Quit:
					if((MUI_RequestA(app,0,0,"Quit?","_Yes|_No","\33cAre you sure?",0)) == 1)
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
