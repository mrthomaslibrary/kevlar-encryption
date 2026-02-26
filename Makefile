CXX = clang
CXXFLAGS = -Wall -std=c++17
TARGET = kevlar
INSTALL_PATH = /usr/local/bin

SRCS = $(wildcard src/*.c)

all: compile install

compile:
	$(CXX) $(SRCS) -o $(TARGET) -lm

install: compile
	-sudo rm $(INSTALL_PATH)/$(TARGET)
	sudo cp $(TARGET) $(INSTALL_PATH)/
	sudo chmod +x $(INSTALL_PATH)/$(TARGET)
	@echo "Build complete and installed to $(INSTALL_PATH)"

clean:
	rm -f $(TARGET)
