//Binary Search Problems: DONE

//Binary Search (EASY)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;

        while(l <= r){
            int index = l+(r-l)/2;
            if(nums[index] > target){
                r = index - 1;
            }
            else if(nums[index] < target){
                l = index + 1;
            }
            else {
                return index;
            }
        }
        return -1;
        
    }
};

//Search 2D Matrix (MEDIUM)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int f = 0;
        int l = matrix.size()-1;

        while(f <= l){
            int arr = f+(l-f)/2;
            if(target >= matrix[arr][0] && target <= matrix[arr][matrix[arr].size()-1]){
                int lt = 0;
                int rt = matrix[arr].size()-1;

                while(lt <= rt){
                    int index = lt+(rt-lt)/2;
                    if(matrix[arr][index] > target){
                        rt = index - 1;
                    }
                    else if(matrix[arr][index] < target){
                        lt = index + 1;
                    }
                    else{
                        return true;
                    }
                }
                return false;
            }
            else if(target <= matrix[arr][0]){
                l = arr-1;
            }
            else{
                f = arr+1;
            }
        }
        return false;
    }
};

//Koko Eating Bananas (MEDIUM)
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        sort(piles.begin(),piles.end());

        int min_speed = piles[piles.size()-1];
        int l = 1;
        int r = piles[piles.size()-1];

        while(l <= r){
            int speed = l+(r-l)/2;
            int h_used = 0;
            for(int i = 0; i < piles.size(); i++){
                h_used = h_used + static_cast<int>(ceil((double)(piles[i])/speed));
            }

            if(h_used > h){
                l = speed + 1;
            }
            else if(h_used <= h){
                min_speed = speed;
                r = speed - 1;
            }
        }
        return min_speed;
        
    }
};

//Find Minimum in Rotated Sorted Array (MEDIUM)
class Solution {
public:
    int findMin(vector<int> &nums) {
        int l = 0;
        int r = nums.size()-1;
        int res = INT_MAX;

        while(l <= r){
            if (nums[l] < nums[r]) {
                res = min(res, nums[l]);
                break;
            }

            int mid = l + ((r-l)/2);
            res = min(res, nums[mid]);

            if(nums[mid] >= nums[l]){
                l = mid+1;
            }
            else{

                r = mid-1;
            }
        }
        return res;
    }
};


//Search in Rotated Sorted Array (MEDIUM)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;

        while(l <= r){
            int mid = l+(r-l)/2;

            //check first
            if(nums[mid] == target){
                return mid;
            }
            if(nums[l] <= nums[mid]){
                if(target > nums[mid] || target < nums[l]){
                    l = mid+1;
                }
                else{
                    r = mid-1;
                }
            }
            else{
                if(target < nums[mid] || target > nums[r]){
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
        }
        return -1;
        
    }
};

//Time-based Key Value Store (MEDIUM)
class TimeMap {
private:
    unordered_map<string, vector<pair<int,string>>> values;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        values[key].push_back({timestamp,value});
    }
    
    string get(string key, int timestamp) {
        if(values.find(key) == values.end()){
            return "";
        }
        else{
            //do binary search on timestamp
            int l = 0; 
            int r = values[key].size()-1;
            string best_time = "";
            
            while(l <= r){
                int m = l+(r-l)/2;
                if(values[key][m].first > timestamp){
                    r = m-1;
                }
                else{
                    l = m+1;
                    best_time = values[key][m].second;
                }
            }
            return best_time;
        }
    }
};

//Median of Two Sorted Arrays (HARD)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& A = nums1;
        vector<int>& B = nums2;
        int total = A.size() + B.size();
        int half = (total + 1) / 2;

        if (B.size() < A.size()) {
            swap(A, B);
        }

        int l = 0;
        int r = A.size();
        while (l <= r) {
            int i = (l + r) / 2;
            int j = half - i;

            int Aleft = i > 0 ? A[i - 1] : INT_MIN;
            int Aright = i < A.size() ? A[i] : INT_MAX;
            int Bleft = j > 0 ? B[j - 1] : INT_MIN;
            int Bright = j < B.size() ? B[j] : INT_MAX;

            if (Aleft <= Bright && Bleft <= Aright) {
                if (total % 2 != 0) {
                    return max(Aleft, Bleft);
                }
                return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
            } else if (Aleft > Bright) {
                r = i - 1;
            } else {
                l = i + 1;
            }
        }
        return -1;
    }
};




