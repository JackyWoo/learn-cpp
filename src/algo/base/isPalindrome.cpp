/// 25 base hard

#include "../Node.h"
#include <vector>
#include <iostream>

using namespace std;

bool isPalindrome(Node * list)
{
    vector<int> arr;
    Node * node = list;
    while (node)
    {
        arr.push_back(node->value);
        node = node->next;
    }
    int size = arr.size();
    int n = size / 2;
    for (int i=0; i<=n; i++)
    {
        if (arr[n] != arr[size -1 - n])
            return false;
    }
    return true;
}

int main()
{
    auto * n1 = new Node(1);
    auto * n2 = new Node(2);
    auto * n3 = new Node(3);
    auto * n4 = new Node(4);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = nullptr;

    cout << isPalindrome(n1) << endl;

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}
