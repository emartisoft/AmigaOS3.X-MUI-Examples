#include "project.h"
#include "function.h"
#include "interface.h"

char cMessage[100];

ShowAddedRecord(void)
{
	stpcpy(cMessage, "        Name : ");
	strcat(cMessage, getstr(StrName));
	strcat(cMessage, "\nPhone Number : ");
	strcat(cMessage, getstr(StrPhoneNumber));
	strcat(cMessage, "\n      Gender : ");
	strcat(cMessage, rGenderContent[getradioindex(rGender)]);
	return (MUI_RequestA(App,winForm,0,"Added Record Info","*OK",cMessage,NULL));
}

BOOL AreYouSure(void)
{
	BOOL sure= TRUE;
	if (MUI_RequestA(App, winForm, 0, "Quit?", "_Yes|_No", "\33cAre you sure?", 0)==1)
		sure = FALSE;
	return sure;
}

int main(int argc,char *argv[])
{	
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	init();

	if (!App)
	{
		printf("Cannot create Application.\n");
		return(0);
	}
	
	DoMethod(winForm,
	MUIM_Window_SetCycleChain, StrName,
	StrPhoneNumber,
	rGender,
	bAdd,
	bClose,
	0
	);

	DoMethod(winForm, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
	  App, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
	  
	/* Close Button */
	DoMethod(bClose, MUIM_Notify, MUIA_Pressed, FALSE,
      App, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);
	
	/* Add & show new record Button */	
	DoMethod(bAdd,MUIM_Notify,MUIA_Pressed,FALSE,
			App,2,MUIM_Application_ReturnID,BUTTONADD);

	/* Open Window */
	set(winForm,MUIA_Window_Open,TRUE);
    
	while(running)
	{
		ULONG id = DoMethod(App,MUIM_Application_Input,&signals);

		switch(id)
		{
				case MUIV_Application_ReturnID_Quit:
					running = AreYouSure();
					break;

				case MENU_ABOUT:
					MUI_RequestA(App,winForm,0,"About","*OK","MUI Virtual Group Object Example on Amiga OS 3.X\n\nLink\nhttps://github.com/emartisoft/AmigaOS3.X-MUI-Examples",NULL);
					break;
					
				case MENU_EXIT:
					running = AreYouSure();
					break;
				
				case BUTTONADD:
					ShowAddedRecord();
					break;
				
		}
		if(running && signals) Wait(signals);
	}

	/* Close Window */
	set(winForm,MUIA_Window_Open,FALSE);

    if(App) MUI_DisposeObject(App);
	Close_Libs();
	exit(TRUE);
}
