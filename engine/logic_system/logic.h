#pragma once
#include "../global.h"
#include <iostream>
#include <string>
#include <variant>
#include <vector>

// Define enum for logic block types
enum LOGIC_BLOCK_TYPE {
	NONE_LOGIC,
	PRINT,
	BRANCH,
	BRANCH_ELSE,
};

enum LOGIC_OPERATOR_TYPE { NONE_OP, NUMBER, ADD, SUB, MUL, DIV, EQUAL, NEQUAL, GREATER, LESSER, GREATERE, LESSERE };

struct LogicBlock;

struct LogicOperator;

// all data types
using ArgumentType = std::variant<int, float, bool, std::string, LogicBlock*, LogicOperator*>;

struct LogicBlock {
	LOGIC_BLOCK_TYPE type = LOGIC_BLOCK_TYPE::NONE_LOGIC;
	std::vector<ArgumentType> arguments;
	LogicBlock* next_block = nullptr;
};

struct LogicOperator {
	LOGIC_OPERATOR_TYPE type = LOGIC_OPERATOR_TYPE::NONE_OP;
	ArgumentType left_value;
	ArgumentType right_value;
	ArgumentType result_value;

	void process() {};
};

struct LogicFunction {
	std::string function_name;
	LogicBlock first_block;
};

class LogicEngine {
      public:
	LogicEngine();
	~LogicEngine();

	LogicBlock first_block;

	void process();
	void process_block(LogicBlock* block);
};
