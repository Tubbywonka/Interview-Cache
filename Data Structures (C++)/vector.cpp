using namespace std;
template<typname T> 
class Vector{
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
        //Constructors
        Vector() : arr(new T[1]), cap(1), curr(0){}

        Vector(int capacity) : arr(new T[capacity]), cap(capacity), curr(0){} 

        //Destructor
        ~Vector(){
            delete[] arr;
        }

        void push_back(T val){
            if(curr == cap){
                resize(cap * 2);
            }
            arr[curr] = val;
            curr++;
        }
        
        void pop_back(){
            if(curr == 0){
                throw runtime_error("Cannot pop from empty vector"); //remember this check
            }
            curr--;
        }

        int size() const{ //remember const
            return curr;
        }

        //capacity
        int capacity() const{ //remember const
            return cap;
        }

        //[] operator
        T& operator[](int index){
            if(index >= curr){
                throw out_of_range("Index out of range") //remember this check
            }
            return arr[index];
        }

        void clear(){
            curr = 0;
        }
};