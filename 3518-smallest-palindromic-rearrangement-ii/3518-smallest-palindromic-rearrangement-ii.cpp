class Solution {
public:
    long long nCr(int n, int r, int k) {
        long long ans = 1;
        r = min(r, n - r);

        for (int i = 1; i <= r; i++) {
            ans *= (n - i + 1);
            ans /= i;

            // No need to calculate further once answer exceeds k
            if (ans > k)
                return k + 1;
        }

        return ans;
    }

    long long countPermutations(vector<int>& halfFreq, int k) {
        int remainingChar = 0;

        for (int x : halfFreq)
            remainingChar += x;

        long long ways = 1;

        for (int i = 0; i < 26; i++) {
            if (halfFreq[i] == 0)
                continue;

            // Choose positions for the current character
            long long comb = nCr(remainingChar, halfFreq[i], k);

            // Multiply by the ways contributed by this character
            ways *= comb;

            if (ways > k)
                return k + 1;

            // These positions are now occupied
            remainingChar -= halfFreq[i];
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26), halfFreq(26);

        for (char ch : s)
            freq[ch - 'a']++;

        string middle = "";

        // Build frequency of the left half
        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;

            if (freq[i] & 1)
                middle = char(i + 'a');
        }

        // Check whether the k-th palindrome exists
        if (countPermutations(halfFreq, k) < k)
            return "";

        string answer = "";
        int halfLength = s.size() / 2;

        while (answer.size() < halfLength) {

            // Try every character in lexicographical order
            for (int i = 0; i < 26; i++) {

                if (halfFreq[i] == 0)
                    continue;

                // Try fixing this character
                halfFreq[i]--;

                // Count remaining permutations
                long long permutations = countPermutations(halfFreq, k);

                if (permutations >= k) {
                    answer += char(i + 'a');
                    break;
                }

                // Skip all permutations beginning with this character
                k -= permutations;

                // Restore and try the next character
                halfFreq[i]++;
            }
        }

        string right = answer;
        reverse(right.begin(), right.end());

        return answer + middle + right;
    }
};