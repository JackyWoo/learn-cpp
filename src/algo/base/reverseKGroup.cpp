/// 25 base hard

#include "../Node.h"
#include <iostream>

using namespace std;

void reverseSubList(Node * head_pre, Node * head, Node * tail, Node * tail_next)
{
    if (head == tail)
        return;

    Node * head_next = head->next;
    head->next = tail_next;

    if (head_pre)
        head_pre->next = tail;

    Node * node = head_next;
    Node * pre = head;
    while (node != tail)
    {
        Node * next = node->next;
        node->next = pre;
        node = next;
        pre = node;
    }
    node->next = pre;
}

Node * reverseKGroup(Node * list, int k)
{
    if (list->next == nullptr)
        return list;

    if (k == 1)
        return list;

    Node * res;

    Node * head_pre = nullptr;
    Node * g_head = list;
    Node * g_tail;

    int n = 0;
    while (list != nullptr)
    {
        if (n % k == 0)
            g_head = list;

        if (list->next == nullptr) /// the last group
        {
            reverseSubList(head_pre, g_head, list, nullptr);
            list = g_head;
            if (n == k -1) /// also is the first group
                res = list;
        }
        else if (n % k == k - 1)
        {
            g_tail = list;
            reverseSubList(head_pre, g_head, g_tail, g_tail->next);
            if (n == k -1) /// the first group
                res = g_tail;
            list = g_head;
            head_pre = g_head;
            g_head = nullptr;
        }

        n++;
        list = list->next;
    }

    return res;
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

    int k = 2;
    auto * node = reverseKGroup(n1, k);

    while (node)
    {
        cout << node->value << " " << endl;
        node = node->next;
    }

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}
