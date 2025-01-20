# [删除倒数第n个节点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)



```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0); // 创建一个虚拟头节点
        dummy->next = head;
        ListNode* first = dummy;
        ListNode* second = dummy;

        // 移动 first 指针，使其与 second 指针之间有 n 个节点的距离
        //因为二者最开始是指向虚指针而不是头结点，所以得是n+1次循环
        for (int i = 0; i <= n; i++) {
            first = first->next;
        }

        // 移动 first 和 second 指针，直到 first 到达链表的末尾
        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }

        // 删除倒数第 n 个节点
        ListNode* toDelete = second->next;
        second->next = second->next->next;
        delete toDelete; // 释放内存

        ListNode* newHead = dummy->next; // 获取新的头节点
        delete dummy; // 释放虚拟头节点
        return newHead;
    }
};
```