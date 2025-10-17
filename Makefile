# Makefile for Lab 1: Linear Lists

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Targets
TARGETS = lab1_arrays lab1_lists

all: $(TARGETS)

lab1_arrays: lab1_arrays.cpp
	$(CXX) $(CXXFLAGS) -o lab1_arrays lab1_arrays.cpp

lab1_lists: lab1_lists.cpp
	$(CXX) $(CXXFLAGS) -o lab1_lists lab1_lists.cpp

clean:
	rm -f $(TARGETS)

run_arrays: lab1_arrays
	./lab1_arrays

run_lists: lab1_lists
	./lab1_lists

run_all: all
	@echo "=== Running Array Implementation ==="
	./lab1_arrays
	@echo ""
	@echo "=== Running Linked List Implementation ==="
	./lab1_lists

.PHONY: all clean run_arrays run_lists run_all
