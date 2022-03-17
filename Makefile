TARGET		:= proxy_server
CXX			:= clang++
CXXFLAGS	:= -pedantic-errors -Wall -Wextra -Werror -pedantic -fdiagnostics-color=always
LDFLAGS		:= -L/usr/lib -lstdc++ -lm
BUILD		:= ./build
OBJ_DIR		:= $(BUILD)/objects
APP_DIR		:= $(BUILD)/apps
INC_DIRS	:= $(shell find ./include -type d)
INCLUDE		:= $(addprefix -I,$(INC_DIRS))
SRC			:= $(wildcard srcs/*.cpp)

OBJECTS		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all build clean fclean debug release info re

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@
	@echo $(CXX) $(CXXFLAGS) $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)
	@echo $(CXX) $(CXXFLAGS) $@

-include $(DEPENDENCIES)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -g -fno-limit-debug-info -D GODMODE -D_GLIBCXX_DEBUG
debug: all

release: CXXFLAGS += -O2
release: fclean all

clean:
	-@rm -rvf $(OBJ_DIR)/*

fclean: clean
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     \n"
	@echo "[*] Object dir:      ${OBJ_DIR}     \n"
	@echo "[*] Sources:         ${SRC}         \n"
	@echo "[*] Objects:         ${OBJECTS}     \n"
	@echo "[*] Dependencies:    ${DEPENDENCIES}\n"

re			: clean all
