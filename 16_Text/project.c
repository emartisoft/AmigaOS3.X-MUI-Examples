#include "project.h"
#include "support.h"
#include "rev.h"

int main(int argc,char *argv[])
{
	Object *app,*win1,*closeButton;
	APTR	GROUP_ROOT_0, TX_label_0;
	STRPTR STR_TX_label_0;
	ULONG signals;
	BOOL running = TRUE;
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}
	
	/*
	
	'\n'	 Start a new line. With this character you can e.g. create
		 multi line buttons.

	ESC -    Disable text engine, following chars will be printed
	         without further parsing.

	ESC u    Set the soft style to underline.

	ESC b    Set the soft style to bold.

	ESC i    Set the soft style to italic.

	ESC n    Set the soft style back to normal.

	ESC   Use pen number n (2..9) as front pen. n must be a valid
		 DrawInfo pen as specified in "intuition/screens.h".

	ESC c    Center current (and following) line(s).
		 This sequence is only valid at the beginning of a
		 string or after a newline character.

	ESC r    Right justify current (and following) line(s).
		 This sequence is only valid at the beginning of a
		 string or after a newline character.

	ESC l    Left justify current (and following) line(s).
		 This sequence is only valid at the beginning of a
		 string or after a newline character.

	ESC I[s] Draw MUI image with specification . See autodocs
	         of image class for image spec definition.

	Note:	 These rules apply to all MUI strings, not only to
		 a text objects contents. You can e.g. format the
	         columns of a listview or include images in a cycle
	         gadgets entries.
	*/
	
	STR_TX_label_0 = "\n\33c\33b" PROJECTNAME "\33n\n\n"
                        " " FULLVERSION_STRING "\n\n"
                        "\33bT\33next \33bM\33nUI \33bE\33nxample \33bP\33nroject\n\n"
                        "\33l\33i* FREEWARE *\33n\n\n"
                        COPYRIGHT "\n"
                        "emarti\n\n"
                        "Email: \33udtemarti@gmail.com\33n\n"
                        "Web: \33uhttp://emarti.sf.net/\33n\n";

	TX_label_0 = TextObject,
		MUIA_Background, MUII_FILL,
		MUIA_Frame, MUIV_Frame_Text,
		MUIA_Text_Contents, STR_TX_label_0,
		MUIA_Text_SetMin, TRUE,
	End;

	GROUP_ROOT_0 = GroupObject,
		Child, TX_label_0,
		Child, MUI_MakeObject(MUIO_HBar,10),
		Child, closeButton=MakeButton("Close"),
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
