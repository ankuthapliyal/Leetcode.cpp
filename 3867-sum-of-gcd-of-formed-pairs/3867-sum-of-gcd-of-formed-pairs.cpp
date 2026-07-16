class Solution {
public:
    long long gcdSum(vector<int>& nums) {
         int n = nums.size();
        vector<int> prefixGcd(n);
        int l = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] > l) {
                l = nums[i];
            }

            prefixGcd[i] = gcd(nums[i], l);
        }

        sort(prefixGcd.begin(), prefixGcd.end());

        int left = 0;
        int r = n - 1;
        long long sum = 0;

        while (left < r) {
            sum += gcd(prefixGcd[left], prefixGcd[r]);
            left++;
            r--;
        }

        return sum;
    }
};