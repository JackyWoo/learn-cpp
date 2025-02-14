//
// Created by wujianchao5 on 2024/1/11.
//


#include <iostream>
#include <string>

struct Node
{
    explicit Node(int32_t data_) : data(data_), next(nullptr) {}
    int32_t data;
    Node * next;
};


Node * mergeOrderedList(Node * list1, Node * list2)
{
    Node * p1 = list1;
    Node * p2 = list2;

    Node * head = nullptr;
    Node * tail = nullptr;

    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->data < p2->data)
        {
            if (head == nullptr)
            {
                head = p1;
                tail = p1;
            }
            else
            {
                tail->next = p1;
                tail = p1;
            }
            p1 = p1->next;
        }
        else
        {
            if (head == nullptr)
            {
                head = p2;
                tail = p2;
            }
            else
            {
                tail->next = p2;
                tail = p2;
            }
            p2 = p2->next;
        }
    }

    if (p1 != nullptr)
        tail->next = p1;
    else
        tail->next = p2;

    return head;
}

int main()
{
    Node node1(1);
    Node node2(3);
    Node node3(5);
    node1.next = &node2;
    node2.next = &node3;

    Node node4(2);
    Node node5(4);
    Node node6(6);
    node4.next = &node5;
    node5.next = &node6;

    auto * merged = mergeOrderedList(&node1, &node4);

    auto * p = merged;
    while (p != nullptr)
    {
        std::cout << std::to_string(p->data) << std::endl;
        p = p->next;
    }

}
