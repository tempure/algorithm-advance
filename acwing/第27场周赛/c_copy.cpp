// CPP program for finding the maximum number
// of trailing zeros in the product of the
// selected subset of size k.
#include <bits/stdc++.h>
using namespace std;
#define MAX5 5010
const int N = 210;
#define int long long
int a[N];
int n, k;
// int subset[N][N];

// Function to calculate maximum zeros.
int maximumZeros(int* arr, int n, int k)
{
    // Initializing each value with -1;
    int subset[k + 1][MAX5 + 5];
    memset(subset, -1, sizeof(subset));

    subset[0][0] = 0;

    for (int p = 0; p < n; p++) {
        int pw2 = 0, pw5 = 0;

        // Calculating maximal power of 2 for
        // arr[p].
        while (arr[p] % 2 == 0) {
            pw2++;
            arr[p] /= 2;
        }

        // Calculating maximal power of 5 for
        // arr[p].
        while (arr[p] % 5 == 0) {
            pw5++;
            arr[p] /= 5;
        }

        // Calculating subset[i][j] for maximum
        // amount of twos we can collect by
        // checking first i numbers and taking
        // j of them with total power of five.
        for (int i = k - 1; i >= 0; i--)
            for (int j = 0; j < MAX5; j++)

                // If subset[i][j] is not calculated.
                if (subset[i][j] != -1)
                    subset[i + 1][j + pw5] =
                        max(subset[i + 1][j + pw5],
                            subset[i][j] + pw2);
    }

    // Calculating maximal number of zeros.
    // by taking minimum of 5 or 2 and then
    // taking maximum.
    int ans = 0;
    for (int i = 0; i < MAX5; i++)
        ans = max(ans, min(i, subset[k][i]));

    return ans;
}

// Driver function
int32_t main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << maximumZeros(a, n, k) << endl;
    return 0;
}
