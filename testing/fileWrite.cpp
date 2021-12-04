#include <cstdlib>
#include <cstdio>
//#include <string>

int main()
{
//    std::string name = "test.txt";    // I'm not modifying it, so it can be char array
    char name[] = "test.txt";

    FILE *fPointer;

    fPointer = fopen(name, "a");
    fprintf(fPointer, "I wish I didn't have to keep on looking this up. It's frustrating.\n");
    fclose(fPointer);

    return EXIT_SUCCESS;
}

