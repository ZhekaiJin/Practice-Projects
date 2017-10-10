
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
Given an integer, convert it to a roman numeral.
Input is guaranteed to be within the range from 1 to 3999.
Medium
*/
class Solution {
public:
	string T="";
	string intToRoman(int num){
		this->processing(num,1000,'M',' ',' ');
		this->processing(num,100,'C','D','M');
		this->processing(num,10,'X','L','C');
		this->processing(num,1,'I','V','X');
		return this->T;}
	void processing(int &num, int level, char A,char B,char C){
	    			if(num>=level){
	    					int a =num%level;
	    					//cout<<"now a is "<<a<<endl;
	    			    		int b =(num-a)/level;
		    				//cout<<"now b is "<<b<<endl;
	    			    		if(b<4){
	    			    			for (int i=0;i<b;i++) {T+=A;}
	    			    		}else if(b==4){
	    			    			T+=A;
	    			    			T+=B;
	    			    		}else if (b==5){
	    			    			T+=B;
	    			    		}else if (b==9){
	    			    			T+=A;
	    			    			T+=C;
	    			    		}else{
	    			    			T+=B;
	    			    			for (int i=0;i<b-5;i++) {
	    			    				T+=A;
	    			    			}
	    			}
	    			    		num=a;
	    			}
	}
};
int main() {
	Solution* A= new Solution;
	cout<<A->intToRoman(6)<<endl;
	return 0;
}
