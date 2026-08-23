class Solution {
public:
    bool sumGame(string num) {
        int n = num.size() / 2;

        vector<int> nums;

        for (char ch : num) {
            if (ch == '?') {
                nums.push_back(9);
            } else {
                nums.push_back(2 * (ch - '0'));
            }
        }

        int left = 0;
        int right = 0;

        for (int i = 0; i < n; i++) {
            left += nums[i];
        }

        for (int i = n; i < nums.size(); i++) {
            right += nums[i];
        }

        return left != right;
    }
};