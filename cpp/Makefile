NAME = name

CC = g++
CCFLAGS = -Ithird/raylib/src -std=c++20

LINKFLAGS = -Lthird/raylib/src/libraylib.a -lraylib

ifeq ($(OS),Windows_NT)
LINKFLAGS += -lgdi32 -lwinmm
else
LINKFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
endif


BUILDDIR := build
SRCDIR := src

SOURCEFILES := $(shell ls $(SRCDIR)/*.cpp)
OBJECTFILES := $(shell echo $(SOURCEFILES) | sed 's/\.cpp/\.o/g' | sed 's/src/$(BUILDDIR)\/objects/g')

all: $(OBJECTFILES) third
	mkdir -p $(BUILDDIR)
	$(CC) $(LINKFLAGS) $^ -o $(BUILDDIR)/$(NAME)

clean:
	rm -rf $(BUILDDIR)
	(cd third/raylib/src && make clean)

third:
	(cd third/raylib/src && make PLATFORM=PLATFORM_DESKTOP DUSE_WAYLAND=ON RAYLIB_TYPE=STATIC)


$(OBJECTFILES): $(SOURCEFILES)
	@printf "Compiling $@\n"
	mkdir -p $(shell dirname "$@")
	test $@ -nt $(shell echo "$@" | sed 's/\.o/\.cpp/g' | sed 's/build\/objects/src/g') || g++ -c $(shell echo "$@" | sed 's/\.o/\.cpp/g' | sed 's/build\/objects/src/g') -o $@ $(FLAGS)
	@printf "Compiled $@\n\n"
