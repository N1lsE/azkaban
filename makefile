CLI_TARGET = azkaban-cli
TUI_TARGET = azkaban_tui
GUI_TARGET = azkaban

# Define variables
CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -pedantic -g
CFLAGS_COMMON = $(CFLAGS_DEBUG) -std=c17 -D_GNU_SOURCE
LIBS_COMMON = -lsqlcipher -lykpiv

# Linux configuration
CFLAGS_LINUX = $(CFLAGS_COMMON) -I/usr/include/ -I/usr/include/x86_64-linux-gnu
LIBS_LINUX = $(LIBS_COMMON) -lSDL2

# MacOS configuration
CFLAGS_MAC = $(CFLAGS_COMMON) $(shell sdl2-config --cflags) -I/opt/homebrew/Cellar/sqlcipher/4.6.1/include
LIBS_MAC = $(LIBS_COMMON) $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image

# Source files
SRCDIR = src
BUILDDIR = build
SRC = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*/*.c)
SRC = $(shell find $(SRCDIR) -type f -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Platform-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS = $(CFLAGS_LINUX)
	LIBS = $(LIBS_LINUX)
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS = $(CFLAGS_MAC)
	LIBS = $(LIBS_MAC)
endif

CFLAGS_END = $(LIBS)



# Default TARGET
all: clean setup $(GUI_TARGET) $(TUI_TARGET) $(CLI_TARGET)

clean:
	@echo "Cleaning up..."
	@if [ -d $(BUILDDIR) ]; then rm -r $(BUILDDIR); fi

setup:
	@echo "Setting up directories..."
	@mkdir -p $(BUILDDIR) $(dir $(OBJ))

# Compile target: build the executable
$(GUI_TARGET): $(filter-out $(BUILDDIR)/$(CLI_TARGET).o $(BUILDDIR)/$(TUI_TARGET).o, $(OBJ))
	@echo "Linking for gui..."
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^ $(CFLAGS_END)

# Compile target: build the executable
$(CLI_TARGET): $(filter-out $(BUILDDIR)/$(TUI_TARGET).o $(BUILDDIR)/$(GUI_TARGET).o, $(OBJ))
	@echo "Linking for cli..."
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^ $(CFLAGS_END)

# Compile target: build the executable
$(TUI_TARGET): $(filter-out $(BUILDDIR)/$(CLI_TARGET).o $(BUILDDIR)/$(GUI_TARGET).o, $(OBJ))
	@echo "Linking for tui..."
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^ $(CFLAGS_END)

# Compile object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "Comppiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(CFLAGS_END)

# Phony targets
.PHONY: all clean setup


