
template<typename T>
struct Node{
    T val;
    Node* next;
    Node* prev;
    Node(T value) : val(value), next(nullptr), prev(nullptr){}

};

template<typename T>
class LinkedList{
    private:
        int size;
        Node<T>* head;

    public:
        LinkedList() : size(0), head(nullptr){}

        ~LinkedList() { clear(); }

        void push_front(const T& value){
            Node<T>* newNode = new Node<T>(value);
            if(!head){
                head = newNode;
            }
            else{
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            size++;
        }

        void push_back(const T& value){
            Node<T>* newNode = new Node<T>(value);
            if(!head){
                head = newNode;
            }
            else{
                Node<T>* curr = head;
                while(curr->next){
                    curr = curr->next;
                }
                curr->next = newNode;
                newNode->prev = curr;
            }
            size++;
        }

        void pop_front(){
            if(!head) return;
            Node<T>* deleteNode = head;
            head = head->next;
            if(head) head->prev = nullptr;
            delete deleteNode;
            size--;
        }

        T& front(){
            if(!head) throw runtime_error("LinkedList empty!");
            return head->val;
        }

        void clear(){
            while(head){
                Node<T>* deleteNode = head;
                head = head->next;
                delete deleteNode;
            }
            size = 0;
        }

        bool empty() const{
            return head == nullptr;
        }

        int size() const{
            return size;
        }
};