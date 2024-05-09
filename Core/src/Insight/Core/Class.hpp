#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <Insight/Core/If.hpp>
#include <Insight/Core/Help.hpp>
#include <Insight/Core/Variables.hpp>

namespace Insight::Internal
{
	
    ///////////////////////////////////////////////////////////////////////////////////
    // Variable Info
    ///////////////////////////////////////////////////////////////////////////////////
    enum class VariableType
    {
        None = 0,
        Char,
        SChar,
        UChar,
        Short,
        UShort,
        Int,
        UInt,
        Long,
        ULong,
        LongLong,
        ULongLong,
        Float,
        Double,
        LongDouble,
        Bool
    };

    struct Variable
    {
    public:
        std::string Name = {};
        VariableType Type = VariableType::None;

    public:
        Variable() = default;
        Variable(const std::string& name, VariableType type)
            : Name(name), Type(type)
        {
        }
        virtual ~Variable() = default;

        template<typename T>
        constexpr static Variable Create(const std::string& name)
        {
            if constexpr (std::is_same_v<T, char>)
                return Variable(name, VariableType::Char);
            else if constexpr (std::is_same_v<T, signed char>)
                return Variable(name, VariableType::SChar);
            else if constexpr (std::is_same_v<T, unsigned char>)
                return Variable(name, VariableType::UChar);
            else if constexpr (std::is_same_v<T, short>)
                return Variable(name, VariableType::Short);
            else if constexpr (std::is_same_v<T, unsigned short>)
                return Variable(name, VariableType::UShort);
            else if constexpr (std::is_same_v<T, int>)
                return Variable(name, VariableType::Int);
            else if constexpr (std::is_same_v<T, unsigned int>)
                return Variable(name, VariableType::UInt);
            else if constexpr (std::is_same_v<T, long>)
                return Variable(name, VariableType::Long);
            else if constexpr (std::is_same_v<T, unsigned long>)
                return Variable(name, VariableType::ULong);
            else if constexpr (std::is_same_v<T, long long>)
                return Variable(name, VariableType::LongLong);
            else if constexpr (std::is_same_v<T, unsigned long long>)
                return Variable(name, VariableType::ULongLong);
            else if constexpr (std::is_same_v<T, float>)
                return Variable(name, VariableType::Float);
            else if constexpr (std::is_same_v<T, double>)
                return Variable(name, VariableType::Double);
            else if constexpr (std::is_same_v<T, long double>)
                return Variable(name, VariableType::LongDouble);
            else if constexpr (std::is_same_v<T, bool>)
                return Variable(name, VariableType::Bool);

            return Variable(name, VariableType::None);
        }
    };
    ///////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////
    // Class Info
    ///////////////////////////////////////////////////////////////////////////////////
	class Classes
	{
	public:
        Classes() = default;
        virtual ~Classes() = default;

        inline void AddClass(const std::string& name, const std::vector<Variable>& vars = { })
        {
            if (m_Classes.find(name) == m_Classes.end())
            {
                m_Classes[name] = vars;
                return;
            }

            for (auto& var : vars)
                m_Classes[name].push_back(var);
        }
        inline void AddVariable(const std::string& name, const Variable& var)
        {
            m_Classes[name].push_back(var);
        }

        inline std::unordered_map<std::string, std::vector<Variable>>& GetClasses()
        {
            return m_Classes;
        }
        inline std::vector<Variable>& GetVariables(const std::string& name)
        {
            return m_Classes[name];
        }

    private:
        std::unordered_map<std::string, std::vector<Variable>> m_Classes = { };
	};


    ///////////////////////////////////////////////////////////////////////////////////
    // Exports
    ///////////////////////////////////////////////////////////////////////////////////
    inline static Classes ClassSymbols = {};

    extern "C"
    {
        inline EXPORT Insight::Internal::Classes* Insight_GetClasses()
        {
            return &Insight::Internal::ClassSymbols;
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////

}

// Note(Jorben): Used for both function definitions
#define INSIGHT_CLASS_GENERIC(name) \
; \
RUN_FUNCTION(INSIGHT_CONC(name, __COUNTER__), Insight::Internal::ClassSymbols.AddClass, #name)

// Export functions 
#if INSIGHT_EXPORT_CLASSES
#define INSIGHT_CLASS(name) \
INSIGHT_CLASS_GENERIC(name) \
extern "C" \
{ \
EXPORT name* Insight_Create##name() \
{ \
    return new name(); \
} \
EXPORT void Insight_Delete##name(name* instance) \
{ \
    delete instance; \
} \
} \
REQUIRE_SEMICOLON(INSIGHT_CONC(name, __COUNTER__))

// Regular functions 
#else
#define INSIGHT_CLASS(name) \
INSIGHT_CLASS_GENERIC(name) \
REQUIRE_SEMICOLON(INSIGHT_CONC(name, __COUNTER__))

#endif