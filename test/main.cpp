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

    PString str_opt; 
    str_opt = str + str2 + "abc";
    str_opt = "abc" + str_opt;
    str_opt = string("std_String") + str_opt;
    str_opt += "abc";
    str_opt += str2;
    str_opt += string("std_String");
    cout << str_opt << endl;


    PString str_chinese = "你好，世界！";
    for(size_t i = 0; i < str_chinese.length(); i++){
        cout << str_chinese.toString() +"[" + std::to_string(i) + "] = " + str_chinese[i] << endl;
    }

    PString str3 = "abc:1222::3333:::";
    PList list = str3.split(":");
    cout << str3.toString() + ".split() = " << list << endl;
    return 0;
}
