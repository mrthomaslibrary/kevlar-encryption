CXX = clang
CXXFLAGS = -Wall -std=c++17
TARGET = kevlar
INSTALL_DIR = $(HOME)/bin
WRAPPER = kevlar

SRCS = $(wildcard src/*.c)

all: compile install

compile:
	$(CXX) $(SRCS) -o $(TARGET) -lm

install:
	mkdir -p $(INSTALL_DIR)
	sudo cp $(TARGET) $(INSTALL_DIR)/
	sudo cp $(WRAPPER) $(INSTALL_DIR)/
	sudo chmod +x $(INSTALL_DIR)/$(WRAPPER)
	@echo "Build complete and installed to $(INSTALL_DIR)"

clean:
	rm -f $(TARGET)
