//
// Created by wujianchao5 on 2020/12/15.
//

#include <unordered_map>
#include <string>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>

using String = std::string;
using Map = std::unordered_map<String, String>;
using TripleMap = std::unordered_map<String, Map>;

void printMap(const Map & map){
    for(const auto & p : map){
        std::cout << p.first << "\t" << p.second << std::endl;
    }
    std::cout << std::endl;
}

void printTripleMap(const TripleMap & map){
    for(const auto & p : map){
        std::cout << p.first << ":\n\t";
        printMap(p.second);
    }
    std::cout << std::endl;
}


//int main(){
//    using namespace std;
//    Map a;
//    a.insert({"1", "1"});
//    String s1 = "2";
//    String s2 = "3";
////    a.insert({s1, s2});
//    a.emplace(s1, s2);
//    cout<<s1<<" - "<<s2<<endl;
//    Map b;
//    for(const auto & p : a)
//    {
//        b.emplace(p.first, p.second);
//    }
//    printMap(a);
//    printMap(b);
//
//    TripleMap c;
//    c.emplace("a", a);
//
//    printTripleMap(c);
//    printMap(a);
//
//    cout<<&a<<endl;
//    cout<<&(c.cbegin()->second)<<endl;
//
//    Map d;
//    d = a;
//    printMap(d);
//
//    cout<<&(a.cbegin()->first)<<endl;
//    cout<<&(d.cbegin()->first)<<endl;
//
//    test();
//
//
//}