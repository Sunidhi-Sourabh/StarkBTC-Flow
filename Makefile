# Project metadata
TARGET = starkbtc
SRC_DIR = src
OBJ_DIR = build
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default build
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
    @echo "🔧 Linking $(TARGET)..."
    $(CC) $(CFLAGS) -o $@ $^

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    @mkdir -p $(OBJ_DIR)
    @echo "📦 Compiling $<..."
    $(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
    @echo "🧹 Cleaning build..."
    rm -rf $(OBJ_DIR) $(TARGET)

# Run CLI
run: $(TARGET)
    @echo "🚀 Running StarkBTC Flow..."
    ./$(TARGET) --btc-swap --verify-wallet --score --report

.PHONY: all clean run

