#pragma once

#include <Insight/Core/If.hpp>
#include <Insight/Core/Help.hpp>
#include <Insight/Core/Class.hpp>
#include <Insight/Core/Variables.hpp>

#define INSIGHT_PRIVATE 1
#define INSIGHT_PUBLIC 0



// Used for all field functions
#define INSIGHT_FIELD_GENERIC(cls, type, name, value) \
type name = value; \
RUN_FUNCTION_NN(INSIGHT_CONC(name, cls), Insight::Internal::ClassSymbols.AddVariable, #cls, Insight::Internal::Variable::Create<type>(#name))

// Export functions
#if INSIGHT_EXPORT_CLASSES
#define INSIGHT_PUBLIC_FIELD(cls, type, name, value) \
public: \
INSIGHT_FIELD_GENERIC(cls, type, name, value)

#define INSIGHT_PRIVATE_FIELD(cls, type, name, value) \
private: \
INSIGHT_FIELD_GENERIC(cls, type, name, value) \
public: \
type Get##name() \
{ \
	return name;\
}\
void Set##name(type val) \
{ \
	name = val; \
} \
private:

// Regular functions
#else
#define INSIGHT_PUBLIC_FIELD(cls, type, name, value) \
public: \
INSIGHT_FIELD_GENERIC(cls, type, name, value)

#define INSIGHT_PRIVATE_FIELD(cls, type, name, value) \
private: \
INSIGHT_FIELD_GENERIC(cls, type, name, value)

#endif

#define INSIGHT_FIELD(access, cls, type, name, value) \
INSIGHT_IF(access, INSIGHT_PUBLIC_FIELD(cls, type, name, value), INSIGHT_PRIVATE_FIELD(cls, type, name, value)) \
REQUIRE_SEMICOLON(INSIGHT_CONC(cls##type##name, __COUNTER__))


#define INSIGHT_PUBLIC_FIELD_EXPORT(cls, type, name) \
extern "C" \
{ \
EXPORT type Insight_Get##name##cls(cls* instance) \
{ \
	return instance->name; \
} \
EXPORT void Insight_Set##name##cls(cls* instance, type val) \
{ \
	instance->name = val; \
} \
}

#define INSIGHT_PRIVATE_FIELD_EXPORT(cls, type, name) \
extern "C" \
{ \
EXPORT type Insight_Get##name##cls(cls* instance) \
{ \
	return instance->Get##name(); \
} \
EXPORT void Insight_Set##name##cls(cls* instance, type val) \
{ \
	instance->Set##name(val); \
} \
}

#if INSIGHT_EXPORT_CLASSES
#define INSIGHT_FIELD_EXPORT(access, cls, type, name) \
INSIGHT_IF(access, INSIGHT_PUBLIC_FIELD_EXPORT(cls, type, name), INSIGHT_PRIVATE_FIELD_EXPORT(cls, type, name)) \
REQUIRE_SEMICOLON(INSIGHT_CONC(cls##type##name, __COUNTER__))

#else // Don't do anything if exporting is disabled
#define INSIGHT_FIELD_EXPORT(access, cls, type, name)

#endif