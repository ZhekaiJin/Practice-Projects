


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution {
public:
    struct ListNode {
          int val;
          ListNode *next;
          ListNode(int x) : val(x), next(NULL) {}
      };
    ListNode *a=new ListNode(5);
    ListNode *b=new ListNode(5);
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    		int carry=0;
    		ListNode *A=new ListNode(5);
    		ListNode *head=A;
    		while((l1!=NULL)||(l2!=NULL)){
                int b=carry;
                if(l1!=NULL) { b+=l1->val;	l1=l1->next;}
                if(l2!=NULL) { b+=l2->val;  l2=l2->next;}  //cant access nullptr's property solution
                if(b>=10){
                    carry=1;
                    b-=10;
                }else{
                    carry=0;
                }
			ListNode* temp= new ListNode(b);
			A->next=temp;
			A=A->next;
            if((l1==NULL)&&(l2==NULL)&&(carry==1)){
                ListNode* temp= new ListNode(1);
                A->next=temp;         
            }
            //f(l1!=nullptr&&l2==nullptr) ListNode* l2= new ListNode(0); ?? why cant work 
            //if(l2!=nullptr&&l1==nullptr) ListNode* l1= new ListNode(0); ??
    		}
    		return head->next;
    }
};
int main() {
    struct ListNode {
          int val;
          ListNode *next;
          ListNode(int x) : val(x), next(NULL) {}
      };
    Solution* B= new Solution;
    Solution::ListNode* c=B->addTwoNumbers(B->a,B->b);
    while(c!=NULL) {
            cout<<(c->val)<<"sad"<<endl;
            c=c->next;
    }
    return 0;
}
