class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n=nums.size();
        
        unordered_set<int> l1, l2;
        unordered_set<int> st;

        for(int i=0; i<n; i++){

            //Check if this element has been calculated before as well
            if(l1.contains(nums[i])) continue;
            l1.insert(nums[i]);

            for(int j=i; j<n; j++){
                int val=nums[i] xor nums[j];

                //Check if we have seen a combination with this xor before
                if(l2.contains(val)) continue;
                l2.insert(val);

                //Add the unique elements that we find
                for(int k=j; k<n; k++){
                    st.insert(nums[i] xor nums[j] xor nums[k]);
                }
            }
        }

        return st.size();
    }
};