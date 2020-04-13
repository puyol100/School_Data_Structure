#include "Manager.h"

int main(int argc, char* argv[])
{
    const char* commandFilepath = "command.txt";
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m;//program manager
    m.Run(commandFilepath);//Run managing program

    return 0;
}
