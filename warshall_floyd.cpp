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

// ワーシャルフロイド法
// グラフの、全ペアについての最短距離を求めて、正方形配列に格納します。
// {cost, target}というペアのvectorのvectorを受け取ります。
vector<vector<ll>> warshallFloyd(vector<vector<pair<ll, ll>>> &targets)
{
    ll n = targets.size();
    vector<vector<ll>> dp(n, vector<ll>(n, LLONG_MAX));
    // 初期化
    for (ll i = 0; i < n; i++)
    {
        dp[i][i] = 0;
        for (pair<ll, ll> costTarget : targets[i])
        {
            ll cost = costTarget.first;
            ll j = costTarget.second;
            dp[i][j] = cost;
        }
    }
    // Warshall-Floyd
    for (ll k = 0; k < n; ++k)
    {
        for (ll i = 0; i < n; ++i)
        {
            for (ll j = 0; j < n; ++j)
            {
                // overflow対策 dp[i][j]が負の数だとまずい。
                if (dp[i][k] < dp[i][j] - dp[k][j])
                    dp[i][j] = dp[i][k] + dp[k][j];
            }
        }
    }
    return dp;
}

int main()
{
    vector<vector<pair<ll, ll>>> targets{
        {{100, 1}, {1, 2}},
        {{30, 2}},
        {{2, 0}}};
    vector<vector<ll>> result = warshallFloyd(targets);
    for (vector<ll> x : result)
    {
        for (ll y : x)
        {
            cout << y << ' ';
        }
        cout << endl;
    }
    return 0;
}