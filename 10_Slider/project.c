#include "project.h"
#include "support3.h"

// MUI Objects
Object *app, *win1, *closeButton, *slider, *infolabel, *bButton;

#define	PRESS	10
char str[100];

ShowContent(void)
{
	IPTR slideValue = 0;
	get(slider, MUIA_Slider_Level, &slideValue);
	
	sprintf(str, "Slider Value is %d", slideValue);
	
	MUI_RequestA(app,win1,0,"Slider Info","*OK",str,NULL);
	
	//set(slider, MUIA_Slider_Level, 50);
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
	
	slider = SliderObject,
		MUIA_HelpNode, "slider",
		MUIA_Frame, MUIV_Frame_Slider,
		MUIA_Slider_Min, 0,
		MUIA_Slider_Max, 100,
		MUIA_Slider_Level, 25,
	End;

	GROUP_ROOT_0 = GroupObject,	
		Child, slider,
		Child, infolabel=CLabel("Scroll slider to min. or max. value"),
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, bButton= MakeButton("Show slider value"),
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
	
		DoMethod(slider,
		MUIM_Notify, MUIA_Slider_Level, 0,
		infolabel,
		3,
		MUIM_Set, MUIA_Text_Contents, "Slider Value: Min."
		);
		
		DoMethod(slider,
		MUIM_Notify, MUIA_Slider_Level, 100,
		infolabel,
		3,
		MUIM_Set, MUIA_Text_Contents, "Slider Value: Max."
		);
		
		DoMethod(slider,
		MUIM_Notify, MUIA_Slider_Level, 1,
		infolabel,
		3,
		MUIM_Set, MUIA_Text_Contents, ""
		);
		
		DoMethod(slider,
		MUIM_Notify, MUIA_Slider_Level, 99,
		infolabel,
		3,
		MUIM_Set, MUIA_Text_Contents, ""
		);
		
		DoMethod(bButton,MUIM_Notify,MUIA_Pressed,FALSE,
			app,2,MUIM_Application_ReturnID,PRESS);

        DoMethod(win1, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
          app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
		  
        DoMethod(closeButton, MUIM_Notify, MUIA_Pressed, FALSE,
          app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);// closeButton

		DoMethod(win1,
		MUIM_Window_SetCycleChain, infolabel,
		0
		);
		
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
