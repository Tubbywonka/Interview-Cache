//Linked List Problems: DONE

//Reverse LinkedList (EASY)
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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr){
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        return prev;
    }
};

//Merge Two Lists (EASY)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* node = &dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                node->next = list1;
                list1 = list1->next;
            } else {
                node->next = list2;b
                list2 = list2->next;
            }
            node = node->next;
        }

        if (list1) {
            node->next = list1;
        } else {
            node->next = list2;
        }

        return dummy.next;
    }
};


//Linked List Cycle Detection (EASY)
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(!(fast == nullptr) && !(fast->next == nullptr)){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                return true;
            }
        }
        return false;
        
    }
};

//Re-order Linked List (MEDIUM)
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* second = slow->next;
        ListNode* prev = slow->next = nullptr;
        while(second != nullptr){
            ListNode* tmp = second->next;
            second->next = prev;
            prev = second;
            second = tmp;
        } 

        ListNode* first = head;
        second = prev;
        while(second != nullptr){
            ListNode* tmp1 = first->next;
            ListNode* tmp2 = second->next;
            first->next = second;
            second->next = tmp1;
            first = tmp1;
            second = tmp2;
        }
    }
};

//Remove Node from End of LinkedList (MEDIUM)

//two iterations
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* first = head;
        int length = 0;

        while(first){
            length++;
            first = first->next;
        }

        int removeIndex = length - n;
        if (removeIndex == 0) {
            return head->next;
        }

        first = head;
        for(int i = 0; i < removeIndex-1; i++){
            first = first->next;
        }
        first->next = first->next->next;
        return head;

    }
};

//two pointer solution
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* left = dummy;
        ListNode* right = head;

        while (n > 0) {
            right = right->next;
            n--;
        }

        while (right != nullptr) {
            left = left->next;
            right = right->next;
        }

        left->next = left->next->next;
        return dummy->next;
    }
};

//Copy LinkedList with Random Pointer (MEDIUM)
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*,Node*> oldToCopy;
        Node* cur = head;
        oldToCopy[NULL] = NULL;

        while(cur != NULL){
            Node* copy = new Node(cur->val);
            oldToCopy[cur] = copy;
            cur = cur->next;
        }
        
        cur = head;
        while(cur != NULL){
            Node* copy = oldToCopy[cur];
            copy->next = oldToCopy[cur->next];
            copy->random = oldToCopy[cur->random];
            cur = cur->next;
        }

        return oldToCopy[head];
    }
};

//Add Two Numbers (MEDIUM)
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        //l1
        int sum1 = 0;
        int digit = 1;
        while(l1){
            sum1 += l1->val * digit;
            digit *= 10;
            l1 = l1->next;  // Added missing semicolon
        }

        //l2
        int sum2 = 0;
        digit = 1;
        while(l2){
            sum2 += l2->val * digit;
            digit *= 10;
            l2 = l2->next;  // Added missing semicolon
        }

        sum2 += sum1; //result

        // Handle edge case: if sum is 0, return single node with value 0
        if(sum2 == 0) {
            return new ListNode(0);
        }

        ListNode* head = nullptr;
        ListNode* prev = nullptr;
        while(sum2 > 0){
            int value = sum2 % 10;
            ListNode* current = new ListNode(value);  // Complete the line
            if(head == nullptr) {
                head = current;
            } else {
                prev->next = current;
            }
            prev = current;
            sum2 = sum2 / 10;
        }
        
        return head;  // Return the head of the result list
    }
};

//Find Duplicate Number (MEDIUM)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) {
                break;
            }
        }

        int slow2 = 0;
        while (true) {
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2) {
                return slow;
            }
        }
    }
};

//LRU Cache (MEDIUM)
struct Node {
    int key;
    int val;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    private:
        int cap;
        unordered_map<int, Node*> cache;
        Node* left;
        Node* right;

        void remove(Node* node) {
            Node* prev = node->prev;
            Node* nxt = node->next;
            prev->next = nxt;
            nxt->prev = prev;
        }

        void insert(Node* node) {
            Node* prev = right->prev;
            prev->next = node;
            node->prev = prev;
            node->next = right;
            right->prev = node;
        }

    public:
        LRUCache(int capacity) {
            cap = capacity;
            cache.clear();
            left = new Node(0, 0);
            right = new Node(0, 0);
            left->next = right;
            right->prev = left;
        }

        int get(int key) {
            if (cache.find(key) != cache.end()) {
                Node* node = cache[key];
                remove(node);
                insert(node);
                return node->val;
            }
            return -1;
        }

        void put(int key, int value) {
            if (cache.find(key) != cache.end()) {
                remove(cache[key]);
            }
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            insert(newNode);

            if (cache.size() > cap) {
                Node* lru = left->next;
                remove(lru);
                cache.erase(lru->key);
                delete lru;
            }
        }
};

//Merge K Sorted Linked lists (HARD)
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0);
        ListNode* start = &dummy;

        if(lists.size() == 0){
            return nullptr;
        }

        //set start pointers
        while(lists.size() > 1){
            int last = lists.size()-1;
            int slast = last -1;

            ListNode* merged = merge_two(lists[last], lists[slast]);
            lists.pop_back();
            lists.pop_back();

            lists.push_back(merged);
        }
        return lists[0];
        
    }

    ListNode* merge_two(ListNode* list1, ListNode* list2){
        ListNode dummy(0);
        ListNode* node = &dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                node->next = list1;
                list1 = list1->next;
            } else {
                node->next = list2;
                list2 = list2->next;
            }
            node = node->next;
        }

        if (list1) {
            node->next = list1;
        } else {
            node->next = list2;
        }

        return dummy.next;
    }
};

//Reverse nodes in k-group (HARD)
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* groupPrev = dummy;

        while (true) {
            ListNode* kth = getKth(groupPrev, k);
            if (!kth) {
                break;
            }
            ListNode* groupNext = kth->next;

            ListNode* prev = kth->next;
            ListNode* curr = groupPrev->next;
            while (curr != groupNext) {
                ListNode* tmp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = tmp;
            }

            ListNode* tmp = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = tmp;
        }
        return dummy->next;
    }

private:
    ListNode* getKth(ListNode* curr, int k) {
        while (curr && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
    }
};