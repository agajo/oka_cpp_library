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

using namespace std;
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;
#define rep(i, n) for (int i = 0; i < (n); ++i)

// 拡張ユークリッド互除法
// aとmが互いに素でない場合、おかしな値が返ります！
ll modularInverse(ll a, ll m)
{
    // このチェックでユークリッドの互除法実行することになるので、外します。
    // if (gcd(a, m) != 1)
    // {
    //     cout << "!!!!!!!!!gcd(a,m) must be 1! a==" << a << " m==" << m << endl;
    //     return 0;
    // }
    ll b = m, u = 1, v = 0;
    while (b)
    {
        ll t = a / b;
        a -= t * b;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    u %= m;
    if (u < 0)
        u += m;
    return u;
}

// 二乗しながら、必要な奴だけ足してます。必要なやつの判定は2進数使ってうまくやる。
ll modularPower(ll a, ll n, ll modulus)
{
    ll result = 1;
    while (n > 0)
    {
        if (n & 1)
            result = result * a % modulus;
        a = a * a % modulus;
        n >>= 1;
    }
    return result;
}

// ここから二項係数(nCk)の話

// TODO: maxNとMODを変更
const int maxN = 510000;
const int MOD = 1000000007;

// 階乗、その逆数、iの逆数のテーブルを生成する
ll fac[maxN], finv[maxN], inv[maxN];

// テーブルを作る前処理
// 計算量 O(n)
void initModularTables()
{
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < maxN; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
        // 何でこれで順にinv[i]が出るんや2020-06-30
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数計算 nCk
// 先にinitModularTables()を呼んでおくこと！
ll modularCombination(ll n, ll k)
{
    if (fac[5] != 120)
    {
        cout << "call initModularTables() first!!!!!!!!" << endl;
        return 0;
    }
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

// 順列計算 nPk
// 先にinitModularTables()を呼んでおくこと！
ll modularPermutation(ll n, ll k)
{
    if (fac[5] != 120)
    {
        cout << "call initModularTables() first!!!!!!!!" << endl;
        return 0;
    }
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * finv[n - k] % MOD;
}

// 離散対数、離散平方根についてはまた必要になったら用意する。2020-06-30

int main()
{
    cout << modularInverse(3, 13) << endl;
    cout << modularPower(3, 4, 10) << endl;
    initModularTables();
    cout << modularCombination(5, 3) << endl;
    cout << modularCombination(100, 50) << endl;
    cout << modularCombination(3, 0) << endl;
    cout << modularPermutation(5, 3) << endl;
    cout << modularPermutation(100, 50) << endl;
    cout << modularPermutation(3, 0) << endl;
}