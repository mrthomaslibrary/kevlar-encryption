CXX = clang
CXXFLAGS = -Wall -std=c++17
TARGET = kevlar
TEST-TARGET = gorun
ROOT_INSTALL_PATH = /usr/local/bin
INSTALL_PATH = ~/bin

SRCS = $(wildcard src/*.c)

test-compile:
	$(CXX) $(SRCS) -o $(TEST-TARGET) -lm

all: compile install

compile:
	$(CXX) $(SRCS) -o $(TARGET) -lm

install: compile
	-sudo rm $(INSTALL_PATH)/$(TARGET)
	-sudo rm $(ROOT_INSTALL_PATH)/$(TARGET)
	sudo cp $(TARGET) $(INSTALL_PATH)/
	sudo cp $(TARGET) $(ROOT_INSTALL_PATH)/
	sudo chmod +x $(INSTALL_PATH)/$(TARGET)
	@echo "Build complete and installed to $(INSTALL_PATH)"

clean:
	rm -f $(TARGET)
