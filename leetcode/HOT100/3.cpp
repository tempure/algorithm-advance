class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<char, int> cnt;
        cnt.clear();
        int res = 0;
        for (int i = 0, j = 0; j < n; j++) {
            cnt[s[j]]++;
            while (cnt[s[j]] > 1) {
                cnt[s[i]]--;
                i++;
            }
            res = max(res, j - i + 1);
        }
        return res;
    }
};