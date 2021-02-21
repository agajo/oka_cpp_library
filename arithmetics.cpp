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

ll power(ll base, ll exponent)
{
    ll ans = 1;
    rep(i, exponent)
    {
        ans *= base;
    }
    return ans;
}

// 割り算いろいろ
// (商×序数)が元の数を超えない割り算(余り非負)
ll re(ll x, ll m)
{
    return (x % m + m) % m;
}

ll qu(ll x, ll m)
{
    return (x - re(x, m)) / m;
}

// (商×序数)が元の数を下回らない割り算(余り非正)(余りというより不足を考える)
ll re2(ll x, ll m)
{
    return (x % m - m) % m;
}

ll qu2(ll x, ll m)
{
    return (x - re2(x, m)) / m;
}

// (商×序数)が元の数にできるだけ近い割り算(最小絶対剰余)(-m/2 <= r < m/2)
ll re3(ll x, ll m)
{
    ll r = (x % m + m) % m;
    if (m - r <= r)
        r = r - m;
    return r;
}

ll qu3(ll x, ll m)
{
    return (x - re3(x, m)) / m;
}

int main()
{
    cout << power(2, 0) << endl;
    cout << power(2, 10) << endl;
    cout << power(2, 62) << endl;
    // ↓ overflow!! ↓
    // cout << power(2, 63) << endl;

    // 割り算いろいろ
    ll m = 4;
    for (ll x = -5; x <= 5; x++)
    {
        if (x != qu(x, m) * m + re(x, m))
            cout << "error with qu and re" << endl;
        if (x != qu2(x, m) * m + re2(x, m))
            cout << "error with qu2 and re2" << endl;
        if (x != qu3(x, m) * m + re3(x, m))
            cout << "error with qu3 and re3" << endl;
        cout << x << "÷" << m << "=" << qu(x, m) << "…" << re(x, m) << ' ';
        cout << x << "÷" << m << "=" << qu2(x, m) << "…" << re2(x, m) << ' ';
        cout << x << "÷" << m << "=" << qu3(x, m) << "…" << re3(x, m) << ' ';
        cout << endl;
    }

    return 0;
}