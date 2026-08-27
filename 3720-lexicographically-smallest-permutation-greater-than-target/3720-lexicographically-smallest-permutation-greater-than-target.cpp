class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);

        for (char ch : s) {
            cnt[ch - 'a']++;
        }

        int p = 0;

        while (p < n) {
            int c = target[p] - 'a';

            if (cnt[c] == 0) {
                break;
            }

            cnt[c]--;
            p++;
        }

        int i = p;

        while (i >= 0) {
            if (i < n) {
                int t = target[i] - 'a';
                int pick = -1;

                for (int c = t + 1; c < 26; c++) {
                    if (cnt[c] > 0) {
                        pick = c;
                        break;
                    }
                }

                if (pick >= 0) {
                    cnt[pick]--;

                    string tail = "";

                    for (int c = 0; c < 26; c++) {
                        tail += string(cnt[c], char('a' + c));
                    }

                    cnt[pick]++;

                    return target.substr(0, i)
                        + char('a' + pick)
                        + tail;
                }
            }

            i--;

            if (i >= 0) {
                cnt[target[i] - 'a']++;
            }
        }

        return "";
    }
};