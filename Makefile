########################################################
# Makefile for Advent of Code 
# Author: Sean Malloy
########################################################

########################################################
# Variable definitions
########################################################
# C++ compiler
# CXX = g++
CXX := clang++

# Directories
INCDIRS = include
SRCDIR = src
SOLDIR = solutions
OBJDIR = obj

vpath %.cpp $(SRCDIR)/
vpath %.cpp $(SOLDIR)/

# Object files
OBJS = advent.o option_parser.o timer.o utils.o d01.o d02.o d03.o d04.o d05.o d06.o d07.o d08.o d09.o d10.o d11.o d12.o d13.o d14.o d15.o d16.o d17.o d18.o d19.o d20.o d21.o d22.o d23.o d24.o d25.o

# C++ compiler flags
# Use the first for debugging, the second for release
# CXXFLAGS := -g -Wall -std=c++20 -I include/
CXXFLAGS := -O3 -Wall -std=c++20 -I include/

# Linker. For C++ should be $(CXX).
LINK := $(CXX)

# Executable name. 
EXEC := advent

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

$(EXEC): $(addprefix $(OBJDIR)/, $(OBJS))
	$(LINK) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#############################################################

.PHONY: clean
clean:
	$(RM) $(EXEC) a.out core
	$(RM) $(OBJDIR)/*.o *.d *~

#############################################################
