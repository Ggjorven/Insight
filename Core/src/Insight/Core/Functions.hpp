#pragma once

#include <Insight/Core/Fields.hpp>

#define INSIGHT_FUNC_DEF(name, returntype, ...) typedef returntype (*Insight##name##Def)(__VA_ARGS__)


// TODO: Add functions

#define INSIGHT_FUNC_GENERIC(cls, name, returntype, ...) // TODO

#define INSIGHT_FUNC(access, cls, name, returntype, ...) \
INSIGHT_IF(access, TODO, TODO)
