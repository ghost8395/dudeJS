#include "v8.h"

#include "./src/dudeJS.hpp"

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    auto *dudeJS = new DudeJS();
    std::unique_ptr<v8::Platform> platform =
        dudeJS->initializeV8(argc, argv);

    dudeJS->initializeVM();
    dudeJS->InitializeProgram(filename);
    dudeJS->Shutdown();

    return 0;
}