//Sliding Window Problems: DONE

//Buying + Selling Stock (EASY)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxP = 0;
        int minB = prices[0];
        
        for(int& price : prices){
            maxP = max(maxP, price-minB);
            minB = min(minB, price);
        }
        return maxP;
        
    }
};

//Longest Substring Without Repeating Characters (MEDIUM)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            while (charSet.find(s[r]) != charSet.end()) {
                charSet.erase(s[l]);
                l++;
            }
            charSet.insert(s[r]);
            res = max(res, r - l + 1);
        }
        return res;
    }
};

//Longest Repeating Character Replacement (MEDIUM)
class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char,int> counts;
        int res = 0; 
        int l = 0;
        int maxf = 0;

        for(int r = 0; r < s.size(); r++){
            counts[s[r]]++;
            maxf = max(maxf,counts[s[r]]);

            //check + fix valid
            while((r-l+1)-maxf > k){
                counts[s[l]]--;
                l++;
            }

            res = max(res, r-l+1);
        }
        return res;

    }
};

//Permutation in String (MEDIUM)
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> s1_counts(26,0);
        vector<int> s2_counts(26,0);

        for(int i = 0; i < s1.size(); i++){
            int index = s1[i] - 'a';
            s1_counts[index]++;
        }

        int l = 0;
        for(int r = 0; r < s2.size(); r++){
            while(r-l >= s1.size()){
                int reduce = s2[l] - 'a';
                s2_counts[reduce]--;
                l++;
            }
            int inc = s2[r]-'a';
            s2_counts[inc]++;
            if(s1_counts == s2_counts){
                return true;
            }

        }
        return false;
    }
};

//Minimum Window Substring (HARD)
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> t_counts;
        unordered_map<char,int> window;
        
        //log the t counts
        for(int i; i < t.size(); i++){
            t_counts[t[i]]++;
        }

        int l = 0; 
        int have = 0; 
        int need = t_counts.size();
        pair<int, int> res = {-1, -1};
        int resLen = INT_MAX;

        for(int r = 0; r < s.size(); r++){
            window[s[r]]++;

            if(t_counts.count(s[r]) && window[s[r]] == t_counts[s[r]]){
                have++;
            }

            while (have == need){
                if ((r - l + 1) < resLen) {
                    resLen = r - l + 1;
                    res = {l, r};
                }

                window[s[l]]--;
                if (t_counts.count(s[l]) && window[s[l]] < t_counts[s[l]]) {
                    have--;
                }
                l++;
            }
          
        }

        return resLen == INT_MAX ? "" : s.substr(res.first, resLen);
        
    }
};

//Sliding Window Maximum (HARD)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> output(n - k + 1);
        deque<int> q;
        int l = 0, r = 0;

        while (r < n) {
            while (!q.empty() && nums[q.back()] < nums[r]) {
                q.pop_back();
            }
            q.push_back(r);

            if (l > q.front()) {
                q.pop_front();
            }

            if ((r + 1) >= k) {
                output[l] = nums[q.front()];
                l++;
            }
            r++;
        }

        return output;
    }
};

//Sliding Window Maximum (HARD)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> output(n - k + 1);
        deque<int> q;
        int l = 0, r = 0;

        while (r < n) {
            while (!q.empty() && nums[q.back()] < nums[r]) {
                q.pop_back();
            }
            q.push_back(r);

            if (l > q.front()) {
                q.pop_front();
            }

            if ((r + 1) >= k) {
                output[l] = nums[q.front()];
                l++;
            }
            r++;
        }

        return output;
    }
};