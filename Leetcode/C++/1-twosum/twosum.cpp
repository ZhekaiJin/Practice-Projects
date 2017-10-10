#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
class Twosum {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int numstofind;
        unordered_map<int,int> mymap;
        for (int i=0;i<nums.size();i++){
            numstofind=target-nums[i];
            std::unordered_map<int,int>::const_iterator got = mymap.find (numstofind);
            if(got!=mymap.end()){
                int a=got->second;
                int b=i;
                int arr[] = {a,b};
                vector<int> vecOfStr(arr, arr + sizeof(arr)/sizeof(int));
                return vecOfStr;
            }else{
                int a=nums[i];
                int b=i;
                mymap.insert(std::make_pair(a,b));
            }
        }
        vector<int> vecOfInts(2);
        return vecOfInts;
    }
};


int main() {
	int arr[] = {1,5,3,4};
	vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]));
	Twosum * A=new Twosum;
	vector<int> B=A->twoSum(vec,8);
	int x=0;
	for(;x<B.size();x++)
		std::cout<<B[x]<<std::endl;
	return 0;
}

