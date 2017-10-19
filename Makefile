# makefile
# only for windows just for now
#include win64.d
#include linux.d
#include macos.d
NAME = csg
VPATH = src

# windows
EXE=$(NAME).exe
CC=gcc

RM=del

MDL= main
OBJ= $(MDL:=.o)
HDR= 

# FLAGS
F_DEBUG= -Werror -ffast-math -O3
F_OGL= -lopengl32 -lglu32
F_GLFW= -lglfw3
F_WIN= -mwindows
LDFLAGS= $(F_WIN) $(F_OGL)  $(F_GLFW)
DO=$(CC) -c $^

%.o: %.c
	$(CC) -o $@ -c $<

$(EXE) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.DEFAULT: run
.PHONY: debug release clean run
debug:LDFLAGS+= $(F_DEBUG)
debug:run
release:$(EXE)
run:$(EXE)
	$(EXE)
clean:
	$(RM) *.o
	$(RM) $(EXE)