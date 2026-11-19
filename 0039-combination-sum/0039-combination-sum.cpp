class Solution {
public:
    set<vector<int>> s;
    void  getallcombination(vector<int>& arr,int target,int index,vector<vector<int>>& ans,vector<int>& combin)
    {
        if(index==arr.size() || target<0)  // base case condition
        {
            return;
        }
        // base case
        if(target==0)
        {
           if(s.find(combin) == s.end())
           {
               ans.push_back(combin);
               s.insert(combin);
           }
            return;
        }
         combin.push_back(arr[index]);
        // singel choice
        getallcombination(arr,target-arr[index],index+1,ans,combin);
        // multiple choice
           getallcombination(arr,target-arr[index],index,ans,combin);

           combin.pop_back(); //backtreck
           //exclusin
              getallcombination(arr,target,index+1,ans,combin);
    }
    vector<vector<int>> combinationSum(vector<int>& arr, int target) {
        vector<vector<int>> ans;
        vector<int> combin;
        int index =0;
        getallcombination(arr,target,index,ans,combin);
  return ans;  }
};