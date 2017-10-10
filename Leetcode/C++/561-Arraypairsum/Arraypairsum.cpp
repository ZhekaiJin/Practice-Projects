#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int temp=0;
        std::sort (nums.begin(), nums.begin()+nums.size());
        for(std::vector<int>::iterator it=nums.begin();it!=nums.end();){
            temp+=*it;
            it+=2;
        }
        return temp;
    }
};
int main(){
	Solution* A =new Solution;
	int arr[] = {1,5,3,4};
	vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout<<(A->arrayPairSum(vec))<<endl;
    return 0;
           
}
