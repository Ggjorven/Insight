#pragma once

// We use a helper function incase 'id' is some kind of function that generates something
// Now it has to be expanded.
#define RUN_FUNCTION_HELPER(id, functionName, ...) \
namespace \
{ \
inline void Run##id() \
{ \
	functionName(__VA_ARGS__); \
} \
\
static int dummy##id = (Run##id(), 0); \
}

#define RUN_FUNCTION_NN_HELPER(id, functionName, ...) \
inline static void Run##id() \
{ \
    functionName(__VA_ARGS__); \
} \
inline static const int dummy##id = (Run##id(), 0);

// Note(Jorben): This runs the function outside of a scope
// The 'id' parameter is just to ensure you can run the same function multiple times 
// 'id' can be an int or whatever as long as it is unique
#define RUN_FUNCTION(id, functionName, ...) RUN_FUNCTION_HELPER(id, functionName, __VA_ARGS__)
// Note(Jorben): NN stands for No Namespace
#define RUN_FUNCTION_NN(id, functionName, ...) RUN_FUNCTION_NN_HELPER(id, functionName, __VA_ARGS__)



#define REQUIRE_SEMICOLON(id) \
struct id \
{} 