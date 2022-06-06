CC = g++
CFLAGS = -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Final executable
EXE = Edge_of_the_Abyss
# Put all auto generated files to this build dir.
BUILD_DIR = ./build

# List of all .cpp source files.
SRCS = $(wildcard src/*.cpp) $(wildcard src/States/*.cpp) $(wildcard src/Util/*.cpp) \
$(wildcard src/ResourceManager/*.cpp) $(wildcard src/Levels/*.cpp) $(wildcard src/Players/*.cpp) 

# All .o files go to build dir.
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEPS = $(OBJS:%.o=%.d)

.PHONY : clean all run run_debug documentation debug release

# Default target
all : release

release : CFLAGS +=-O3
release : $(EXE)

debug : CFLAGS += -g -Wall -Werror -pedantic -pedantic-errors -fsanitize=address
debug : LFLAGS += -fsanitize=address
debug : $(EXE)

# Depends on all .o files.
# Create build directories - same structure as sources and link all the object files.
$(EXE) : $(OBJS)
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
run : release
	./$(EXE)

run_debug : debug
	./$(EXE)

# Creates and opens the doxygen documentation
documentation :
	doxygen ./documentation/Doxyfile
	xdg-open ./documentation/html/index.html

# This should remove all generated files.
clean :
	-rm -rf $(BUILD_DIR) *.d *.o ./scores.txt ./$(EXE)