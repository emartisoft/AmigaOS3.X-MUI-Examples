#include <string.h>
#include <libraries/gadtools.h>
#include <libraries/mui.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/muimaster.h>
#include <proto/intuition.h>

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

IPTR getcycleindex(Object *obj)
{
	IPTR index = 0;
	get(obj, MUIA_Cycle_Active, &index);
	return (index);
}

IPTR getlistindex(Object *obj)
{
	IPTR index = 0;
	get(obj, MUIA_List_Active, &index);
	return (index);
}

IPTR getradioindex(Object *obj)
{
	IPTR index = 0;
	get(obj, MUIA_Radio_Active, &index);
	return (index);
}

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
