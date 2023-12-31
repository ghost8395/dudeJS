#include "v8.h"

#include "./src/myOwnNodeJS.hpp"

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    auto *myOwnNodeJS = new MyOwnNodeJS();
    std::unique_ptr<v8::Platform> platform =
        myOwnNodeJS->initializeV8(argc, argv);

    myOwnNodeJS->initializeVM();
    myOwnNodeJS->InitializeProgram(filename);
    myOwnNodeJS->Shutdown();

    return 0;
}