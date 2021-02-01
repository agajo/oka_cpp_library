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
    ll numberOfCities;
    cin >> numberOfCities;
    vector<ll> x(numberOfCities);
    vector<ll> y(numberOfCities);
    vector<ll> z(numberOfCities);
    rep(i, numberOfCities) cin >> x[i] >> y[i] >> z[i];

    // distance
    vector<vector<ll>> dist(numberOfCities, vector<ll>(numberOfCities));
    rep(cityFrom, numberOfCities)
    {
        rep(cityTo, numberOfCities)
        {
            // TODO: 都市cityFromからcityToへの距離。問題によって違うはず。
            // 都市は0〜(numberOfCities-1) になっていること。
            dist[cityFrom][cityTo] = abs(x[cityFrom] - x[cityTo]) + abs(y[cityFrom] - y[cityTo]) + max(ll{0}, z[cityTo] - z[cityFrom]);
        }
    }

    // dp[state][last] = 訪問済み都市状態がstateで、最後に訪れた都市がlastである状態になれる最小コスト
    vector<vector<ll>> dp(1 << numberOfCities, vector<ll>(numberOfCities, LLONG_MAX));
    // 都市一つも訪れてない状態を作るコストは0にします。多分意味ないけど。
    rep(last, numberOfCities) dp[0][last] = 0;

    // TODO: 「最初の都市としてコスト0でいける都市1つだけに訪れたことがある状態」を作るコストを0とします。
    // スタートが決まっていない場合
    // rep(last, numberOfCities)
    // {
    //     dp[1 << last][last] = 0;
    // }
    // 都市0からスタートする場合
    dp[1 << 0][0] = 0;

    // 状態列挙しながら、そこから次の都市を全列挙しながら、その場合の次の状態におけるコストを更新していきます
    for (ll state = 1; state < 1 << numberOfCities; ++state)
    {
        for (ll last = 0; last < numberOfCities; ++last)
        {
            // lastが行ったことない場所だったらおかしいのでcontinue
            if ((state & (1 << last)) == 0)
            {
                continue;
            }
            for (ll nextCity = 0; nextCity < numberOfCities; ++nextCity)
            {
                // 訪問済みの場所に行こうとしてたら意味ないのでcontinue
                if (state & 1 << nextCity)
                    continue;
                // ここから作る次の状態がより良い場合、更新します
                if (dp[state][last] < LLONG_MAX && dp[state | 1 << nextCity][nextCity] > dp[state][last] + dist[last][nextCity])
                {
                    dp[state | 1 << nextCity][nextCity] = dp[state][last] + dist[last][nextCity];
                }
            }
        }
    }

    ll result = LLONG_MAX;
    rep(last, numberOfCities)
    {
        // TODO: 都市0に戻らない場合、+dist[last][0]は不要
        // スタートがどこでもよくて一周する場合は、0からスタートして0に戻ることにすればOK
        if (result > dp[(1 << numberOfCities) - 1][last] + dist[last][0])
        {
            result = dp[(1 << numberOfCities) - 1][last] + dist[last][0];
        }
    }
    cout << result << endl;

    return 0;
}