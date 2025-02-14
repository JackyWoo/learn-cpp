/// 141 double-pointers easy

#include "../Node.h"
#include <iostream>

using namespace std;

bool hasCycle(Node * list)
{
    if (list == nullptr)
        return false;

    Node * fast = list;
    Node * slow = list;

    while (fast->next != nullptr)
    {
        fast = fast->next; /// fast move 1 step
        if (fast == slow)
            return true;
        fast = fast->next; /// fast and slow move 1 step
        slow = slow->next;
        if (fast == nullptr)
            return false;
        if (fast == slow)
            return true;
    }
    return false;
}

int main()
{
    auto * n1 = new Node(3);
    auto * n2 = new Node(2);
    auto * n3 = new Node(0);
    auto * n4 = new Node(-4);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n2;

    Node * list = n1;
    cout << hasCycle(list) << endl;

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}
