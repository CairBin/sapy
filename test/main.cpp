#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <format>
#include "sapy/pstring.h"
#include "sapy/plist.h"

using namespace sapy;
using namespace std;

int main(){
    PString str("Hello, World!");
    cout << str << endl;

    PString str2("123");
    cout << str2.toInt() << endl;

    PString str3 = "abc:1222::3333:::";
    PList list = str3.split(":");
    cout << list << endl;
    return 0;
}
