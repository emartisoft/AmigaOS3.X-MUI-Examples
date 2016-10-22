
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

APTR	grpRoot, grpVirtual, lHead, lInfo, obj_aux0, obj_aux1, obj_aux2, obj_aux3;
APTR	hBar;

enum 
{
	MENU_PROJECT=1,
	MENU_ABOUT,
	MENU_EXIT,
};

static struct NewMenu MenuStr[]=
{
    {NM_TITLE, "Virtual Group Example 2",      0 , 0, 0,  (APTR)MENU_PROJECT},
    {NM_ITEM,  "About",  		              "A", 0, 0,  (APTR)MENU_ABOUT  },
    {NM_ITEM,  NM_BARLABEL,                    0 , 0, 0,  (APTR)0           },
    {NM_ITEM,  "Exit",                        "E", 0, 0,  (APTR)MENU_EXIT   },
    {NM_END,   NULL,                           0 , 0, 0,  (APTR)0           },
};

init(void)
{
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
		MUIA_Application_Title      , "Virtual Group Example 2",
		MUIA_Application_Version    , "$VER: Virtual Group Example 1.0",
		MUIA_Application_Copyright  , "(c) 2016",
		MUIA_Application_Author     , "emarti",
		MUIA_Application_Description, "MUI Virtual Group Example", 
		MUIA_Application_Base       , "Amiga",
		MUIA_Application_Menustrip  , MUI_MakeObject(MUIO_MenustripNM,MenuStr,0),
		SubWindow, winForm,
		
		
	End;
}

