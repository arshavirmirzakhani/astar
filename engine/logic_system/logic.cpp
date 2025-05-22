#include "logic.h"

LogicEngine::LogicEngine() {}

LogicEngine::~LogicEngine() {}

void LogicEngine::process() {

	LogicBlock current_block = this->first_block;

	while (true) {
		this->process_block(&current_block);

		if (current_block.next_block == nullptr) {
			break;
		} else {
			current_block = *current_block.next_block;
		}
	}
}

void LogicEngine::process_block(LogicBlock* block) {
	switch (block->type) {
	case LOGIC_BLOCK_TYPE::NONE:
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
	}
}