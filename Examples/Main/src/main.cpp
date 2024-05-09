#include <Insight/Insight.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    Insight::Dll dll = Insight::Dll("../../bin/Debug-windows/Dll/Dll.dll");
    Insight::DefaultVariableCollection vars = {};
    
    for (auto& [name, internalVars] : dll.GetClasses().GetClasses())
    {
        void* cls = dll.CreateClass(name);
        auto varInterfaces = dll.GetVariables(name, cls);

        vars.Add(varInterfaces);
    }

    return 0;
}