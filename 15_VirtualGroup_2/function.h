
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
