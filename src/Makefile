OS         := $(shell uname -s)

NAME       := 3DViewer_v2

ifeq ($(OS), Darwin)
BIN        := $(NAME).app
else
BIN        := $(NAME)
endif

CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -Werror -Wextra
LDFLAGS    := -lgtest -lgtest_main
CKFLAGS    := -lgcov --coverage

SRC        := model/obj.cc model/utils.cc
TEST_SRC   := tests/main.cc

BUILD_DIR  := build

ifeq ($(OS), Darwin)
INSTALL_DIR       := $(HOME)/Applications
else
INSTALL_DIR       := /tmp/
endif

all: test build run

install: build
	cp -rf $(BUILD_DIR)/$(BIN) $(INSTALL_DIR)
	make clean

uninstall: 
	rm -rf $(INSTALL_DIR)/$(BIN)

clean: clean_test
	rm -rf $(BUILD_DIR)*/ report/ report.info

dvi:
	open dvi.html

dist: build
	mkdir -p dist
	tar -cvf ./dist/$(NAME).tar $(BUILD_DIR)/$(BIN) dvi.html
	gzip ./dist/$(NAME).tar

.PHONY: test
test: clean_test
ifeq ($(OS), Darwin)
	@mkdir -p $(BUILD_DIR) \
		&& $(CXX) $(CXXFLAGS) $(LDFLAGS) $(CKFLAGS) -Imodel $(SRC) $(TEST_SRC) -o $(BUILD_DIR)/tests \
		&& ./$(BUILD_DIR)/tests
else
	@mkdir -p $(BUILD_DIR) \
		&& $(CXX) $(CXXFLAGS) $(LDFLAGS) $(CKFLAGS) -g -pthread $(SRC) $(TEST_SRC) -o $(BUILD_DIR)/tests \
		&& ./$(BUILD_DIR)/tests
endif

gcov_report: test
	lcov -t "$<" -o report.info -c -d .
	lcov --remove report.info \
		$(shell pwd)/tests/* \
		/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/* \
		/usr/local/include/c++/10.3.0/* \
		/usr/local/include/c++/10.3.0/bits/* \
		/usr/local/include/c++/10.3.0/ext/* \
		/usr/local/include/gtest/* \
		/usr/local/include/gtest/internal/* \
		-o report.info
	genhtml -o report report.info
	open ./report/index.html

.PHONY: rebuild
rebuild: clean build

.PHONY: build
build:
	mkdir -p $(BUILD_DIR) \
		&& cd $(BUILD_DIR) \
		&& qmake .. \
		&& make

.PHONY: run
run:
ifeq ($(OS), Darwin)
	./$(BUILD_DIR)/$(BIN)/Contents/MacOS/$(NAME)
else
	./$(BUILD_DIR)/$(BIN)
endif

.PHONY: clean_test
clean_test:
	rm -rf $(BUILD_DIR)/tests *.gcda *.gcno
