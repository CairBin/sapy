#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <format>
#include <cassert>
#include "sapy/pstring.h"
#include "sapy/plist.h"
#include "sapy/piterator.h"
#include "sapy/pdict.h"
#include "sapy/pset.h"

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
        cout << *iter << endl;
    }

    for(auto c : str_chinese){
        cout << PString(c) << endl;
    }

    PString str3 = "abc:1222::3333:::";
    PList list = str3.split(":");
    cout << str3.toString() + ".split(\":\") = " << list << endl;
    cout << str3.toString() + ".split() = " << str3.split() << endl;
    cout << str3.toString() + ".split(\":\",2) = " << str3.split(":",2) << endl;
    cout << str3.toString() + ".rsplit(\":\") = " << str3.rsplit(":") << endl;
    cout << str3.toString() + ".rsplit() = " << str3.rsplit() << endl;
    cout << str3.toString() + ".rsplit(\":\",2) = " << str3.rsplit(":",2) << endl;

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

    PString str_join = "a";
    PList join_list;
    join_list.append("a","b","c","d");
    // PList join_list2 = PList("a", "b", "c", "d");
    PString join_str = "sdf";
     cout << str_join.toString() + ".join("<< join_str.toString() << ") = " << str_join.join(join_list).toString() << endl;
    cout << str_join.toString() + ".join(" << join_list.toString() << ") = " << str_join.join(join_str).toString() << endl;

    auto transtable = PString::maketrans("abc", "123");
    auto transtable2 = PString::maketrans("abc", "123", "def");

    cout << "PString::maketrans(\"abc\", \"123\") = " << transtable.toString() << endl;
    cout << "PString::maketrans(\"abc\", \"123\", \"def\") = " << transtable2.toString() << endl;
    // cout << str_translate.toString() + ".translate(" << transtable.toString() << ") = " << str_translate.translate(transtable).toString() << endl;
    // cout << str_translate.toString() + ".translate(" << transtable2.toString() << ") = " << str_translate.translate(transtable2).toString() << endl;

    PString str_partition = "acbcc hello sdfdsfd";
    cout << str_partition.toString() + ".partition(\"hello\") = " << str_partition.partition("hello").toString() << endl;
    cout << str_partition.toString() + ".partition(\"hee--\") = " << str_partition.partition("hee--").toString() << endl;

    PString str_removeprefix = "TestHook";
    PString str_removeprefix2 = "BaseTestCase";
    cout << str_removeprefix.toString() + ".remoteprefix(\"Test\") = " << str_removeprefix.remoteprefix("Test").toString() << endl;
    cout << str_removeprefix2.toString() + ".remoteprefix(\"Test\") = " << str_removeprefix2.remoteprefix("Test").toString() << endl;

    PString str_removesuffix = "MiscTests";
    PString str_removesuffix2 = "TmpDirMixin";
    cout << str_removesuffix.toString() + ".removesuffix(\"Tests\") = " << str_removesuffix.removesuffix("Tests").toString() << endl;
    cout << str_removesuffix2.toString() + ".removesuffix(\"Tests\") = " << str_removesuffix2.removesuffix("Tests").toString() << endl;

    PString str_replace = "abcabcabc";
    cout << str_replace.toString() + ".replace(\"abc\", \"123\") = " << str_replace.replace("abc", "123").toString() << endl;
    cout << str_replace.toString() + ".replace(\"abc\", \"123\", 2) = " << str_replace.replace("abc", "123", 2).toString() << endl;
    cout << str_replace.toString() + ".replace(\"abc\", \"-\") = " << str_replace.replace("abc", "-").toString() << endl;
    cout << str_replace.toString() + ".replace(\"abc\", \"|....\") = " << str_replace.replace("abc", "|....").toString() << endl;

    PString str_find = "acbcc hello sdfdsfd";
    cout << str_find.toString() + ".find(\"hello\") = " << str_find.find("hello") << endl;
    cout << str_find.toString() + ".find(\"hello\",6,10) = " << str_find.find("hello",6,10) << endl;
    cout << str_find.toString() + ".find(\"hello\",6,11) = " << str_find.find("hello",6,11) << endl;
    cout << str_find.toString() + ".rfind(\"hello\") = " << str_find.rfind("hello") << endl;
    cout << str_find.toString() + ".rfind(\"hello\",6,10) = " << str_find.rfind("hello",6,10) << endl;
    cout << str_find.toString() + ".rfind(\"hello\",6,11) = " << str_find.rfind("hello",6,11) << endl;

    PString str_rpartition = "acbcc hello hello sdfdsfd";
    cout << str_rpartition.toString() + ".rpartition(\"hello\") = " << str_rpartition.rpartition("hello").toString() << endl;

    PString str_splitlines = "acbcc hello\nhello\nsdfdsfd\rxxx\r\nxxx\n\rsss\x1cssds";
    cout << str_splitlines.toString() + ".splitlines() = " << str_splitlines.splitlines().toString() << endl;
    cout << str_splitlines.toString() + ".splitlines(true) = " << str_splitlines.splitlines(true).toString() << endl;

    PString str_swapcase = "你好AbCdEf";
    cout << str_swapcase.toString() + ".swapcase() = " << str_swapcase.swapcase().toString() << endl;
    cout << str_swapcase.toString() + ".swapcase().swapcase() = " << str_swapcase.swapcase().swapcase().toString() << endl;

    PString str_title = "they're bill's friends from the UK";
    cout << str_title.toString() + ".title() = " << str_title.title().toString() << endl;

    PDict trans_table = PString::maketrans("123","abc");
    PString str_translate = "123abc---123456712123";
    cout << str_translate.toString() << ".translate(" << trans_table.toString() << ") = " << str_translate.translate(trans_table).toString() << endl;

    PString str_zfill = "42";
    cout << str_zfill.toString() + ".zfill(5) = " << str_zfill.zfill(5).toString() << endl;
    cout << str_zfill.toString() + ".zfill(2) = " << str_zfill.zfill(2).toString() << endl;
    PString str_zfill2 = "-42";
    cout << str_zfill2.toString() + ".zfill(5) = " << str_zfill2.zfill(5).toString() << endl;
    cout << str_zfill2.toString() + ".zfill(2) = " << str_zfill2.zfill(2).toString() << endl;

    PString str_expandtabs = "\n67890\t";
    PString str_expandtabs2 = "01\t012\t0123\t01234";
    cout << str_expandtabs.toString() + ".expandtabs() = " << str_expandtabs.expandtabs().toString()  << " len=" <<
    str_expandtabs.expandtabs().length() << endl;
    cout << str_expandtabs2.toString() + ".expandtabs(4) = " << str_expandtabs2.expandtabs(4).toString()  << " len=" <<
    str_expandtabs2.expandtabs(4).length() << endl;

    PString str_encode = "你好,abc";
    cout << str_encode.toString() + ".encode(\"utf-8\") = " << str_encode.encode("utf-8").toString() <<
    "len = " << str_encode.encode("utf-8").length() << std::endl;
    cout << str_encode.toString() + ".encode(\"utf-16\") = " << str_encode.encode("utf-16").toString() <<
    "len = " << str_encode.encode("utf-16").length() << std::endl;
    cout << str_encode.toString() + ".encode(\"utf-32\") = " << str_encode.encode("utf-32").toString() <<
    "len = " << str_encode.encode("utf-32").length() << std::endl;

    PString str_equal = "你好,abc";
    PString str_equal_other = "你好,abc";
    const char* str_equal_other2 = "你好,abc";
    std::string str_equal_other3 = "你好,abc";
    PString str_equal_ = "您好,abc";
    cout << str_equal.toString() + " == " << str_equal_other.toString() << " = " << (str_equal == str_equal_other) << std::endl;
    cout << str_equal.toString() + " == " << str_equal_other2 << " = " << (str_equal == str_equal_other2) << std::endl;
    cout << str_equal.toString() + " == " << str_equal_other3 << " = " << (str_equal == str_equal_other3) << std::endl;
    cout << str_equal_.toString() + " == " << str_equal_other.toString() << " = " << (str_equal_ == str_equal_other) << std::endl;
    cout << str_equal_.toString() + " == " << str_equal_other2 << " = " << (str_equal_ == str_equal_other2) << std::endl;
    cout << str_equal_.toString() + " == " << str_equal_other3 << " = " << (str_equal_ == str_equal_other3) << std::endl;
    

    std::vector<PString> vec = {"a", "b", "c", "d", "e","aaa","abc","ce"};
    std::sort(vec.begin(), vec.end());
    for(auto item: vec){
        cout << item << ",";
    }
    cout << endl;

    PAnyWrapper wrap = "Hello, World!";
    PString wrap_str = wrap;
    std::cout << wrap_str << std::endl;

    PList list2;
    list2.append(42);               // int
    list2.append(3.14159);          // double
    list2.append(std::string("Hello, World!")); // std::string
    list2.append("abc");
    list2.append('a');
    list2.append(PString("PString"));
    list2.appendSingle(list);
    cout << list2 << endl;

    PList list_init1 = {1,2,3,4,5,6,7,8,9,10};
    cout << list_init1 << endl;
    PList list_init2 = {"Hello", "World", "!", 1, 2, 3, 3.14159};
    cout << list_init2 << endl;


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

    PList list4({1, 1, 4, 5, "N"});
    PList list5({1, 2});

    cout << "list4 + list5: " << list4 + list5 << endl;
    list4.extend({1, 2});
    cout << "list4.extend({1, 2}): " << list4 << endl;
    list4 += list5;
    cout << "list4 += list5: " << list4 << endl;

    cout << "list4.index(\"N\"): " << list4.index("N") << endl;

    list4.reverse();
    cout << "reversed list4: " << list4 << endl;

    PDict dict;
    dict[PString("key1")] = PString("value1");
    dict[PString("key2")] = PString("value2");
    dict[PString("key3")] = 128;
    dict[PString("key4")] = 3.14159;
    dict[999] = PString("value5");
    dict[3.14159] = PString("value6");
    dict[PString("key7")] = PString("value7");
    cout << dict << endl;

    auto value1 = dict.find(PString("key1"));
    auto value2 = dict.find(PString("key2"));
    std::cout << dict[PString("key1")]<< std::endl;
    std::cout << dict[PString("key2")] << std::endl;
    std::cout << dict[PString("key3")] << std::endl;
    std::cout << dict[PString("key4")] << std::endl;
    std::cout << dict[999] << std::endl;
    std::cout << dict[3.14159] << std::endl;

    PDict dict2 = {
        {"key1", PString("value1")},
        {"key2", PString("value2")},
        {"key3", 128}
    };

    std::cout <<dict2 <<std::endl;
    std::cout << "dict2[\"key3\"] = " << dict2["key3"] << std::endl; 

    for(auto iter = dict.begin(); iter != dict.end(); iter++){
        cout << iter->first << ": " << iter->second <<std::endl;
    }

    for(auto iter: dict){
        cout << iter.first << ": " << iter.second <<std::endl;
    }

    PSet s1 = {1,2,3,4,5,6,7,8,9,10};
    PSet s2 = {1,2,3,4,5,"str","hello", "", 3.14159};

    cout <<"s1: " << s1 << endl;
    cout <<"s2: " << s2 << endl;

    for(auto item: s1){
        cout << item << endl;
    }

    s1.clear();
    cout << "s1.clear() = " << s1 << endl;
    
    for(int i = 0; i < 10; i++){
        s1.add(i);
    }
    cout << "s1.add(0-9) = " << s1 << endl;

    cout << "s1.contain(5) = " << s1.contain(5) << endl;
    cout << "s1.contain(10) = " << s1.contain(10) << endl;

    s1.remove(5);
    cout << "s1.remove(5) -> s1:  " << s1 << endl;
    

    cout << "s1.difference(s2) = " << s1.difference(s2) << endl;
    cout << "s1.intersection(s2) = " << s1.intersection(s2) << endl;
    cout << "s1.union_(s2) = " << s1.union_(s2) << endl;
    cout << "s1.symmetric_difference(s2) = " << s1.symmetric_difference(s2) << endl;
    cout << "s1.isdisjoint(s2) = " << s1.isdisjoint(s2) << endl;
    cout << "s1.issubset(s2) = " << s1.issubset(s2) << endl;
    cout << "s1.issuperset(s2) = " << s1.issuperset(s2) << endl;
    //cout << "s1.pop() = " << s1.pop() << endl;
    cout << "s1.copy() = " << s1.copy() << endl;
    cout << "s1.size() = " << s1.size() << endl;
    s1.intersection_update(s2);
    cout << "s1.intersection_update(s2) -> s1 = " << s1 << endl;
    s1.difference_update(s2);
    cout << "s1.differece_update(s2) -> s1 = " << s1 << endl;
    s1.symmetric_difference_update(s2);
    cout << "s1.symmetric_difference_update(s2) -> s1 = " << s1 << endl;

    s1.remove("hello");
    cout << "s1.remove(\"hello\") -> s1 = " << s1 << endl;

    PSet s3 = {PSet({1,2,3}), PSet({4,5,6}), PSet({7,8,9})};
    cout << "s3 = " << s3 << endl;
    for(auto item: s3){
        cout << item << endl;
    }

    for(auto iter = s3.begin(); iter != s3.end(); iter++){
        PSet item = *iter;
        cout << item << endl;
    }

    PSet s4 = {PSet({"¬3"}), PSet({"1", "2", "3"})};

    s4.add(PSet({"1", "2", "4"}));

    cout << "s4 = " << s4 << endl;

    for(auto it = s4.begin(); it != s4.end(); it++){
        for(auto jt = it; jt != s4.end(); jt++){
            if(it == jt) continue;
            PSet elem1 = *it;
            PSet elem2 = *jt;
            cout << "elem1: " << elem1 << ", elem2: " << elem2 << endl;
        }
    }
    s4.add(PSet({"1", "2", "3"}));
    cout << "s4.add(PSet({\"1\", \"2\", \"3\"})) -> s4 = " << s4 << endl;
    s4.discard(PSet({"1", "2", "3"}));
    cout << "s4.discard(PSet({\"1\", \"2\", \"3\"})) -> s4 = " << s4 << endl;
    s4.add(2);
    cout << "s4.add(2) -> s4 = " << s4 << endl;
    s4.add(2);
    cout << "s4.add(2) -> s4 = " << s4 << endl;
    return 0;
}
