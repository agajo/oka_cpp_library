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

// https://ja.wikipedia.org/wiki/%E3%83%A6%E3%83%BC%E3%82%AF%E3%83%AA%E3%83%83%E3%83%89%E3%81%AE%E4%BA%92%E9%99%A4%E6%B3%95#%E6%8B%A1%E5%BC%B5%E3%81%95%E3%82%8C%E3%81%9F%E4%BA%92%E9%99%A4%E6%B3%95
// ↑にある逆行列の方法でやってます。

// mx+ny=target の解(x,y)を一つだけ返します。後はなんとかしてください。
// targetがgcd(m,n)の倍数じゃない場合、(LLONG_MAX, LLONG_MAX)を返します
pair<ll, ll> bezout(ll m, ll n, ll target)
{
    ll a = m;
    ll b = n;
    ll x = 1;
    ll y = 0;
    ll u = 0;
    ll v = 1;
    while (b != 0)
    {
        ll r = (a % abs(b) + abs(b)) % abs(b);
        ll k = (a - r) / b;
        a = r;
        swap(a, b);
        ll tempX = u;
        ll tempY = v;
        ll tempU = x - k * u;
        ll tempV = y - k * v;
        x = tempX;
        y = tempY;
        u = tempU;
        v = tempV;
    }
    ll g = m * x + n * y; // これがgcd(m,n)
    if (target % g != 0)
    {
        return pair<ll, ll>{LLONG_MAX, LLONG_MAX};
    }
    ll ratio = target / g;
    return pair<ll, ll>{x * ratio, y * ratio};
}

// 大きな数でうまく動かないので非推奨！！！！
// m1で割ってr1余り、m2で割ってr2余るような非負整数(lcm(m1,m2)未満)を返します
// 存在しない場合は-1を返します。
// 大きな数でうまく動かないので非推奨！！！！
ll chineseRemainder(ll r1, ll r2, ll m1, ll m2)
{
    ll m = lcm(m1, m2);
    // n = m1q1+r1 = m2q2+r2 なので
    // q1m1-q2m2=r2-r1 なるBezoutを解く。
    pair<ll, ll> p = bezout(m1, m2, r2 - r1);
    if (p.first == LLONG_MAX)
        return -1;
    ll n = m1 * p.first + r1;
    n = (n % m + m) % m;
    return n;
}

int main()
{
    // 14x - 52y = 4 の解を返す
    pair<ll, ll> ans0 = bezout(14, -52, 4);
    cout << ans0.first << ' ' << ans0.second << endl;
    // 14x - 52y = 3 の解を返す(存在しない)
    pair<ll, ll> ans1 = bezout(14, -52, 3);
    cout << ans1.first << ' ' << ans1.second << endl;
    // 7,13で割って3,4余る整数(<lcm(7,13))を返します
    ll ans2 = chineseRemainder(3, 4, 7, 13);
    cout << ans2 << endl;
    // 12,15で割って4,8余る整数(<lcm(12,15))を返します(存在しない)
    ll ans3 = chineseRemainder(4, 8, 12, 15);
    cout << ans3 << endl;

    return 0;
}