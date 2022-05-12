#ifndef BST_H
#define BST_H
#include <iostream>
#include <stack>
using namespace std;

template <class T>
class Node
{
    public:
        T val;
        Node* right;
        Node* left;
        Node(T val)
        {
            this->val = val;
            right = NULL;
            left = NULL;
        }
};
template <class T>
class BSTree
{
    Node <T> *root;
    void preorder(Node<T> *root){
            if (root!=NULL){
                cout<<root->val<<" ";
                preorder(root->left);
                preorder(root->right);
            }
        }
    bool is_bst_right(Node <T> *root){
            if (root!=NULL){
                if (root->val>root->right->val){
                    return false;
                }
                else if (root->val <= root->left->val){
                    return false;
                }
                if (is_bst_right(root->left) && is_bst_right(root->right)){
                    return true;
                }
                else{return false;}
            }
            return true;
        }
        bool is_bst_left(Node <T> *root)
        {   
            if (root!=NULL){
                if (root->val<=root->left->val){
                    return false;
                }
                else if (root->val>root->right->val){
                    return false;
                }
                if (is_bst_left(root->left) && is_bst_left(root->right)){
                    return true;
                }
                else{return false;}
                

            }
            return true;
        }
        T min(Node <T> *root){
            if (root->left==NULL){
                return (root->val);
            }
            else
            {
                return (min(root->left));
            }
        }
        T max(Node <T> *root){
            if (root->right==NULL){
                return (root->val);
            }
            else{
                return (max(root->right));
            }
        }
        void inorder(Node<T> *root){
            if (root==NULL){
                return;
            }
            inorder(root->left);
            cout<<root->val<<" ";
            inorder(root->right);
        }
        void postorder(Node<T> *root){
            if (root==NULL){
                return;
            }
            postorder(root->left);
            postorder(root->right);
            cout<<root->val<<" ";
        }
        int tree_height(Node<T> *root){
            if (root==NULL){
                return 0;
            }
            int l_height = tree_height(root->left);
            int r_height = tree_height(root->right);

            if (l_height>r_height){
                return (l_height+1);
            }
            else{
                return (r_height+1);
            }
        }
        T getsecondmax(Node<T> *root){
            if (root->right==NULL){
                Node<T> *temp = root->left;
                while(temp->right!=NULL)
                temp = temp->right;

                return (temp->val);
            }
            else if(root->right->right==NULL){
                return (root->val);
            }
            else{
                Node<T> *temp = root;
                while (temp->right->right!=NULL){
                    temp = temp->right;
                }
                if (temp->right->left==NULL){
                    return (temp->val);
                }
            }
            return -1;
        }
    public:
        BSTree(){
            root = NULL;
        }
        T callgetsecondmax(){
            return getsecondmax(root);
        }
        void input(T val){
            if (root==NULL){
                root = new Node <T> (val);
                return;
            }
            else{
                Node <T> *current = root;
                Node <T> *parent = NULL;
                while(current!=NULL){
                    if (val < current->val)
                    {
                        parent = current;
                        current = current->left;
                    }
                    else
                    {
                        parent = current;
                        current = current->right;
                    }
                }
                if (val < parent->val){
                    parent->left = new Node<T> (val);
                }
                else
                {
                    parent->right = new Node<T> (val);
                }
            }
        }
        void pre_order_iter(){
            if (root==NULL){
                return;
            }
            stack <Node <T> *> s;
            s.push(root);
            Node <T> *temp = NULL;
            while (!s.empty()){
                temp = s.top();
                s.pop();
                cout<<temp->val<<" ";
                if (temp->right!=NULL){
                    s.push(temp->right);
                }
                if (temp->left!=NULL){
                    s.push(temp->left);
                }
            }
        }
        int get_inorder_successor(Node<T> *root){
            Node <T> *current = root->left;
            while(current!=NULL){
                root = current;
                current = current->right;
            }
            return (root->val);
        }
        void delete_node(T val,Node<T> *root){
            //traversing to find node
            Node <T> *current = root;
            Node <T> *parent = NULL;
            while (current!=NULL && current->val!=val){
                if (val<current->val){
                    parent = current;
                    current = current->left;
                }
                else
                {
                    parent = current;
                    current = current->right;
                }
            }
            if (current->val==val){
                //case 1
                if(current->left==current->right)    //both are null
                {
                    if (val<parent->val){
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }
                    delete current;
                }
                else if (current->left!=NULL && current->right==NULL){
                    Node <T> *temp = current->left;
                    parent->left = temp;
                    //now we can delete current
                    delete current;
                }
                else if (current->right!=NULL && current->left==NULL){
                    Node <T> *temp = current->right;
                    parent->right = temp;
                    delete current;
                }
                else{       //both have childs
                    // getting inorder predecessor
                    // Node <T> *temp = current->left;
                    // //Node <T> *temp_parent = current;
                    // if (temp->right!=NULL){
                    //         Node<T> *predecessor = temp->right;
                    //         while(predecessor->right!=NULL){
                    //         temp = predecessor;
                    //         predecessor = predecessor->right;
                    //         }
                    //         current->val = predecessor->val;
                    //         delete_node(predecessor->val,temp);
                    // }
                    // else{
                    //     T x = temp->val;
                    //     delete_node(x,current);
                    //     current->val = x;
                    // }
                    //getting inorder successor
                    // Node<T> *temp = current->right;
                    // if (temp->left!=NULL){
                    //     Node<T> *successor = temp->left;
                    //     while(successor->left!=NULL){
                    //         temp = successor;
                    //         successor = successor->left;
                    //     }
                    //     current->val = successor->val;
                    //     delete_node(successor->val,temp);
                    // }
                    // else{
                    //     T x = temp->val;
                    //     delete_node(x,current);
                    //     current->val = x;
                    // }
                    deletionbymerging(parent,current);
                }
            }
        }
        void call_delete(T val){
            delete_node(val,root);
        }
        T get_min(){
            return min(root);
        }
        T get_max(){
            return max(root);
        }
        int get_height(){
            return tree_height(root);
        }
        Node<T>* Search(int val){
            if (root->val==val){
                return (root);
            }
            else
            {
                Node <T> *current = root;
                Node <T> *parent = NULL;
                while (current!=NULL && current->val!=val){
                    if (current->val<val){
                        parent = current;
                        current = current->left;
                    }
                    else
                    {
                        parent = current;
                        current = current->right;
                    }
                }
                if (current->val==val){
                    return (current);
                }
                else{
                    return (NULL);
                }
            }
        }
        bool is_bst(){
            if (root->val > root->right->val || root->val <= root->left->val){
                return false;
            }
            if (is_bst_left(root->left) && is_bst_right(root->right)){
                return true;
            }
            return false;
        }
        void deletionbymerging(Node<T> *parent,Node<T> *temp){
            if (parent==NULL){      //the node to delete is root
                Node<T> *left_ch = temp->left;
                Node<T> *right_ch = temp->right;
                Node<T> *current = temp->left;
                while(current->right!=NULL){
                    current = current->right;
                }
                current->right = right_ch;
                root = temp;
                delete temp;
            }
            else
            {
                Node<T> *left_ch = temp->left;
                Node<T> *right_ch = temp->right;
                if (temp->val<parent->val){
                    parent->left = left_ch;
                }
                else{
                    parent->right = left_ch;
                }
                Node<T> *current = left_ch;
                while(current->right!=NULL)
                current = current->right;
                current->right = right_ch;
                delete temp; 
            }
        }
        void postorder_iter(){
            stack<Node<T> *> s;
            //s.push(root);
            Node<T> *current = root;
            do
            {
                while(current!=NULL){
                    if (current->right){
                        s.push(current->right);
                        s.push(current);
                    }
                    
                    current = current->left;
                }
                current = s.top();
                s.pop();
                if(current->right!=NULL){
                    if (current->right==s.top()){
                        s.pop();
                        s.push(current);
                        current = current->right;
                    }
                }
                else{
                    cout<<current->val<<" ";
                    current = NULL;
                }
            } while (!s.empty());
            
        }
        int search_dfs(Node<T> *root, T &e1, T &e2){
            if (root==NULL){
                return -1;
            }
            if (root->val>e1 && root->val>e2){
                return(search_dfs(root->left,e1,e2));
            }
            if (root->val<e1 && root->val<e2){
                return (search_dfs(root->right,e1,e2));
            }
            return (root->val);
        }
        int gca(T &e1, T &e2)
        {
             if (is_present(root,e1) && is_present(root,e2)){
                return (search_dfs(root,e1,e2));
            }
            else{
                 return (-1);
            }
        }
        void inorder_iter(){
                stack<Node<T> *> s;
                Node<T> *current = root;
                //s.push(current);
                while (current!=NULL || !s.empty()){
                    while (current!=NULL){
                        s.push(current);
                        current = current->left;
                    }
                    current = s.top();
                    s.pop();
                    cout<<current->val<<" ";
                    current = current->right;
                    
                }
        }
        void preorder_traverse(){
            preorder(root);
        }
        void inorder_traverse(){
            inorder(root);
        }
        void postorder_traverse(){
            postorder(root);
        }
        bool is_present(Node<T> *root, T &val){
            if (root==NULL){
                return false;
            }
            else if(root->val==val){
                return true;
            }
            if (root->val>val){
                return(is_present(root->left,val));
            }
            else{
                return(is_present(root->right,val));
            }
            
        }
};
#endif