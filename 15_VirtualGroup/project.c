#include "project.h"

#define		BUTTONADD		0x00ff

// MUI Objects
Object *App;
Object *winForm;
Object *StrName;
Object *StrPhoneNumber;
Object *rGender;
Object *bAdd;
Object *bClose;
STRPTR	rGenderContent[3];

char cMessage[100];

enum 
{
	MENU_PROJECT=1,
	MENU_ABOUT,
	MENU_EXIT,
};

static struct NewMenu MenuStr[]=
{
    {NM_TITLE, "Virtual Group Example",        0 , 0, 0,  (APTR)MENU_PROJECT},
    {NM_ITEM,  "About",  		              "A", 0, 0,  (APTR)MENU_ABOUT  },
    {NM_ITEM,  NM_BARLABEL,                    0 , 0, 0,  (APTR)0           },
    {NM_ITEM,  "Exit",                        "E", 0, 0,  (APTR)MENU_EXIT   },
    {NM_END,   NULL,                           0 , 0, 0,  (APTR)0           },
};

IPTR getradioindex(Object *obj)
{
	IPTR index = 0;
	get(obj, MUIA_Radio_Active, &index);
	return (index);
}

LONG xget(Object *obj,ULONG attribute)
{
	LONG x;
	get(obj,attribute,&x);
	return(x);
}

char *getstr(Object *obj)
{
	return((char *)xget(obj,MUIA_String_Contents));
}

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
	APTR	grpRoot, grpVirtual, lHead, lInfo, obj_aux0, obj_aux1, obj_aux2, obj_aux3;
	APTR	hBar;
	
	ULONG signals;
	BOOL running = TRUE;	
	
	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	rGenderContent[0] = "Female";
	rGenderContent[1] = "Male";
	rGenderContent[2] = NULL;

	lHead = CLabel("New Personal Record");

	lInfo = CLabel("   Please, fill in the blanks to add new personal record.   ");

	StrName = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "StrName",
		MUIA_String_MaxLen, 50,
	End;

	obj_aux1 = Label2("        Name :");

	obj_aux0 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux1,
		Child, StrName,
	End;

	StrPhoneNumber = StringObject,
		MUIA_Frame, MUIV_Frame_String,
		MUIA_HelpNode, "StrPhoneNumber",
		MUIA_String_Accept, "0123456789",
	End;

	obj_aux3 = Label2("Phone Number :");

	obj_aux2 = GroupObject,
		MUIA_Group_Columns, 2,
		Child, obj_aux3,
		Child, StrPhoneNumber,
	End;

	rGender = RadioObject,
		MUIA_Frame, MUIV_Frame_Group,
		MUIA_FrameTitle, "Gender",
		MUIA_HelpNode, "rGender",
		MUIA_Radio_Entries, rGenderContent,
	End;

	grpVirtual = VirtgroupObject,
		VirtualFrame,
		MUIA_HelpNode, "grpVirtual",
		Child, lHead,
		Child, lInfo,
		Child, obj_aux0,
		Child, obj_aux2,
		Child, rGender,
	End;

	grpVirtual = ScrollgroupObject,
		MUIA_Scrollgroup_Contents, grpVirtual,
	End;

	hBar = RectangleObject,
		MUIA_Rectangle_HBar, TRUE,
		MUIA_FixHeight, 8,
	End;

	bAdd = SimpleButton("Add & show new record");

	bClose = SimpleButton("Close");

	grpRoot = GroupObject,
		Child, grpVirtual,
		Child, hBar,
		Child, bAdd,
		Child, bClose,
	End;

	winForm = WindowObject,
		MUIA_Window_Title, "Form",
		MUIA_Window_ID, MAKE_ID('E', 'W', 'I', 'N'),
		MUIA_Window_AppWindow, TRUE,
		WindowContents, grpRoot,
	End;
	
	App = ApplicationObject,
		MUIA_Application_Title      , "Virtual Group Example",
		MUIA_Application_Version    , "$VER: Virtual Group Example 1.0",
		MUIA_Application_Copyright  , "(c) 2016",
		MUIA_Application_Author     , "emarti",
		MUIA_Application_Description, "MUI Virtual Group Example", 
		MUIA_Application_Base       , "Amiga",
		MUIA_Application_Menustrip  , MUI_MakeObject(MUIO_MenustripNM,MenuStr,0),
		SubWindow, winForm,
		
		
	End;

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
