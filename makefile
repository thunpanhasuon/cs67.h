# Compiler settings
CC = gcc
CFLAGS_COMMON = -Wall -Wextra -std=c99
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0 -DDEBUG -fsanitize=address -fsanitize=undefined
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O3 -DNDEBUG -march=native
CFLAGS_TEST = $(CFLAGS_COMMON) -g -O0 -coverage
LDFLAGS_DEBUG = -fsanitize=address -fsanitize=undefined
LDFLAGS_RELEASE = 
LDFLAGS_TEST = -coverage

# Source files
LIB_SOURCES = cs67.c
TEST_SOURCES = cs67_test.c
LIB_OBJECTS_DEBUG = $(LIB_SOURCES:.c=_debug.o)
LIB_OBJECTS_RELEASE = $(LIB_SOURCES:.c=_release.o)
LIB_OBJECTS_TEST = $(LIB_SOURCES:.c=_test.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=_test.o)

# Targets
TARGET_DEBUG = cs67_test_debug
TARGET_RELEASE = cs67_test_release
TARGET_TEST = cs67_test

# Build directories
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release
TEST_DIR = $(BUILD_DIR)/test

# Default target
all: debug

# Help message
help:
	@echo "=========================================="
	@echo "  CS67 Library Build System"
	@echo "=========================================="
	@echo ""
	@echo "Available targets:"
	@echo "  all         - Build debug version (default)"
	@echo "  debug       - Build with debug symbols and sanitizers"
	@echo "  release     - Build optimized release version"
	@echo "  test        - Build and run tests with coverage"
	@echo "  build       - Build both debug and release versions"
	@echo "  clean       - Remove all build artifacts"
	@echo "  clean-debug - Remove debug build artifacts"
	@echo "  clean-release - Remove release build artifacts"
	@echo "  clean-test  - Remove test build artifacts"
	@echo "  rebuild     - Clean and rebuild everything"
	@echo "  help        - Show this help message"
	@echo ""
	@echo "Build configurations:"
	@echo "  DEBUG:   -g -O0 -fsanitize=address,undefined"
	@echo "  RELEASE: -O3 -march=native"
	@echo "  TEST:    -g -O0 -coverage"
	@echo ""

# Debug build
debug: $(DEBUG_DIR) $(DEBUG_DIR)/$(TARGET_DEBUG)

$(DEBUG_DIR)/$(TARGET_DEBUG): $(addprefix $(DEBUG_DIR)/, $(LIB_OBJECTS_DEBUG)) $(addprefix $(DEBUG_DIR)/, $(TEST_OBJECTS))
	@echo "Linking debug executable..."
	$(CC) $(CFLAGS_DEBUG) -o $@ $^ $(LDFLAGS_DEBUG)
	@echo "✓ Debug build complete: $(DEBUG_DIR)/$(TARGET_DEBUG)"

$(DEBUG_DIR)/%_debug.o: %.c cs67.h
	@echo "Compiling $< (debug)..."
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

$(DEBUG_DIR)/%_test.o: %.c cs67.h
	@echo "Compiling $< (debug)..."
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

# Release build
release: $(RELEASE_DIR) $(RELEASE_DIR)/$(TARGET_RELEASE)

$(RELEASE_DIR)/$(TARGET_RELEASE): $(addprefix $(RELEASE_DIR)/, $(LIB_OBJECTS_RELEASE)) $(addprefix $(RELEASE_DIR)/, $(TEST_OBJECTS))
	@echo "Linking release executable..."
	$(CC) $(CFLAGS_RELEASE) -o $@ $^ $(LDFLAGS_RELEASE)
	@echo "✓ Release build complete: $(RELEASE_DIR)/$(TARGET_RELEASE)"

$(RELEASE_DIR)/%_release.o: %.c cs67.h
	@echo "Compiling $< (release)..."
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

$(RELEASE_DIR)/%_test.o: %.c cs67.h
	@echo "Compiling $< (release)..."
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

# Test build with coverage
test: $(TEST_DIR) $(TEST_DIR)/$(TARGET_TEST)
	@echo ""
	@echo "=========================================="
	@echo "  Running Tests"
	@echo "=========================================="
	@cd $(TEST_DIR) && ./$(TARGET_TEST)
	@echo ""
	@echo "Coverage report:"
	@cd $(TEST_DIR) && gcov cs67.c 2>/dev/null | grep -A 3 "cs67.c" || echo "Install gcov for coverage reports"

$(TEST_DIR)/$(TARGET_TEST): $(addprefix $(TEST_DIR)/, $(LIB_OBJECTS_TEST)) $(addprefix $(TEST_DIR)/, $(TEST_OBJECTS))
	@echo "Linking test executable..."
	$(CC) $(CFLAGS_TEST) -o $@ $^ $(LDFLAGS_TEST)
	@echo "✓ Test build complete: $(TEST_DIR)/$(TARGET_TEST)"

$(TEST_DIR)/%_test.o: %.c cs67.h
	@echo "Compiling $< (test)..."
	$(CC) $(CFLAGS_TEST) -c $< -o $@

# Build all configurations
build: debug release
	@echo ""
	@echo "✓ All builds complete!"

# Create build directories
$(DEBUG_DIR):
	@mkdir -p $(DEBUG_DIR)

$(RELEASE_DIR):
	@mkdir -p $(RELEASE_DIR)

$(TEST_DIR):
	@mkdir -p $(TEST_DIR)

# Clean targets
clean: clean-debug clean-release clean-test
	@rm -rf $(BUILD_DIR)
	@rm -f test_input.txt
	@echo "✓ All build artifacts removed"

clean-debug:
	@rm -rf $(DEBUG_DIR)
	@echo "✓ Debug artifacts removed"

clean-release:
	@rm -rf $(RELEASE_DIR)
	@echo "✓ Release artifacts removed"

clean-test:
	@rm -rf $(TEST_DIR)
	@rm -f *.gcda *.gcno *.gcov
	@echo "✓ Test artifacts removed"

# Rebuild everything
rebuild: clean build

# Run debug version
run-debug: debug
	@echo ""
	@echo "Running debug build..."
	@$(DEBUG_DIR)/$(TARGET_DEBUG)

# Run release version
run-release: release
	@echo ""
	@echo "Running release build..."
	@$(RELEASE_DIR)/$(TARGET_RELEASE)

.PHONY: all help debug release test build clean clean-debug clean-release clean-test rebuild run-debug run-release
