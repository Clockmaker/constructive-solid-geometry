# MAKEFILE
#
# just for windows :(
#
NAME = csg
VPATH = src
PATH_DEP = deps

ifeq ($(OS),Windows_NT)
	# directory separator
	/=$(strip \)
	#include win64.d
	F_WIN= -mwindows 
	F_OS = $(F_WIN)
	EXE=$(NAME).exe
	CC=gcc
	RM=del /Q
else
	/=/
	RM=rm -f
	#include linux.d
	#include macos.d
endif

# lazy way $(wildcard src/*.c)
FILE=\
	r_main\
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


# objects
%.o: %.c
%.o : %.c $(PATH_DEP)/%.d
	$(CC) $(CFLAGS) -o $@ -c $<

# compile
$(EXE) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#
.PHONY:all clean debug run try
.DEFAULT:all
.SUFFIXES:
.SECONDARY:

#
all:clean $(EXE)
	@echo $(OS)

debug:CFLAGS+= $(F_DEBUG) -mconsole
debug:run

run:$(EXE)
	$(EXE)

clean:
	-$(RM) $(EXE) *.o $(PATH_DEP)$/*.d

# shorter alias just for convenience
try:debug
	