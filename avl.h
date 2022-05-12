#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>
using namespace std;
class LLNode
{
    public:
    string destination,price,date;
    LLNode* next;
    LLNode()
    {
        next = NULL;
    }
    LLNode(string destt, string pri, string da){
        next = NULL;
        destination = destt;
        price = pri;
        date = da;
    }
    void set_data(string destt,string pri,string da){
        destination = destt;
        price = pri;
        date = da;
    }
};
class singlylinkedlist
{
    LLNode* head;
    //int size;
    public:
        singlylinkedlist()
        {
            head = NULL;
            //size = 0;
        }
        singlylinkedlist (const  singlylinkedlist &obj)
        {
            LLNode* temp = head;
            LLNode* src_temp = obj.head;
            if (obj.head==NULL)
            {
                cout<<"The linked list doesn't exist"<<endl;
            }
            else{
                temp = new LLNode;
                head = temp;
                while(src_temp->next != NULL){
                    //temp = new(nothrow) Node;
                    temp->destination = src_temp->destination;
                    temp->price = src_temp->price;
                    temp->date = src_temp->date;
                    temp->next = new LLNode;
                    temp = temp->next;
                    src_temp = src_temp->next;
                }
                temp->destination = src_temp->destination;
                temp->date = src_temp->date;
                temp->price = src_temp->price;
                temp->next = NULL;
            }
        }
        void push_back(LLNode* ll_node){
          if (head==NULL){
            head = ll_node;
            return;
          }
          if(ll_node!=NULL && head!=NULL){
            LLNode* temp = head;

            while (temp->next!=NULL)
            {
              temp = temp->next;
            }
            temp->next = ll_node;
          }
        }
        void push_back(string destt,string pric, string date)
        {
            //size++;
            LLNode* new_node = new LLNode(destt,pric,date);
            if (head==NULL)
            {
                head = new_node;
            }
            else
            {
                LLNode* temp;
                temp = head;
                while (temp->next!=NULL)
                {
                    temp=temp->next;
                }
                temp->next = new_node;
            }
        }
        void traverse(){
            LLNode *temp = head;
            if(head==NULL){
                return;
            }
            else{
              int i=1;
                while(temp!=NULL){
                    cout<<i<<" Destination is: "<<temp->destination<<"Price is: "<<temp->price<<"Date is: "<<temp->date<<endl;
                    temp = temp->next;
                    i++;
                }
            }

        }
        LLNode* get_head(){return head;}

};
class TreeNode
{
  public:
  string val;
  TreeNode* right;
  TreeNode* left;
  singlylinkedlist LL;
  TreeNode(){
    right = NULL;
    left = NULL;
  }
  TreeNode(string v){
    val = v;
    right = NULL;
    left = NULL;
  }
};
class AVLTree
{
  public:
    TreeNode* root;
    AVLTree(){root= NULL;}
    //function to get height
    int height(TreeNode* t){
      if (t==NULL){
        return 0;
      }
      int l_height = height(t->left);
      int r_height = height(t->right);
      return max(l_height,r_height)+1;
    }
    //function to get difference of heights i.e balance factor
    int difference(TreeNode* t){
      int l_height = height(t->left);
      int r_height = height(t->right);
      return (l_height - r_height);
    }
    // rotation functions
    TreeNode* rr_rotate(TreeNode* parent){
      TreeNode* t;
      t = parent->right;
      parent->right = t->left;
      t->left = parent;
      return t;
    }
    TreeNode* ll_rotate(TreeNode* parent){
      TreeNode* t;
      t = parent->left;
      parent->left = t->right;
      t->right = parent;
      return t;
    }
    TreeNode* lr_rotate(TreeNode* parent){
      TreeNode *t;
      t = parent->left;
      parent->left = rr_rotate(t);
      return ll_rotate(parent);
    }
    TreeNode* rl_rotate(TreeNode* parent){
      TreeNode* t;
      t = parent->right;
      parent->right = ll_rotate(t);
      return rr_rotate(parent);
    }
    TreeNode* balance(TreeNode* t){
      int bal_factor = difference(t);
      if (bal_factor>1){
        if (difference(t->left) > 0){
          t = ll_rotate(t);
        }
        else{
          t = lr_rotate(t);
        }
      }
      else if(bal_factor < -1){
        if (difference(t->right) > 0){
          t = rl_rotate(t);
        }
        else{
          t = rr_rotate(t);
        }
      }
      return t;
    }
    TreeNode* insert_tree(TreeNode *t,string v, LLNode* ll_node){
        if(is_present(t,v)){
          TreeNode* temp = t;
          if(temp->val==v){
            temp->LL.push_back(ll_node);
            return t;
          }
          while (temp->val!=v)
          {
            if (temp->val>v){
            temp = temp->left;
            }
            else{
              temp = temp->right;
            }
          }
          if (temp->val==v){
            temp->LL.push_back(ll_node);
          }
          return t;
      }
      return(insert(t,v,ll_node));

    }
    TreeNode * insert(TreeNode *t, string v,LLNode* ll_node){
    if (t==NULL){
      t = new TreeNode(v);
      t->LL.push_back(ll_node);
      return t;
    }
    else if(v < t->val){
      t->left = insert(t->left,v,ll_node);
      t = balance(t);
    }
    else if(v >= t->val){
      t->right = insert(t->right,v,ll_node);
      t = balance(t);
    }
    return t;
  }
  bool is_present(TreeNode* t,string v){
    if(t==NULL){
      return false;
    }
    if(t->val==v){
      return true;
    }
    if (v<t->val){
      return(is_present(t->left,v));
    }
    return(is_present(t->right,v));
  }
 LLNode* search_list(TreeNode* t,string v)
 {
   if(t==NULL){
     return NULL;
   }
   if (t->val==v){
     return (t->LL.get_head());
   }
   if (v<t->val){
      return(search_list(t->left,v));
   }
   return (search_list(t->right,v));
   
 }
 void pre_order(TreeNode* t){
   if (t==NULL){return;}
   cout<<t->val<<" ";
   t->LL.traverse();
   pre_order(t->left);
   pre_order(t->right);
 }
};
#endif