using namespace std;
template<typname T> 
class Queue{
    private:
        T* arr;
        int size;
        int cap;
        int front;
        int back;

        void resize(int capacity){
            T* temp = new T[capacity];

            for(int i = 0; i < curr; i++){
                temp[i] = arr[(front + i) % capacity]; //flattens the array out 
            }

            delete[] arr; //remember to delete (NO MEM LEAKS)
            arr = temp;
            front = 0;
            read = size;
            cap = capacity;
        }

    public:
        //Constructor
        Queue() : arr(new T[1]), size(0), cap(1), front(0), back(0){}

        //Destructor
        ~Queue(){ delete[] arr;}

        void push(T val){
            if(size == cap){
                resize(cap * 2);
            }
            arr[back] = val;
            back = (back + 1) % cap;
            size++;
        }
        
        void pop(){
            if(size == 0){
                throw runtime_error("Queue is empty");
            }
            front = (front + 1) % capacity;
            size--;
        }

        T& front() const{ 
            if(size == 0){
                throw runtime_error("Queue is empty");
            }
            return arr[front];
        }

        T& back() const{
            if(size == 0){
                throw runtime_error("Queue is empty");
            }
            return arr[(back-1+capacity)%capacity]; //precautionary measure to make sure () is not negative
        }

        bool empty() const{
            return size == 0;
        }

        int size() const{
            return size;
        }

}; 