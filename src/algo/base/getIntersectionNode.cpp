/// 160 ds medium

#include "../Node.h"
#include <iostream>

using namespace std;

int getIntersectionNode(Node * l1, Node * l2)
{
    Node * l1_p = l1;
    Node * l2_p = l2;

    while (l1_p != l2_p)
    {
        l1_p = l1_p == nullptr ? l1 : l1_p->next;
        l2_p = l2_p == nullptr ? l2 : l2_p->next;
    }

    return l1_p->value;
}

int main()
{
    auto * n1 = new Node(1);
    auto * n2 = new Node(2);
    auto * n3 = new Node(3);
    auto * n4 = new Node(4);
    auto * n5 = new Node(5);
    auto * n6 = new Node(6);
    n1->next = n2;
    n2->next = n3;
    n3->next = n5;
    n4->next = n5;
    n6->next = n6;

    Node * l1 = n1;
    Node * l2 = n3;
    cout << getIntersectionNode(l1, l2) << endl;

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
}
