# 
# Target OS: Amiga OS3.X
# Compiler : GCC
#
	
objects = project.o
appname = Project
#option = -O3 -m68030
option = -O3 -m68030 -noixemul

project:	$(objects)
	gcc -o $(appname) $(objects) $(option)
	
project.o:	project.c project.h support3.h
	gcc -c project.c $(option)
	
clean:
	rm $(objects) $(appname)
	