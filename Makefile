# Set compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude/thirdy_party
LDFLAGS := -Linclude/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# Define source files and object files for hello_world
hello_world_sources := $(wildcard hello_world/src/*.cpp)
hello_world_objects := $(patsubst hello_world/src/%.cpp, hello_world/build/%.o, $(hello_world_sources))
hello_world_executable := executables/hello_world

# Define source files and object files for rectangles
rectangles_sources := $(wildcard rectangles/src/*.cpp)
rectangles_objects := $(patsubst rectangles/src/%.cpp, rectangles/build/%.o, $(rectangles_sources))
rectangles_executable := executables/rectangles

# Define source files and object files for triangles
triangles_sources := $(wildcard triangles/src/*.cpp)
triangles_objects := $(patsubst triangles/src/%.cpp, triangles/build/%.o, $(triangles_sources))
triangles_executable := executables/triangles

# Default target, compiles and links all executables
all: hello_world rectangles triangles

hello_world: create_build_dir $(hello_world_objects)
	$(CXX) $(hello_world_objects) -o $(hello_world_executable) $(LDFLAGS)

rectangles: create_build_dir $(rectangles_objects)
	$(CXX) $(rectangles_objects) -o $(rectangles_executable) $(LDFLAGS)

triangles: create_build_dir $(triangles_objects)
	$(CXX) $(triangles_objects) -o $(triangles_executable) $(LDFLAGS)

# Create build directory if it doesn't exist
create_build_dir:
	mkdir -p hello_world/build rectangles/build triangles/build

# Compile hello_world source files
hello_world/build/%.o: hello_world/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile rectangles source files
rectangles/build/%.o: rectangles/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile triangles source files
triangles/build/%.o: triangles/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf hello_world/build/*.o $(hello_world_executable) rectangles/build/*.o $(rectangles_executable)
	rm -rf triangles/build/*.o $(triangles_executable)