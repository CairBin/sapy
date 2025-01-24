#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <format>
#include "sapy/pstring.h"
#include "sapy/plist.h"
#include "sapy/piterator.h"

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

    for(auto iter = str_chinese.begin(); iter != str_chinese.end(); iter++){
        cout << PString(*iter) << endl;
    }

    for(auto c : str_chinese){
        cout << PString(c) << endl;
    }

    PString str3 = "abc:1222::3333:::";
    PList list = str3.split(":");
    cout << str3.toString() + ".split() = " << list << endl;


    PString str_strip_before = "  \t\n\r  abc  \t\n\r  ";
    cout << str_strip_before.toString() + ".lstrip() = " << str_strip_before.lstrip().toString() << endl;
    cout << str_strip_before.toString() + ".rstrip() = " << str_strip_before.rstrip().toString() << endl;
    cout << str_strip_before.toString() + ".strip()  = " << str_strip_before.strip().toString() << endl;

    PString str_strip_2 = "abcaabb12345678bcaddbcabac";
    cout << str_strip_2.toString() + ".lstrip(\"abc\") = " << str_strip_2.lstrip("abc").toString() << endl;
    cout << str_strip_2.toString() + ".rstrip(\"abc\") = " << str_strip_2.rstrip("abc").toString() << endl;
    cout << str_strip_2.toString() + ".strip(\"abc\")  = " << str_strip_2.strip("abc").toString() << endl;

    PString str_cap1 = "aBC";
    cout << str_cap1.toString() + ".captilize() = " << str_cap1.captilize().toString() << endl;
    PString str_cap2 = "你好";
    cout << str_cap2.toString() + ".captilize() = " << str_cap2.captilize().toString() << endl;
    PString str_cap3 = " aBC dfdfd";
    cout << str_cap3.toString() + ".captilize() = " << str_cap3.captilize().toString() << endl;

    PString str_center = "abc";
    cout << str_center.toString() + ".center(10) = " << str_center.center(10).toString() << endl;
    cout << str_center.toString() + ".center(10, '-') = " << str_center.center(10, '-').toString() << endl;
    cout << str_center.toString() + ".center(2, '-') = " << str_center.center(2, '-').toString() << endl;
    cout << str_center.toString() + ".center(4, '-') = " << str_center.center(4, '-').toString() << endl;

    PString str_count = "abcabcabc";
    cout << str_count.toString() + ".count(\"abc\") = " << str_count.count("abc") << endl;
    cout << str_count.toString() + ".count(\"abc\",0,9) = " << str_count.count("abc",0,9) << endl;
    cout << str_count.toString() + ".count(\"abc\",0,8) = " << str_count.count("abc",0,8) << endl;
    cout << str_count.toString() + ".count(\"abc\",1,9) = " << str_count.count("abc",1,9) << endl;

    PString fmt = "Hello, {}!";
    cout << fmt.toString() + ".format(\"World\") = " << fmt.format("World").toString() << endl;

    PString str_istitle1 = "Hello World!";
    PString str_istitle2 = "1Cc";
    PString str_istitle3 = "1CC";
    PString str_istitle4 = "1cC";
    PString str_istitle5 = "Ss Abc_cc";
    PString str_istitle6 = "Ss Abc_Cc";
    cout << str_istitle1.toString() + ".istitle() = " << str_istitle1.istitle() << endl;
    cout << str_istitle2.toString() + ".istitle() = " << str_istitle2.istitle() << endl;
    cout << str_istitle3.toString() + ".istitle() = " << str_istitle3.istitle() << endl;
    cout << str_istitle4.toString() + ".istitle() = " << str_istitle4.istitle() << endl;
    cout << str_istitle5.toString() + ".istitle() = " << str_istitle5.istitle() << endl;
    cout << str_istitle6.toString() + ".istitle() = " << str_istitle6.istitle() << endl;

    PString str_isupper = "_";
    PString str_isupper2 = "你好ABC";
    PString str_isupper3 = "你好";
    cout << str_isupper.toString() + ".isupper() = " << str_isupper.isupper() << endl;
    cout << str_isupper2.toString() + ".isupper() = " << str_isupper2.isupper() << endl;
    cout << str_isupper3.toString() + ".isupper() = " << str_isupper3.isupper() << endl;

    PList list2;
    list2.append(42);               // int
    list2.append(3.14159);          // double
    list2.append(std::string("Hello, World!")); // std::string
    list2.append("abc");
    list2.append('a');
    list2.append(PString("PString"));
    list2.append(list);
    cout << list2 << endl;

    for(auto iter = list2.begin(); iter != list2.end(); iter++){
        cout << *iter << endl;
    }

    for(auto c: list2){
        cout << c << endl;
    }

    PList list3;
    list3.append(1,2,3,"Hello", "World", "!");
    cout << list3 << endl;

    auto item1 = list3[0].unwrap<int>();
    int item2 = list3[1];
    
    cout << "item1:" << item1 << endl;
    cout << "item2:" << item2 << ", type: "<<  typeid(item2).name() << endl;
    for(size_t i = 0; i < list3.size(); i++){
        cout << list3[i];
        cout << ", type: " << typeid(list3[i]).name() << endl;
    }


    return 0;
}
