#include <string>
#include <iostream>
#include <stack>
#include <queue> // priority_queue も入ってる
#include <set>   // 要素数は size() で取得 multisetもある
#include <map>
#include <array> // sizeはコンパイル時定数で固定
#include <vector>
#include <numeric>   // accumulate, gcd
#include <algorithm> // count_ifに必要
#include <iomanip>   // cout << setprecision(15) << x で小数の出力精度を指定
#include <tuple>
#include <utility> //pair
#include <cmath>
#include <random>

using namespace std;
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

// ABC144 E に提出してACしたものです。

int main()
{
    // TODO: 変数・入出力を正しく
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n), f(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> f[i];
    sort(a.begin(), a.end());
    sort(f.rbegin(), f.rend());

    // ここから答えを二分探索
    ll left = 0;
    ll right = LLONG_MAX;
    while (left != right)
    {
        // TODO: 答えが、thresholdAnswer以下である条件を記述
        ll thresholdAnswer = (left + right) / 2;

        ll kNeeds = 0;
        rep(i, n)
        {
            if (a[i] * f[i] > thresholdAnswer)
            {
                kNeeds += (a[i] * f[i] - thresholdAnswer + f[i] - 1) / f[i];
            }
        }
        bool isSmall = kNeeds <= k;
        if (isSmall)
        {
            right = (left + right) / 2;
        }
        else
        {
            left = (left + right) / 2 + 1;
        }
    }
    cout << left << endl;

    return 0;
}