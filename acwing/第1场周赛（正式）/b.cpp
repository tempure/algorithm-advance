#include <bits/stdc++.h>
using namespace std;

// Function to check operation can be
// perform or not
bool possible(int arr[], int N, int mid, int K) {
    int add = 0;
    for (int i = N / 2 - (N + 1) % 2;
            i < N; ++i) {
        if (mid - arr[i] > 0) {
            // Number of operation to
            // perform s.t. mid is median
            add += (mid - arr[i]);

            if (add > K)
                return false;
        }
    }

    // If mid is median of the array
    if (add <= K)
        return true;
    else
        return false;
}

// Function to find max median
// of the array
int findMaxMedian(int arr[], int N, int K) {
    // Lowest possible median
    int low = 1;
    int mx = 0;

    for (int i = 0; i < N; ++i) {
        mx = max(mx, arr[i]);
    }

    // Highest possible median
    long long int high = K + mx;

    while (low <= high) {

        int mid = (high + low) / 2;

        // Checking for mid is possible
        // for the median of array after
        // doing at most k operation
        if (possible(arr, N, mid, K)) {
            low = mid + 1;
        }

        else {
            high = mid - 1;
        }
    }

    if (N % 2 == 0) {
        if (low - 1 < arr[N / 2]) {
            return (arr[N / 2] + low - 1) / 2;
        }
    }

    // Return the max possible ans
    return low - 1;
}

const int N = 2e5 + 10;
int arr[N];

int main() {
    int n, K;
    cin >> n >> K;
    for (int i =  0; i < n; i++) cin >> arr[i];


    sort(arr, arr + n);

    cout << findMaxMedian(arr, n, K) << endl;

    return 0;
}