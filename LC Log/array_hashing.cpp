//Arrays + Hashing Problems: DONE 

//Contains Duplicate (Easy)
bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}

//isAnagram (Easy) 
class Solution {
public:
    bool isAnagram(string s, string t) {
        std::unordered_map<char, int> s_freq;
        std::unordered_map<char, int> t_freq;
        if(s.size() != t.size()){
            return false;
        }

        for(int i = 0; i < s.size(); i++){
            s_freq[s[i]]++;
            t_freq[t[i]]++;
        }

        for(int j = 0; j < s.size(); j++){
            if(s_freq[s[j]] != t_freq[s[j]]){
                return false;
            }
        }
        return true;

        
    }
};

//Two Sum (Easy)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> dset;

        for(int i = 0; i < nums.size(); i++){
            if(dset.count(target - nums[i]))
                return {dset[target - nums[i]],i};
            dset[nums[i]] = i;
        }
    }
};

//Group Anagrams (Medium)
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        std::unordered_map<string,vector<string>> dict;

        for(int i = 0; i < strs.size(); i++){
            int key[26] = {0};
            std::string word = strs[i];

            for(int j = 0; j < word.length(); j++){
                int index = word[j] - 'a';
                key[index]++;
            }

            std::string keyStr;
            for (int i = 0; i < 26; i++) {
                keyStr += std::to_string(key[i]) + ",";
            }
            dict[keyStr].push_back(word);
        }

        vector<vector<string>> result;
        for (const auto& pair : dict) {
            result.push_back(pair.second);
        }
        return result;
    }
};

//Top K Frequent Elements (Medium)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> counts;
        vector<vector<int>> freq(nums.size());
        vector<int> res;
        
        //keeps track of counts of each #
        for(int i : nums){
            counts[i]++;
        }
        
        //reformat
        for(const auto& entry : counts){
            freq[entry.second-1].push_back(entry.first);
        }

        //return top k
        for(int j = freq.size()-1; j >= 0; j--){
            for(int l : freq[j]){
                res.push_back(l);
                if(res.size() == k){
                    return res;
                }
            }
        }
        return res;
    }
};

//Encode and Decode Strings (Medium)
class Solution {
public:

    string encode(vector<string>& strs) {
        string en_res = "";
        for(string e : strs){
            en_res += to_string(e.size()) + "#" + e;
        }
        return en_res;

    }

    vector<string> decode(string s) {
        vector<string> res;
        int i = 0;
        int j = 0;
        while (i < s.size()) {
            int j = i;
            while (s[j] != '#') {
                j++;
            }
            int length = stoi(s.substr(i, j - i));
            i = j + 1;
            j = i + length;
            res.push_back(s.substr(i, length));
            i = j;
        }
        return res;
    }
};

//Products of Array Except Self (Medium)
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(),1);

        for(int i = 1; i < nums.size(); i++){
            res[i] = res[i-1]*nums[i-1];
        }

        int postfix = 1;
        for(int k = nums.size()-1; k >= 0; k--){
            res[k] = postfix*res[k];
            postfix = postfix*nums[k];
        }
        return res;

    }
};

//Valid Sudoku (Medium)
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int, unordered_set<char>> rows, cols;
        map<pair<int,int>, unordered_set<char>> box;

        for(int r = 0; r < 9; r++){
            for(int c = 0; c < 9; c++){
                if(board[r][c] == '.')
                    continue;

                pair<int,int> box_key = {r/3,c/3};

                if(rows[r].insert(board[r][c]).second == false || 
                   cols[c].insert(board[r][c]).second == false ||
                   box[box_key].insert(board[r][c]).second == false)
                    return false;

                //add everything
                rows[r].insert(board[r][c]);
                cols[c].insert(board[r][c]);
                box[box_key].insert(board[r][c]);
            }
        }
        return true;
        
    }
};

//Longest Consecutive Sequence (Medium)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int longest = 0;
        unordered_map<int, int> seq;

        for(int num : nums){
            if(seq[num] == 0){
                seq[num] = seq[num-1] + seq[num+1] + 1;
                seq[num-seq[num-1]] = seq[num];
                seq[num+seq[num+1]] = seq[num];
                longest = max(longest, seq[num]);
            } 
        }

        return longest;
    }
};
