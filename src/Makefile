IDIR =../include
CXX=g++
CXXFLAGS=-I$(IDIR) -g -Wall -Werror
CC=gcc
CFLAGS=-I$(IDIR) -g -Wall -Werror
ODIR=obj
LDIR=../lib

# FOR LINKING WITH PKG-CONFIG
#PACKAGES = glfw3 glew x11
#CPPFLAGS := $(shell pkg-config --cflags $(PACKAGES))
#LIBS := $(shell pkg-config --libs $(PACKAGES))

LIBS = -lglfw3 -lGLEW -lGL -lm -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lpthread -ldl -lGLU -lXcursor

_DEPS = triangle.h application.h camera.h header.h log.h manager.h shader.h singleton.h stb_image.h texture.h glad.h glfw3.h glfw3native.h gtc/matrix_transform.hpp gtc/type_ptr.hpp glm.hpp boost/static_assert.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o triangle.o application.o shader.o texture.o glad.o stb_image.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
