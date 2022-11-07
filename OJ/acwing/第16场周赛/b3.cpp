#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
int arr[N];

int binarysearch(vector <int> &v, int x) {
    int low = 0, high = v.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (v[mid] <= x)
            low = mid + 1;
        else if (v[mid] > x && v[mid - 1] <= x)
            return mid;
        else if (v[mid] > x && mid == 0)
            return mid;
        else
            high = mid - 1;
    }
    return -1;
}

ll CountContiguousParts(int arr[] , int n) {
    ll count = 0;

    int prefix[n];
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++)
        prefix[i] = prefix[i - 1] + arr[i];

    int total_sum = prefix[n - 1];

    if (total_sum % 3 != 0)
        return 0;

    int suffix[n];
    suffix[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--)
        suffix[i] = suffix[i + 1] + arr[i];
    vector <int> v;
    for (int i = 0; i < n; i++)
        if (suffix[i] == total_sum / 3)
            v.push_back(i);


    for (int i = 0; i < n; i++) {
        if (prefix[i] == total_sum / 3)
        {
            int res = binarysearch(v, i + 1);

            if (res != -1)
                count += v.size() - res;
        }
    }

    return count;
}

int main() {
    int num;
    cin >> num;
    if (num < 3) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < num; i++) cin >> arr[i];
    cout << CountContiguousParts(arr, num) << endl;
    return 0;
}