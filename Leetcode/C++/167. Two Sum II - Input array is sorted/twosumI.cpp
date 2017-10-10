#include <iostream>
#include <vector>
using namespace std;




class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> result={};
        int low=0, high = (int)numbers.size()-1;
        while (low < high){
            if (numbers[low] + numbers[high] == target){
                result.push_back(low+1);
                result.push_back(high+1);
                return result;
            }else{
                numbers[low] + numbers[high] > target ? high-- : low++;
            }
        }
        
        return result;
    }
};

int main(){
    vector <int> A={1,2,4,6};
    Solution* Test= new Solution;
    vector <int> result= Test->twoSum(A,10);
    for(int i=0;i<result.size();i++) {
        cout<<"resulting index is:"<<result[i]<<endl;
    }
    return 0;
    }
