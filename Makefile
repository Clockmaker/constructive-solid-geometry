# MAKEFILE
#
# just for windows :(
#
NAME = csg
VPATH = src
PATH_DEP = deps

# lazy way $(wildcard src/*.c)
FILE=\
	r_main\
	glad\
	main

OBJ= $(FILE:=.o)
HDR= 
DEP= $(FILE:=.d)

# FLAGS
F_DEBUG= -Werror -ffast-math -O3
F_OGL= -lopengl32 -lglu32
F_GLFW= -lglfw3
# auto-dependency
F_DEP= -MT $@ -MMD -MP -MF $(PATH_DEP)/$*.d
$(PATH_DEP)/%.d: ;
.PRECIOUS: $(PATH_DEP)/%.d
-include $(PATH_DEP)/$(DEP)

# compiler & linker
CFLAGS= $(F_DEP)
LDFLAGS= $(F_OS) $(F_OGL) $(F_GLFW)

RM=rm -f

# OS
ifeq ($(OS), Windows_NT)
	# directory separator
	/=$(strip \)
	#include win64.d
	F_WIN= -mwindows
	F_DEBUG+= -mconsole
	F_OS = $(F_WIN)
	EXE=$(NAME).exe
	CC=gcc
	#CLC=cls
	RM=del /Q
else
	/=/
	
	# add -ldl to flags
	#include linux.d
	#include macos.d
endif

# objects
%.o: %.c
%.o : %.c $(PATH_DEP)/%.d
	$(CC) $(CFLAGS) -o $@ -c $<

# compile
$(EXE) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#
.PHONY:all clean debug run try force
.DEFAULT:all
.SUFFIXES:
.SECONDARY:

#
all:clean $(EXE)
	@echo $(OS)

debug:CFLAGS  += -include $(VPATH)/debug.h
debug:LDFLAGS += $(F_DEBUG) 
debug:run

run:$(EXE)
	$(EXE)

clean:
	-$(RM) $(EXE) *.o $(PATH_DEP)$/*.d

# utilities and alias
try:debug
	