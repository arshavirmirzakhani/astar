#include "logic.h"

LogicEngine::LogicEngine() {}

LogicEngine::~LogicEngine() {}

void LogicEngine::process() {

	LogicBlock* current_block = &this->first_block;

	while (current_block != nullptr) {
		this->process_block(current_block);
		current_block = current_block->next_block; // Move to next block
	}
}

void LogicEngine::process_block(LogicBlock* block) {
	switch (block->type) {
	case LOGIC_BLOCK_TYPE::NONE_LOGIC:
		break;

	case LOGIC_BLOCK_TYPE::PRINT:
		std::visit(
		    [](auto&& arg) {
			    using T = std::decay_t<decltype(arg)>;
			    if constexpr (std::is_same_v<T, LogicBlock*>) {
				    std::cout << "[LogicBlock Pointer]" << std::endl;
			    } else {
				    std::cout << arg << std::endl;
			    }
		    },
		    block->arguments[0]);

	case LOGIC_BLOCK_TYPE::BRANCH:
		std::visit(
		    [&block](auto&& arg) {
			    using T = std::decay_t<decltype(arg)>;
			    if constexpr (std::is_same_v<T, LogicOperator*>) {
				    arg->process();

				    using T = std::decay_t<decltype(arg->result_value)>;

				    if constexpr (!std ::is_same_v<T, bool>) {

					    using T = std::decay_t<decltype(block->arguments[1])>;
					    if constexpr (std::is_same_v<T, LogicBlock*>) {
						    block->next_block = block->arguments[1]
					    }
				    }
			    }
		    },
		    block->arguments[0]);
	}
}