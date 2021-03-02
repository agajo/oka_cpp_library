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
// 正負の制限はなし。どれが正でも負でも0でもOK。
// targetがgcd(m,n)の倍数じゃない場合、(LLONG_MAX, LLONG_MAX)を返します
// target=gcd(m,n)の解だけ出して使い回せる時に、この関数をtargetを変えながら何度も呼ばないように注意。
pair<ll, ll> bezout(ll m, ll n, ll target)
{
    if (target == 0)
        return {0, 0};
    if (m == 0 && n == 0)
        return {LLONG_MAX, LLONG_MAX};
    if (m == 0)
    {
        if (target % n == 0)
            return {0, target / n};
        else
            return {LLONG_MAX, LLONG_MAX};
    }
    if (n == 0)
    {
        if (target % m == 0)
            return {target / m, 0};
        else
            return {LLONG_MAX, LLONG_MAX};
    }
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

// m1で割ってr1余り、m2で割ってr2余るような非負整数(lcm(m1,m2)未満)を返します
// m1, m2は正。0<=r1<m1, 0<=r2<m2 が前提のコード。それ以外の時は未調査。
// 存在しない場合は-1を返します。
ll chineseRemainder(ll r1, ll r2, ll m1, ll m2)
{
    ll m = lcm(m1, m2);
    // n = m1q1+r1 = m2q2+r2 なので
    // q1m1-q2m2=r2-r1 なるBezoutを解く。
    pair<ll, ll> p = bezout(m1, -m2, r2 - r1);
    if (p.first == LLONG_MAX)
        return -1;
    ll n;
    ll q1 = p.first;
    ll q2 = p.second;
    // bezout()が返したのは最小とは限らないので、
    // m2' = m2/gcd ずつq1を減らしていって、減らしきった残りで置き換える
    ll m2dash = m2 / gcd(m1, m2);
    q1 = (q1 % m2dash + m2dash) % m2dash;
    n = m1 * q1 + r1;

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
    // 268537208999999999が返ればOK
    ll ans4 = chineseRemainder(1000000073, 999999999, 2000000998, 1000000000);
    cout << ans4 << endl;

    return 0;
}