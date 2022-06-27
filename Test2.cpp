//
// Created by JackyWoo on 2022/6/15.
//

#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <regex>
#include <shared_mutex>
#include <sstream>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <fcntl.h>
#include <unistd.h>
#include <deque>

using namespace std;

int main()
{

    int16_t aaaa_aab[2] = {1, 2};
    unique_ptr<int16_t *> uniquePtr = std::make_unique<int16_t *>(aaaa_aab);

    cout << *(aaaa_aab) << endl;

    int16_t * aa = *(uniquePtr.get());
    int16_t * bb = *(uniquePtr.release());

    cout << *(aa) << endl;
    cout << *(bb) << endl;

//    cout << **(uniquePtr.get()) << endl;
//    cout << **(uniquePtr.release()) << endl;

    std::vector<char> vec;
    vec[0] = '1';
    cout<<vec[0] <<endl;

}