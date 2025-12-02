TARGET = pulser

INCDIR = inc
SRCDIR = src
OBJDIR = obj
BINDIR = bin


#CC       = g++ -D_ISLINUX 
CC       = g++ 


#detect the OS (linux or OSX, dont care about windows)
UNAME := $(shell uname)



# compiling flags  

#all the warnings (for final compiling)
#CFLAGS   = -I$(INCDIR) -Wall 

#for just making this damn thing run 
CFLAGS   = -I$(INCDIR) -w -fcompare-debug-second    


LINKER   = g++

# linking flags 

#Linux
ifeq ($(UNAME), Linux)

	#LFLAGS   = -std=c++17  

	#SHOW ME ALL THE WARNINGS 
	#LFLAGS = -Wall -lglut -lGL -lGLU 

	#NO WARNINGS 
	LFLAGS = -g -w -lglut -lGL -lGLU 

endif

# #OSX
# ifeq ($(UNAME), Darwin)
# 	LFLAGS   = -Wall -lm -lz -framework Glut -framework OpenGL
# endif



SOURCES  := $(wildcard $(SRCDIR)/*.cpp)

OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f


$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"


.PHONY: cleanimg
cleanimg:
	@$(rm) *.bmp
	@echo "image cleanup done"


.PHONY: clean
clean:
	@$(rm) $(TARGET)
	@$(rm) $(OBJECTS)
	@echo "cleanup done"


.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) $(OBJDIR)/*.o
	@echo "Executable removed!"
	 




## OBJ = main.o
## INC = -I "inc"
## confusion36d:$(OBJ)
## 	# -std=c++11 added for OSX to handle vectors properly  
## 	g++ -std=c++17 -o confusion36d main.cpp cnc_globals.cpp cnc_io.cpp cnc_plot.cpp math_op.cpp point_op.cpp 
## 	# -g is for debugging flags with GDB 
## 	#g++ -g -o confusion36d main.cpp Matrices.cpp model.cpp framebuffer.cpp render.cpp
## 	rm -f $(OBJ)
## clean:
## 	rm -f $(OBJ) confusion36d
## 	rm -f *.o 
## 	rm -f *.bmp	
## copy:
## 	#cp ./point_ops.obj ../3d_obj/point_ops.obj
## 	cp ./*.obj ../3d_obj


