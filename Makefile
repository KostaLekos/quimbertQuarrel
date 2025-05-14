NAME = QuimbertQuarrel

CC = g++
CCFLAGS = -Ithird/raylib/src --std=c++20 -g -Wpedantic -Wall -Wextra -Wold-style-cast

LINKFLAGS = third/raylib/src/libraylib.a
BINNAME = 

ifeq ($(OS),Windows_NT)
BINNAME = $(NAME).exe
LINKFLAGS += -lgdi32 -lwinmm
else
LINKFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
BINNAME = $(NAME)
endif

BUILDDIR := build
SRCDIR := src

SOURCEFILES := $(shell ls $(SRCDIR)/*.cpp)
OBJECTFILES := $(shell echo $(SOURCEFILES) | sed 's/\.cpp/\.o/g' | sed 's/src/$(BUILDDIR)\/objects/g')

.PHONY: third clean all dist

all: $(OBJECTFILES)
	mkdir -p $(BUILDDIR)
	make third
	$(CC) $^ -o $(BUILDDIR)/$(BINNAME) $(LINKFLAGS)

clean:
	rm -r $(BUILDDIR) || true
	(cd third/raylib/src && make clean)

third:
	(cd third/raylib/src && make PLATFORM=PLATFORM_DESKTOP DUSE_WAYLAND=ON RAYLIB_TYPE=STATIC -j 4)


$(OBJECTFILES): $(SOURCEFILES)
	@printf "Compiling $@\n"
	mkdir -p $(shell dirname "$@")
	test $@ -nt $(shell echo "$@" | sed 's/\.o/\.cpp/g' | sed 's/build\/objects/src/g') || g++ -c $(shell echo "$@" | sed 's/\.o/\.cpp/g' | sed 's/build\/objects/src/g') -o $@ $(CCFLAGS)
	@printf "Compiled $@\n\n"
