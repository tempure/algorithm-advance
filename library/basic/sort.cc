//快排
const int N = 100010;
int a[N];
void quick_sort(int a[], int l, int r) {
    if (l >= r) return;
    int i  = l - 1, j = r + 1, x = a[l + r >> 1];
    while (i < j) {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    quick_sort(a, l, j); quick_sort(a, j + 1, r);
}
//归并排序
void merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];
    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];
    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
}
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    quick_sort(a, 0, n - 1);  //模板的下标右边可以取到
    // merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << endl;
    return 0;
}

/*
    例题：归并排序求逆序对数量(后补充树状数组)
    给定一个长度为n的整数数列，请你计算数列中的逆序对的数量。
    第一行包含整数n，表示数列的长度。
    第二行包含 n 个整数，表示整个数列。
*/
typedef long long ll;
const int N = 100010;
int tmp[N]; ll res = 0;
int a[N];
ll merge_sort(int l, int r) {
    if (l >= r) return 0;
    int mid = l + ((r - l) >> 1);
    res = merge_sort(l, mid) + merge_sort(mid + 1, r);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            res += mid - i + 1;
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];
    return res;
}
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    cout << merge_sort(0, n - 1) << endl;
    return 0;
}