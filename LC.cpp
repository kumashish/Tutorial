    /* You are given two non-empty linked lists representing two non-negative integers.
    The digits are stored in reverse order, and each of their nodes contains a single digit.
    Add the two numbers and return the sum as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p = nullptr;
        ListNode *head = nullptr;
        int carry = 0;
        while(l1 || l2) {
            auto x = 0;
            x += l1? l1->val:0;            
            x += l2? l2->val:0;
            x += carry;
            if (x > 9)  { carry = 1; x -= 10; }
            else { carry =0; }
            ListNode *l = new ListNode(x);
            if(!p) { p = l; head = l; }
            else {
                p->next = l; p = l;
            }
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if (carry) {
             ListNode *l = new ListNode(1);
            p->next = l;
        }
        return head;
    }
