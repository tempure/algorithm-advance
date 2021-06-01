// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.


//本质就是一个 stable sort， 可以用 trick方法
//正解是二分

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> v;
        for (int i = 1; i <= N; i++) v.push_back(i);
        stable_sort(v.begin(), v.end(), compare);
        return v;
    }
};