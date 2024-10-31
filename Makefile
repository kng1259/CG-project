# Makefile for GLUT Project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Include directories
INCLUDES = -Iinclude

# Libraries
LIBS = -lGL -lGLU -lglut

# Source files
SRCS = src/main.cpp src/Mesh.cpp src/supportClass.cpp

# Object directory
OBJDIR = obj

# Object files
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Executable
EXEC = main

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compile source files into object files
$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean