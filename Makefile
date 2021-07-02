#SFMLDIR = /usr/include/SFML
#INCLUDEDIR = $(SFMLDIR)
#LIBDIR = $(SFMLDIR)
CC = g++
CFLAGS = -g -std=c++17 -Wall -Werror -pedantic -pedantic-errors -fsanitize=address #-I $(INCLUDEDIR)
LFLAGS = -fsanitize=address -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Final executable
EXE = Edge_of_abyss
# Put all auto generated files to this build dir.
BUILD_DIR = ./build

# List of all .cpp source files.
SRCS = $(wildcard src/*.cpp) $(wildcard src/States/*.cpp) $(wildcard src/Util/*.cpp) \
$(wildcard src/ResourceManager/*.cpp) $(wildcard src/Levels/*.cpp) 

# All .o files go to build dir.
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEPS = $(OBJS:%.o=%.d)

.PHONY : clean all run documentation

# Default target
all : $(EXE)

$(EXE) : $(BUILD_DIR)/$(EXE)

# Actual target of the executable - depends on all .o files.
# Create build directories - same structure as sources and link all the object files.
$(BUILD_DIR)/$(EXE) : $(OBJS)
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(LFLAGS)

# Include all .d files
-include $(DEPS)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEPS)`.
# The -MMD flags additionaly creates a .d file with
# the same name as the .o file.
$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ -MMD -c $< $(CFLAGS)

# Runs the executable after building it.
run : all
	$(BUILD_DIR)/$(EXE)

# Creates and opens the doxygen documentation
documentation :
	doxygen ./documentation/Doxyfile
	xdg-open ./documentation/html/index.html

# This should remove all generated files.
clean :
	-rm $(BUILD_DIR)/$(EXE) $(OBJS) $(DEPS)