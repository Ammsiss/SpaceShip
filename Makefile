BINARY = main
CODEDIRS = . ./src
INCDIRS = . ./inc

CXX = g++
OPT = -O0
DEPFLAGS = -MP -MD
LDLIBS = $(shell pkg-config --static --libs raylib)

CXXFLAGS = -fsanitize=address -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -pedantic-errors -g -std=c++20 $(shell pkg-config --cflags raylib) \
$(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

CXXFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.cpp))
OBJECTS = $(patsubst %.cpp, ./build/%.o, $(CXXFILES))
DEPFILES = $(patsubst %.cpp, ./build/%.d, $(CXXFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BINARY) $(LDLIBS)

cc:
	bear -- $(MAKE) clean all

./build/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BINARY) build compile_commands.json

-include $(DEPFILES)
