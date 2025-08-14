//Bit Manipulation Problems: DONE

//Single Number (EASY)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int num : nums){
            res = res ^ num;
        }
        return res;
        
    }
};


//Number of 1s (EASY)
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for(int i = 0; i < 32; i++){
            if(n & 1){
                count++;
            }
            n = n >> 1;
        }
        return count;
    }
};

//Counting Bits - DP (EASY) 
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);

        int index = 1;
        int callback = 1;
        while(index <= n){
            if(index == 2*callback){
                callback = callback *2;
            }
            res[index] = 1 + res[index-callback];
            index++;
        }
        return res;
        
    }
};

//Reverse Bits (EASY)
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0; i < 32; i++){
            uint32_t bit = (n >> i) & 1;
            res += bit << (31-i);
        }
        return res;
    }
};

//Find Missing Number (EASY)
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int all = 0;
        int some = nums[0];

        for(int i = 1; i < nums.size(); i++){
            some = some ^ nums[i];
        }

        for(int j = 0; j < nums.size()+1; j++){
            all = all ^ j;
        }

        return all ^ some;
        
    }
};


//Sum of Two Integers (MEDIUM)
class Solution {
public:
    int getSum(int a, int b) {
        int carry = 0, res = 0, mask = 0xFFFFFFFF;

        for (int i = 0; i < 32; i++) {
            int a_bit = (a >> i) & 1;
            int b_bit = (b >> i) & 1;
            int cur_bit = a_bit ^ b_bit ^ carry;
            carry = (a_bit + b_bit + carry) >= 2 ? 1 : 0;
            if (cur_bit) {
                res |= (1 << i);
            }
        }

        if (res > 0x7FFFFFFF) {
            res = ~res + 1;
        }

        return res;
    }
};


//Reverse Integer (MEDIUM)
class Solution {
public:
    int reverse(int x) {
        int res = 0;
        const int MIN = -2147483648; // -2^31
        const int MAX = 2147483647;  // 2^31 - 1

        while(x != 0){
            int val = x % 10;
            x = x/10;

            if (res > MAX / 10 || (res == MAX / 10 && val > MAX % 10))
                return 0;
            if (res < MIN / 10 || (res == MIN / 10 && val < MIN % 10))
                return 0;

            res = (res * 10) + val;
        }

        return res;
    }
};

