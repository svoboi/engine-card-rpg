#CREDIT FOR THE BASE OF THIS MAKEFILE: David Bernhauer, Tomas Pecka, David Breiner,
#https://gitlab.fit.cvut.cz/bernhdav/pa2-minesweeper/-/blob/master/Makefile
#https://gitlab.fit.cvut.cz/breindan/bi-pa2-tutorials-b222/-/blob/main/cv11/solution/Makefile

TARGET=svoboi11
SOURCE_DIR=src
BUILD_DIR=build
DOC_DIR=doc

CXX=g++
LD=g++
#to use valgrind, -fsanitize=address needs to be deleted from both flags below
CXXFLAGS=-Wall -pedantic -fsanitize=address -g
LDFLAGS=-fsanitize=address
MKDIR=mkdir -p

HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)

OBJECTS = $(SOURCES:$(SOURCE_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean run compile


all: compile $(DOC_DIR)

compile: $(TARGET)

$(DOC_DIR): Doxyfile README.md $(HEADERS)
	doxygen Doxyfile

$(TARGET): $(OBJECTS)
	$(MKDIR) $(BUILD_DIR)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(BUILD_DIR)/ $(DOC_DIR)/

run: compile
	./${TARGET}
