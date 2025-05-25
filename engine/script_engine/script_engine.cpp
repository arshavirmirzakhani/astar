#include "script_engine.h"

ScriptEngine::ScriptEngine() {}
ScriptEngine::~ScriptEngine() {}

void ScriptEngine::run(sol::state lua_engine) { lua_engine.script("main()"); }