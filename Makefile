# Compiler and flags
CXX := g++
CXXFLAGS := -Iinclude -Wall -O2

# Directories
SRCDIR := src
INCDIR := include
BUILDDIR := build

# Files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TARGET := $(BUILDDIR)/MLP.exe

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files to .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILDDIR):
	mkdir $(BUILDDIR)

# Clean build artifacts
clean:
	del /Q $(BUILDDIR)\*.o 2>nul
	del /Q $(TARGET) 2>nul

.PHONY: all clean
