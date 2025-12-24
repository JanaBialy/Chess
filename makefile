CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = 

SRCDIR = src
INCDIR = include
OBJDIR = obj
SAVEDIR = saves

TARGET = chess

SOURCES = $(wildcard $(SRCDIR)/*.c)

OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)
	@echo "✓ Build complete! Run with: ./$(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(SAVEDIR):
	@mkdir -p $(SAVEDIR)

clean:
	@echo "Cleaning build files..."
	rm -rf $(OBJDIR) $(TARGET) $(TARGET).exe
	@echo "✓ Clean complete!"

rebuild: clean all

run: all
	@echo "Starting chess game..."
	./$(TARGET)

install: all
	@echo "Installing $(TARGET) to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "✓ Installation complete! Run with: chess"

uninstall:
	@echo "Removing $(TARGET) from /usr/local/bin..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "✓ Uninstall complete!"

help:
	@echo "Chess Game Makefile"
	@echo "==================="
	@echo ""
	@echo "Usage:"
	@echo "  make          - Build the chess game"
	@echo "  make run      - Build and run the game"
	@echo "  make clean    - Remove compiled files"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make install  - Install to system (sudo required)"
	@echo "  make uninstall- Remove from system"
	@echo "  make help     - Show this help message"
	@echo ""

.PHONY: all clean rebuild run install uninstall help