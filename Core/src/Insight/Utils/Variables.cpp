#include "ispch.h"
#include "Variables.hpp"

namespace Insight
{

	DefaultVariableCollection::DefaultVariableCollection(const std::vector<OpaqueVariable>& vars)
	{
		Add(vars);
	}

	void DefaultVariableCollection::Add(OpaqueVariable var)
	{
		#define INSIGHT_CASE_DVC(type) \
		case Internal::VariableType::type: \
			type##s.push_back(Variable<type>(var.GetVariableInfo(), var.GetInstance(), (Set##type##Fn)var.GetSetter(), (Get##type##Fn)var.GetGetter())); \
			break

		switch (var.GetVariableInfo().Type)
		{
		INSIGHT_CASE_DVC(Char);
		INSIGHT_CASE_DVC(SChar);
		INSIGHT_CASE_DVC(UChar);
		INSIGHT_CASE_DVC(Short);
		INSIGHT_CASE_DVC(UShort);
		INSIGHT_CASE_DVC(Int);
		INSIGHT_CASE_DVC(UInt);
		INSIGHT_CASE_DVC(Long);
		INSIGHT_CASE_DVC(ULong);
		INSIGHT_CASE_DVC(LongLong);
		INSIGHT_CASE_DVC(ULongLong);
		INSIGHT_CASE_DVC(Float);
		INSIGHT_CASE_DVC(Double);
		INSIGHT_CASE_DVC(LongDouble);
		INSIGHT_CASE_DVC(Bool);
		}
	}

	void DefaultVariableCollection::Add(const std::vector<OpaqueVariable> vars)
	{
		for (auto& var : vars)
			Add(var);
	}

}