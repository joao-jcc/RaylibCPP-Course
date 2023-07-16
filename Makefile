# Set compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude/thirdy_party
LDFLAGS := -Linclude/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

# Define source files and object files for hello_world
hello_world_sources := $(wildcard hello_world/src/*.cpp)
hello_world_objects := $(patsubst hello_world/src/%.cpp, hello_world/build/%.o, $(hello_world_sources))
hello_world_executable := executables/hello_world

# Default target, compiles and links all executables
all: hello_world

hello_world: create_build_dir $(hello_world_objects)
	$(CXX) $(hello_world_objects) -o $(hello_world_executable) $(LDFLAGS)


# Create build directory if it doesn't exist
create_build_dir:
	mkdir -p hello_world/build

# Compile hello_world source files
hello_world/build/%.o: hello_world/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf hello_world/build/*.o $(hello_world_executable)