#pragma once
#include "../global.h"
#include <iostream>
#include <string>
#include <variant>
#include <vector>

// Define enum for logic block types
enum LOGIC_BLOCK_TYPE {
	NONE,
	PRINT,
};

// Forward declaration
struct LogicBlock;

// ArgumentType supports int, float, string, and pointer to another LogicBlock
using ArgumentType = std::variant<int, float, std::string, LogicBlock*>;

// Represents a single logic instruction
struct LogicBlock {
	LOGIC_BLOCK_TYPE type = LOGIC_BLOCK_TYPE::NONE;
	std::vector<ArgumentType> arguments;
	LogicBlock* next_block = nullptr;
};

// Represents a function composed of logic blocks
struct LogicFunction {
	std::string function_name;
	LogicBlock first_block;
};

// Engine to process logic blocks
class LogicEngine {
      public:
	LogicEngine();
	~LogicEngine();

	LogicBlock first_block;

	void process();
	void process_block(LogicBlock* block);
};
