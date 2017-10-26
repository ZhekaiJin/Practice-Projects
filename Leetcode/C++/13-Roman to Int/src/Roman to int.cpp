#include<unordered_map>
#include<string>
#include<iostream>
using namespace std;
class Solution {
public:
    int romanToInt(string s) {
        std::unordered_map<char, int> u = {
        {'I',1},
        {'V',5}, 
        {'X',10},
        {'L',50},
        {'C',100},
        {'D',500},
        {'M',1000},
        };
        int i=0,P=(u.find(s[s.size()-1]))->second;
        int T=P;
        for (i=s.size()-2;i>=0;i--){
            int a=u.find(s[i])->second;
            if(a>=P){
                 T+=a;
            }else{
                T-=a;
            }
            P=a;
        }
        return T;
    }
};
//I=1
//V=5
//X=10
//L=50
//C=100
//D=500
//M=1000
//test case 
int main(){
    Solution* test= new Solution;
    cout<<(test->romanToInt("DCXXI"))<<endl;
}
