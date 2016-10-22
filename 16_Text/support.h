#include <string.h>
#include <libraries/gadtools.h>
#include <libraries/mui.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/muimaster.h>

/**************************************************************************
 Some MUI support functions
**************************************************************************/
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

BOOL getbool(Object *obj)
{
	return((BOOL)xget(obj,MUIA_Selected));
}
/*
Object *MUI_NewObject          (char *classname,Tag tag1,...)
{
	return MUI_NewObjectA(classname, (struct TagItem*)&tag1);
}

BOOL MUI_AslRequestTags(APTR requester, Tag Tag1, ...)
{
	return MUI_AslRequest(requester, (struct TagItem*)&Tag1);
}

Object *MUI_MakeObject         (LONG type,...)
{
	return MUI_MakeObjectA(type, ((ULONG*)&type)+1);
}

LONG    MUI_Request            (APTR app,APTR win,LONGBITS flags,char *title,char *gadgets,char *format,...)
{
	return MUI_RequestA(app,win,flags,title,gadgets,format,((ULONG*)&format)+1);
}


Object *MakeLabel(STRPTR str)  { return(MUI_MakeObject(MUIO_Label,str,0)); }
Object *MakeLabel1(STRPTR str)  { return(MUI_MakeObject(MUIO_Label,str,MUIO_Label_SingleFrame)); }
Object *MakeLabel2(STRPTR str)  { return(MUI_MakeObject(MUIO_Label,str,MUIO_Label_DoubleFrame)); }
Object *MakeLLabel(STRPTR str)  { return(MUI_MakeObject(MUIO_Label,str,MUIO_Label_LeftAligned)); }
Object *MakeLLabel1(STRPTR str)  { return(MUI_MakeObject(MUIO_Label,str,MUIO_Label_LeftAligned|MUIO_Label_SingleFrame)); }
*/
Object *MakeCheck(BOOL check)
{
	Object *obj = MUI_MakeObject(MUIO_Checkmark,NULL);
	if (obj) set(obj,MUIA_CycleChain,1);
	return(obj);
}

Object *MakeButton(STRPTR str)
{
	Object *obj = MUI_MakeObject(MUIO_Button,str);
	if (obj) set(obj,MUIA_CycleChain,1);
	return(obj);
}

Object *MakeCycle(STRPTR *array)
{
	Object *obj = MUI_MakeObject(MUIO_Cycle, NULL, array);
	if (obj) set(obj,MUIA_CycleChain,1);
	return(obj);
}

Object *MakeString(STRPTR def, LONG maxlen)
{
	Object *obj = MUI_MakeObject(MUIO_String,NULL,maxlen);

	if (obj)
	{
		SetAttrs(obj,
			MUIA_CycleChain,1,
			MUIA_String_Contents,(int)def,
			TAG_DONE);
	}

	return(obj);
}

/*Object *MakeInteger(LONG num)
{
	Object *obj = MUI_MakeObject(MUIO_String,NULL,10);

	if (obj)
	{
		SetAttrs(obj,
			MUIA_CycleChain,1,
  		MUIA_String_Accept, "0123456789",
  		MUIA_String_Integer,0,//num,
			TAG_DONE);
	}

	return(obj);
}*/

Object *MakeImageButton(ULONG image)
{
	return ImageObject,ImageButtonFrame,
								MUIA_Image_Spec,image,
								MUIA_Background, MUII_ButtonBack,
								MUIA_InputMode, MUIV_InputMode_RelVerify,
								MUIA_Image_FreeVert, TRUE,
								MUIA_CycleChain,1,
								End;

}

Object *MakeLV(APTR pool)
{
	return(
		ListviewObject,
			MUIA_Listview_Input, TRUE,
			MUIA_Listview_List , ListObject,
				InputListFrame,
				MUIA_List_ConstructHook, MUIV_List_ConstructHook_String,
				MUIA_List_DestructHook , MUIV_List_DestructHook_String,
				pool?MUIA_List_Pool:TAG_IGNORE,pool,
				End,
			End
	);
}
