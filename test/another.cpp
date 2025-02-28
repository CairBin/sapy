#include "another.h"

using namespace std;
using namespace sapy;

// For testing multiple files

void another_func() {
    PString str = "Hello, World!";

    PList list;
    list.append(42);               // int
    list.append(3.14159);          // double
    list.append(std::string("Hello, World!")); // std::string
    list.append("abc");
    list.append('a');
    list.append(PString("PString"));

    PDict dict;
    dict[1] = 3;
    dict[3] = 5;
    dict[5] = 10;
    dict[10] = 20;

    PSet set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

}
