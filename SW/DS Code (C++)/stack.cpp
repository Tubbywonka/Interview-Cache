using namespace std;
template<typname T> 
class Stack{
    private:
        T* arr;
        int cap;
        int curr;

        void resize(int capacity){
            T* temp = new T[capacity];

            for(int i = 0; i < curr; i++){
                temp[i] = arr[i];
            }

            delete[] arr; //remember to delete (NO MEM LEAKS)
            arr = temp;
            cap = capacity;
        }

    public:
        //Constructor
        Stack() : arr(new T[1]), cap(1), curr(0){}

        //Destructor
        ~Stack(){
            delete[] arr;
        }

        void push(T val){
            if(curr == cap){
                resize(cap * 2);
            }
            arr[curr] = val;
            curr++;
        }
        
        void pop(){
            if(curr == 0){
                throw runtime_error("Cannot pop from empty stack"); //remember this check
            }
            curr--;
        }

        int size() const{ //remember const
            return curr;
        }

        T& top() const{
            return arr[curr-1];
        }

        bool empty() const{
            return curr == 0;
        }
};