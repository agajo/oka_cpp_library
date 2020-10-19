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
// 問題が起こるまでintは使用禁止2020-04-13
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

template <class InputIterator, class T>
bool contains_itr(InputIterator iterator, const T &value)
{
    if (find(iterator.begin(), iterator.end(), value) == iterator.end())
        return false;
    else
        return true;
}

template <class T>
bool contains_set(set<T> st, const T &value)
{
    if (st.find(value) == st.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <class InputIterator>
auto sum(InputIterator iterator)
{
    return accumulate(iterator.begin(), iterator.end(), 0);
}

// endは排他的(exclusive)なので注意
vector<ll> range(ll begin, ll end)
{
    vector<ll> result;
    for (ll i = begin; i < end; ++i)
    {
        result.push_back(i);
    }
    return result;
}

random_device seed_gen;
mt19937 engine(seed_gen());
// 0, 1, 2 のどれかが得られる一様分布
// uniform_int_distribution<> dist(0, 2);
// cout << dist(engine) << endl;
// みたいに、先に確率分布を宣言して、そこにengineを与えて使う。

// =========ここまでテンプレ============

// ABC180のE問題に提出してACしたコードです。
// 巡回セールスマン問題を解くものです。

int main()
{
    ll n;
    cin >> n;
    vector<ll> x(n);
    vector<ll> y(n);
    vector<ll> z(n);
    rep(i, n) cin >> x[i] >> y[i] >> z[i];

    vector<vector<ll>> dist(n, vector<ll>(n));
    rep(j, n)
    {
        rep(k, n)
        {
            // TODO: 都市jからkへの距離。問題によって違うはず。
            dist[j][k] = abs(x[j] - x[k]) + abs(y[j] - y[k]) + max(ll{0}, z[k] - z[j]);
        }
    }

    // dp[i][j] = 訪問済み都市状態がiで、最後に訪れた都市がjである状態になれる最小コスト
    vector<vector<ll>> dp(1 << n, vector<ll>(n, LLONG_MAX));
    // 都市0だけに訪れたことがある状態を作るコストを0とします。
    dp[1][0] = 0;
    // 状態列挙しながら、そこから次の都市を全列挙しながら、その場合の次の状態におけるコストを更新していきます
    for (ll i = 1; i < 1 << n; ++i)
    {
        for (ll last = 0; last < n; ++last)
        {
            // lastが行ったことない場所だったらおかしいのでcontinue
            if ((i & (1 << last)) == 0)
            {
                continue;
            }
            for (ll j = 0; j < n; ++j)
            {
                // 訪問済みの場所に行こうとしてたら意味ないのでcontinue
                if (i & 1 << j)
                    continue;
                // ここから作る次の状態がより良い場合、更新します
                if (dp[i][last] < LLONG_MAX && dp[i | 1 << j][j] > dp[i][last] + dist[last][j])
                {
                    dp[i | 1 << j][j] = dp[i][last] + dist[last][j];
                }
            }
        }
    }

    ll result = LLONG_MAX;
    rep(j, n)
    {
        // TODO: 都市0に戻るかどうかによってここの処理は変わるはず。
        if (result > dp[(1 << n) - 1][j] + dist[j][0])
        {
            result = dp[(1 << n) - 1][j] + dist[j][0];
        }
    }
    cout << result << endl;

    return 0;
}