//Tree Problems: DONE

//Invert Binary Tree (EASY)
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;

        TreeNode* temp = root->right;
        root->right = root->left;
        root->left = temp;

        invertTree(root->right);
        invertTree(root->left);

        return root;
        
    }
};


//Find Max Depth (EASY)
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1 + max(maxDepth(root->right), maxDepth(root->left));
    }
};


//Diameter of Binary Tree (EASY)
class Solution {
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;
        dfs(root,res);
        return res;
    }

    int dfs(TreeNode* root, int& res){
        if(!root){
            return 0;
        }
        int left = dfs(root->left, res);
        int right = dfs(root->right, res);
        res = max(res, left+right);
        return 1+max(left,right);
    }
};

//Balanced Binary Tree (EASY)
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return dfs(root)[0] == 1;
    }

private:
    vector<int> dfs(TreeNode* root) {
        if (!root) {
            return {1, 0};
        }

        vector<int> left = dfs(root->left);
        vector<int> right = dfs(root->right);

        bool balanced = (left[0] == 1 && right[0] == 1) &&
                        (abs(left[1] - right[1]) <= 1);
        int height = 1 + max(left[1], right[1]);

        return {balanced ? 1 : 0, height};
    }
};


//Same Binary Tree (EASY)
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if((p && q) && (p->val == q->val)){
            bool left = isSameTree(p->left, q->left);
            bool right = isSameTree(p->right, q->right);
            return left && right;
        }
        else if(!p && !q){
            return true;
        }
        else{
            return false;
        }
    }

};

//Subtree of Another Tree (EASY)
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {

        if(!subRoot){
            return true;
        }

        if(!root){
            return false;
        }
        
        if(isSameTree(root,subRoot)){
            return true;
        }
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot); 
        
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        if((p && q) && (p->val == q->val)){
            bool left = isSameTree(p->left, q->left);
            bool right = isSameTree(p->right, q->right);
            return left && right;
        }
        else if(!p && !q){
            return true;
        }
        else{
            return false;
        }
    }
};
