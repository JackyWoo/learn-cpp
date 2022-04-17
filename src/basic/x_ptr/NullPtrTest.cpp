//
// Created by wujianchao5 on 2020/12/23.
//

#include <iostream>

void nullPtrTest(){
    char* s = nullptr;
    char* s1 = nullptr;
//    std::cout<< *s<<std::endl;
//    std::cout<< *s1<<std::endl;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"
    printf("%s\\n",*s);
    printf("%s\\n",*s1);
#pragma clang diagnostic pop
}

/**
 * print 空指针会报错
 * @return
 */
int main(){
    nullPtrTest();
}