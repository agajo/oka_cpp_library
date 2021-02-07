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

// 二分探索で特定の整数を見つけます。欲しい整数が一意に定まるように定義しておくこと！
// LLONG_MAXからはじめて範囲を狭めていくので、オーバーフロー注意！

// TODO: 引数は問題によって違うよ
ll bs(ll n, ll k, vector<ll> &a, vector<ll> &f)
{
    // ここから答えを二分探索
    // left < 目的の整数 <= right を常に保ったまま、範囲を狭めます。
    // ここの等号不等号を逆にしなければならないことがある！
    // その場合、出力するものをleftに変えること。

    // leftの初期値注意。
    // left = 0だと、rightが0になれないので、答えに0がありうる場合はleftの初期値は-1。
    // 答えに負の数もありうる時はleftの初期値はLLONG_MIN。
    ll left = -1;
    ll right = LLONG_MAX;

    while (left + 1 != right)
    {
        ll mid = (left + right) / 2;

        // l < 目的の整数 <= mid (ansIsInLeftRange)なのか
        // mid < 目的の整数 <= right (!ansIsInLeftRange)なのかを判定します。
        // TODO: その判定方法は問題によって違う
        ll kNeeds = 0;
        rep(i, n)
        {
            if (a[i] * f[i] > mid)
            {
                kNeeds += (a[i] * f[i] - mid + f[i] - 1) / f[i];
            }
        }
        bool ansIsInLeftRange = (kNeeds <= k);
        if (ansIsInLeftRange)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    // TODO: 等号不等号を逆にした場合は、leftを出力
    return right;
}

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

    ll ans = bs(n, k, a, f);
    cout << ans << endl;

    return 0;
}