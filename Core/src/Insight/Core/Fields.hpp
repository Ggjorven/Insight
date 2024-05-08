#pragma once

#include <Insight/Core/If.hpp>
#include <Insight/Core/Class.hpp>
#include <Insight/Core/Variables.hpp>
#include <Insight/Core/Functions.hpp>

#define INSIGHT_PRIVATE 1
#define INSIGHT_PUBLIC 0



// Used for all field functions
#define INSIGHT_FIELD_GENERIC(cls, type, name, value) \
type name = value; \
RUN_FUNCTION_NN(INSIGHT_CONC(name, cls), Insight::Internal::ClassSymbols.AddVariable, #cls, Insight::Internal::Variable::Create<type>(#name))

// Export functions // TODO
#if INSIGHT_EXPORT_CLASSES
#define INSIGHT_PUBLIC_FIELD(cls, type, name, value) \
INSIGHT_FIELD_GENERIC(cls, type, name, value) \
extern "C" \
{ \
type* Insight_Get##name##cls(cls* instance) \
{ \
	return &instance->name; \
} \
void Insight_Set##name##cls(cls* instance, type val) \
{ \
	instance->name = val; \
} \
}

#define INSIGHT_PRIVATE_FIELD(cls, type, name, value) \
INSIGHT_FIELD_GENERIC(cls, type, name, value) \
public: \
type* Get##name() \
{ \
	return &name;\
}\
void Set##name(type val) \
{ \
	name = val; \
} \
extern "C" \
{ \
type* Insight_Get##name##cls(cls* instance) \
{ \
	return instance->Get##name(); \
} \
void Insight_Set##name##cls(cls* instance, type val) \
{ \
	instance->Set##name(val); \
} \
private: \
}

// Regular functions
#else
#define INSIGHT_PUBLIC_FIELD(cls, type, name, value) \
INSIGHT_FIELD_GENERIC(cls, type, name, value)

#define INSIGHT_PRIVATE_FIELD(cls, type, name, value) \
INSIGHT_FIELD_GENERIC(cls, type, name, value)

#endif



#define INSIGHT_FIELD(access, cls, type, name, value) INSIGHT_IF(access, INSIGHT_PRIVATE_FIELD(cls, type, name, value), INSIGHT_PUBLIC_FIELD(cls, type, name, value))