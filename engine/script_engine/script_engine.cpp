#include "script_engine.h"

void ScriptEngine::run() { this->lua_engine.script("main()"); }