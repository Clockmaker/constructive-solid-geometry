# MAKEFILE
#
# FIXME: just for windows :S
#
NAME = csg
VPATH = src
PATH_DEP = deps

FILE= $(basename $(notdir $(wildcard $(VPATH)/*.c)))


OBJ= $(FILE:=.o)
DEP= $(FILE:=.d)

# FLAGS
F_DEBUG= -Werror -ffast-math
F_RELEASE= -O3
F_OGL= -lopengl32 -lglu32
F_GLFW= -lglfw3
# auto-dependency
F_DEP= -MT $@ -MMD -MP -MF $(PATH_DEP)/$*.d
F_C99= -std=c99 -pedantic
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
.PHONY:all clean debug run try force release
.DEFAULT:all
.SUFFIXES:
.SECONDARY:

#
all:clean $(EXE)
	@echo $(OS)

debug:CFLAGS  += -DDEBUG=0
debug:LDFLAGS += $(F_DEBUG) 
debug:run

release:LDFLAGS += $(F_RELEASE)
	#@echo

run:$(EXE)
	@echo DEBUG $(OS)
	$(EXE)

clean:
	-$(RM) $(EXE) *.o $(PATH_DEP)$/*.d

# utilities and alias
try:debug
force: clean debug
	-$(RM) $(EXE) *.o
