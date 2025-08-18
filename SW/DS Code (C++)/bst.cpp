//Binary Tree Implementation
#include <iostream>
#include <queue>
using namespace std;

// Basic TreeNode structure used by both trees
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Basic Binary Tree class
class BinaryTree {
private:
    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
public:
    TreeNode* root;
    
    BinaryTree() : root(nullptr) {}
    
    // Destructor to clean up memory
    ~BinaryTree() {
        deleteTree(root);
    }
    
    // Pre-order traversal: Root -> Left -> Right
    void preOrder(TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    
    // In-order traversal: Left -> Root -> Right
    void inOrder(TreeNode* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }
    
    // Post-order traversal: Left -> Right -> Root
    void postOrder(TreeNode* node) {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->val << " ";
    }
    
    // Level-order traversal (BFS)
    void levelOrder() {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            cout << curr->val << " ";
            
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }
    
    // Calculate height of tree (HEIGHT MEANS #EDGES)
    int height(TreeNode* node) {
        if (!node) return -1;
        return 1 + max(height(node->left), height(node->right));
    }
    
    // Count total nodes
    int size(TreeNode* node) {
        if (!node) return 0;
        return 1 + size(node->left) + size(node->right);
    }

    void deleteTree(TreeNode* root){
        if(!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
};

//----------------------------------------------------------------------------
// Binary Search Tree (BST) Class
//----------------------------------------------------------------------------

class BST : public BinaryTree {
public:
    BST() : BinaryTree() {}
    
    // Insert a value into BST
    void insert(int val) {
        root = insertHelper(root, val);
    }
    
    // Search for a value in BST
    bool search(int val) {
        return searchHelper(root, val);
    }
    
    // Delete a value from BST
    void remove(int val) {
        root = removeHelper(root, val);
    }
    
    // Find minimum value in BST
    int findMin() {
        if (!root) throw runtime_error("Empty tree");
        TreeNode* curr = root;
        while (curr->left) {
            curr = curr->left;
        }
        return curr->val;
    }
    
    // Find maximum value in BST
    int findMax() {
        if (!root) throw runtime_error("Empty tree");
        TreeNode* curr = root;
        while (curr->right) {
            curr = curr->right;
        }
        return curr->val;
    }
    
    // Validate if tree is a valid BST
    bool isValidBST() {
        return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
    }

private:
    TreeNode* insertHelper(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        
        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        }
        // If val == node->val, don't insert duplicates
        
        return node;
    }
    
    bool searchHelper(TreeNode* node, int val) {
        if (!node) return false;
        if (node->val == val) return true;
        
        if (val < node->val) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }
    
    TreeNode* removeHelper(TreeNode* node, int val) {
        if (!node) return nullptr;
        
        if (val < node->val) {
            node->left = removeHelper(node->left, val);
        } else if (val > node->val) {
            node->right = removeHelper(node->right, val);
        } else {
            // Found node to delete
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            } else {
                // Node has two children - find inorder successor
                TreeNode* successor = findMinNode(node->right);
                node->val = successor->val;
                node->right = removeHelper(node->right, successor->val);
            }
        }
        return node;
    }
    
    TreeNode* findMinNode(TreeNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    bool isValidBSTHelper(TreeNode* node, long long minVal, long long maxVal) {
        if (!node) return true;
        
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        return isValidBSTHelper(node->left, minVal, node->val) &&
               isValidBSTHelper(node->right, node->val, maxVal);
    }
};
