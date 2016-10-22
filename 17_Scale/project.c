#include "project.h"

int main(int argc,char *argv[])
{
	Object *app,*win1;
	ULONG signals;
	BOOL running = TRUE;
	
	APTR	GROUP_ROOT_0, Scale_0, TX_label_0, STR_TX_label_0, GA_label_0;
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	STR_TX_label_0 = "\n\33c\33bDownloading...\33n\n\n http://www.google.com/files/google-all.lha";

	TX_label_0 = TextObject,
		MUIA_Background, MUII_FILL,
		MUIA_Frame, MUIV_Frame_Text,
		MUIA_Text_Contents, STR_TX_label_0,
		MUIA_Text_SetMin, TRUE,
	End;

	Scale_0 = ScaleObject,
		MUIA_FramePhantomHoriz, TRUE,
		MUIA_Scale_Horiz, TRUE,
	End;

	GA_label_0 = GaugeObject,
		GaugeFrame,
		MUIA_HelpNode, "GA_label_0",
		MUIA_FixHeight, 10,
		MUIA_Gauge_Horiz, TRUE,
		MUIA_Gauge_InfoText, "%1d%",
		MUIA_Gauge_Current, 48,
		MUIA_Gauge_Max, 100,
	End;

	GROUP_ROOT_0 = GroupObject,
		Child, TX_label_0,
		Child, Scale_0,
		Child, GA_label_0,
	End;

	win1 = WindowObject,
		MUIA_Window_Title, "window_title",
		MUIA_Window_ID, MAKE_ID('0', 'W', 'I', 'N'),
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
