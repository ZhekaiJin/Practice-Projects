#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution {
public:
    bool checkPerfectNumber(int num) {
        bool isPerfect=0;
        int sum=1;
        for(int i=2;i<sqrt(num);i++){
            int b=num%i;
            if (b==0){sum+=(i+num/i);}
        }      //dont need to conside n=[2^(k−1)](2^k−1)
        if(sum==num&&num!=1){ isPerfect=1;}
        return isPerfect;
    }
};
int main(){
    Solution* test=new Solution;
    if(test->checkPerfectNumber(28)){cout<<"perfect"<<endl;}else{cout<<"Not perfect"<<endl;}
}
