class Solution {
public:
    string smallestNumber(string num, long long t) {
        auto [primeCount, isDivisible] = getPrimeCount(t);
        if (!isDivisible) return "-1";
        
        auto factorCount = getFactorCount(primeCount);
        if (sumValues(factorCount) > (int)num.length()) 
            return construct(factorCount);
        
        auto primeCountPrefix = getPrimeCount(num);
        int firstZeroIndex = num.find('0');
        if (firstZeroIndex == string::npos) {
            firstZeroIndex = num.length();
            if (isSubset(primeCount, primeCountPrefix)) return num;
        }
        
        for (int i = (int)num.length() - 1; i >= 0; --i) {
            int d = num[i] - '0';
            // Remove the current digit's factors from primeCountPrefix
            primeCountPrefix = subtract(primeCountPrefix, kFactorCounts.at(d));
            int spaceAfterThisDigit = (int)num.length() - 1 - i;
            
            if (i > firstZeroIndex) continue;
            
            for (int biggerDigit = d + 1; biggerDigit < 10; ++biggerDigit) {
                // Compute the required factors after replacing with a larger digit
                auto factorsAfterReplacement = getFactorCount(
                    subtract(subtract(primeCount, primeCountPrefix), kFactorCounts.at(biggerDigit))
                );
                
                // Check if the replacement is possible within the available space
                if (sumValues(factorsAfterReplacement) <= spaceAfterThisDigit) {
                    // Fill extra space with '1's and construct the result
                    int fillOnes = spaceAfterThisDigit - sumValues(factorsAfterReplacement);
                    return num.substr(0, i) +                    // Keep the prefix unchanged
                           to_string(biggerDigit) +              // Replace the current digit
                           string(fillOnes, '1') +               // Fill remaining space with '1'
                           construct(factorsAfterReplacement);
                }
            }
        }
        
        // No solution of the same length exists, extend the number
        auto factorsAfterExtension = getFactorCount(primeCount);
        return string(num.length() + 1 - sumValues(factorsAfterExtension), '1') + 
               construct(factorsAfterExtension);
    }

private:
    static const unordered_map<int, unordered_map<int, int>> kFactorCounts;
    
    // Returns the prime count of t and whether t is only composed of primes 2,3,5,7
    pair<unordered_map<int, int>, bool> getPrimeCount(long long t) {
        unordered_map<int, int> count{{2, 0}, {3, 0}, {5, 0}, {7, 0}};
        for (int prime : {2, 3, 5, 7}) {
            while (t % prime == 0) {
                t /= prime;
                ++count[prime];
            }
        }
        return {count, t == 1};
    }
    
    // Returns the prime count of the digits in num
    unordered_map<int, int> getPrimeCount(const string& num) {
        unordered_map<int, int> count{{2, 0}, {3, 0}, {5, 0}, {7, 0}};
        for (char d : num) {
            for (const auto& [prime, freq] : kFactorCounts.at(d - '0')) {
                count[prime] += freq;
            }
        }
        return count;
    }
    
    unordered_map<int, int> getFactorCount(const unordered_map<int, int>& count) {
        // Maximize higher digits to minimize length: 8=2^3, 9=3^2
        int count8 = count.at(2) / 3;
        int remaining2 = count.at(2) % 3;
        int count9 = count.at(3) / 2;
        int count3 = count.at(3) % 2;
        int count4 = remaining2 / 2;
        int count2 = remaining2 % 2;
        
        int count6 = 0;
        // Prefer combining 2+3 into 6
        if (count2 == 1 && count3 == 1) {
            count2 = 0;
            count3 = 0;
            count6 = 1;
        }
        // Prefer combining 3+4 into 2+6
        if (count3 == 1 && count4 == 1) {
            count2 = 1;
            count6 = 1;
            count3 = 0;
            count4 = 0;
        }
        
        return {
            {2, count2}, {3, count3}, {4, count4}, {5, count.at(5)},
            {6, count6}, {7, count.at(7)}, {8, count8}, {9, count9}
        };
    }
    
    string construct(const unordered_map<int, int>& factors) {
        string res;
        for (int digit = 2; digit <= 9; ++digit) {
            res += string(factors.at(digit), '0' + digit);
        }
        return res;
    }
    
    bool isSubset(const unordered_map<int, int>& a, const unordered_map<int, int>& b) {
        for (const auto& [key, value] : a) {
            if (b.at(key) < value) return false;
        }
        return true;
    }
    
    unordered_map<int, int> subtract(unordered_map<int, int> a, const unordered_map<int, int>& b) {
        for (const auto& [key, value] : b) {
            a[key] = max(0, a[key] - value);
        }
        return a;
    }
    
    int sumValues(const unordered_map<int, int>& count) {
        int sum = 0;
        for (const auto& [_, v] : count) sum += v;
        return sum;
    }
};

const unordered_map<int, unordered_map<int, int>> Solution::kFactorCounts = {
    {0, {}}, {1, {}},
    {2, {{2, 1}}}, {3, {{3, 1}}}, {4, {{2, 2}}},
    {5, {{5, 1}}}, {6, {{2, 1}, {3, 1}}}, {7, {{7, 1}}},
    {8, {{2, 3}}}, {9, {{3, 2}}}
};