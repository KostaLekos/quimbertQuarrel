NAME = QuimbertQuarrel

CC = g++
CCFLAGS = -Ithird/raylib/src --std=c++20 -g

LINKFLAGS = 

ifeq ($(OS),Windows_NT)
LINKFLAGS += -lgdi32 -lwinmm
else
LINKFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
endif

LINKFLAGS += third/raylib/src/libraylib.a

BUILDDIR := build
SRCDIR := src

SOURCEFILES := $(shell ls $(SRCDIR)/*.cpp)
OBJECTFILES := $(shell echo $(SOURCEFILES) | sed 's/\.cpp/\.o/g' | sed 's/src/$(BUILDDIR)\/objects/g')

.PHONY: third clean all

all: $(OBJECTFILES)
	mkdir -p $(BUILDDIR)
	make third
	$(CC) $^ -o $(BUILDDIR)/$(NAME) $(LINKFLAGS)

clean:
	rm -rf $(BUILDDIR)
	(cd third/raylib/src && make clean)

third:
	(cd third/raylib/src && make PLATFORM=PLATFORM_DESKTOP DUSE_WAYLAND=ON RAYLIB_TYPE=STATIC -j 4)


$(OBJECTFILES): $(SOURCEFILES)
	@printf "Compiling $@\n"
	mkdir -p $(shell dirname "$@")
	test $@ -nt $(shell echo "$@" | sed 's/\.o/\.cpp/g' | sed 's/build\/objects/src/g') || g++ -c $(shell echo "$@" | sed 's/\.o/\.cpp/g' | sed 's/build\/objects/src/g') -o $@ $(CCFLAGS)
	@printf "Compiled $@\n\n"
