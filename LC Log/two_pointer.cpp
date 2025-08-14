//Two Pointer Problems: DONE

//Valid Palindrome (EASY)
class Solution {
public:
    bool isPalindrome(string s) {
        int r = s.size()-1;
        int l = 0;

        while(r > l){
            while(r > l && !isalnum(s[r]))
                r--;

            while(l < r && !isalnum(s[l]))
                l++;

            if(tolower(s[r]) != tolower(s[l])){
                return false;
            }
            r--;
            l++;
        }
        return true;
    }
};

//Two Integer Sum II (MEDIUM)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0;
        int r = numbers.size()-1;
        int sum;
        vector<int> res;

        while(l < r){
            sum = numbers[l] + numbers[r];
            if(sum == target){
                return {l+1,r+1};
            }
            else if(sum < target){
                l++;
            }
            else{
                r--;
            }
        }
        
    }
};


//3Sum (MEDIUM)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int l,r;
        vector<vector<int>> res;

        for(int i = 0; i < nums.size(); i++){
            //if the first number is > 0, ts cooked no triplets
            if(nums[i] > 0)
                break;

            //check for duplicates and move up if its dupe
            if (i > 0 && nums[i] == nums[i - 1]) 
                continue;  

            l = i+1, r = nums.size()-1;
            while(l < r){
                int sum = nums[l] + nums[r] + nums[i];
                if(sum == 0){
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;
                    while(l < r && nums[l] == nums[l-1]){
                        l++;
                    }
                }
                else if (sum < 0){
                    l++;
                }
                else{
                    r--;
                }
            }
        }
        return res;
        
    }
};

//Container with Most Water (MEDIUM)
class Solution {
public:
    int maxArea(vector<int>& heights) {
        int l = 0;
        int r = heights.size()-1;
        int max_wtr = 0;
        int area = 0;

        while(l < r){  
            area = (r-l) * min(heights[l], heights[r]);
            max_wtr = max(area, max_wtr);
            if(heights[l] <= heights[r]){
                l++;
            }
            else{
                r--;
            }
        }

        return max_wtr;
        
    }
};

//Trapping Rainwater (HARD)
class Solution {
public:
    int trap(vector<int>& height) {
        if(height.empty()){
            return 0;
        }


        int l = 0;
        int r = height.size()-1;
        int leftMax = height[l];
        int rightMax = height[r];
        int result = 0;

        while(l < r){
            if(leftMax < rightMax){
                l++;
                leftMax = max(leftMax, height[l]);
                result += leftMax - height[l];
            }
            else {
                r--;
                rightMax = max(rightMax, height[r]);
                result += rightMax - height[r];
            }
            
        }
        return result;
    }
};

