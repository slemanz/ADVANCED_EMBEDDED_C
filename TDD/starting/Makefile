CC= gcc
CFLAGS = -c -Wall -std=gnu99 -O0

TEST_DIR = tests
BUILD_DIR = build
UNITY_DIR = ../unity

INCLUDES += -I ../unity
INCLUDES += -I tests

TESTS += $(BUILD_DIR)/LedDriverTests.o
TESTS += $(BUILD_DIR)/AllTestRunner.o

UNITY += $(BUILD_DIR)/unity_fixture.o
UNITY += $(BUILD_DIR)/unity.o

all: $(BUILD_DIR) test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TEST_DIR)/$(*).c

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(UNITY_DIR)/$(*).c

test: $(TESTS) $(UNITY)
	$(CC) $(INCLUDES) $^ -o $(BUILD_DIR)/run_tests
	./$(BUILD_DIR)/run_tests


clean:
	rm -rf $(BUILD_DIR)/*