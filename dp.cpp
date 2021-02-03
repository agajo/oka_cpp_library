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

// Levenshtein distanceを例に、DPを実装しておきます。
// 正しさの確認は ABC185 E で。

// 今回は、dp[i][j]は「sをi文字消し、tを左にj文字追加した状態までのコスト」とする。
int fillDpTable(vector<vector<ll>> &dp, vector<ll> &s, vector<ll> &t)
{
    // TODO: 初期値を埋めます。
    rep(i, dp.size())
    {
        dp[i][0] = i;
    }
    rep(j, dp[0].size())
    {
        dp[0][j] = j;
    }

    // 残りをすべて埋めていきます。
    // TODO: 埋める範囲はこれでいい？
    for (ll i = 1; i < dp.size(); ++i)
    {
        for (ll j = 1; j < dp[0].size(); ++j)
        {
            // TODO: 漸化式に従って、埋めていく処理。
            // 足す場合も比べる場合も、ここは縦にキレイに並ぶように書くと良い。
            ll ans = LLONG_MAX;
            ans = min(ans, dp[i - 1][j] + 1);
            ans = min(ans, dp[i][j - 1] + 1);
            ans = min(ans, dp[i - 1][j - 1] + 1);
            if (s[i - 1] == t[j - 1])
            {
                ans = min(ans, dp[i - 1][j - 1]);
            }
            dp[i][j] = ans;
        }
    }
    return 0;
}

int main()
{
    // TODO: 入力を正しく受け取る
    ll sourceSize, targetSize;
    cin >> sourceSize >> targetSize;
    vector<ll> source(sourceSize);
    vector<ll> target(targetSize);
    rep(i, sourceSize) cin >> source[i];
    rep(i, targetSize) cin >> target[i];

    // TODO: DP Tableの大きさを指定
    vector<vector<ll>> dp(sourceSize + 1, vector<ll>(targetSize + 1, 0));

    // TODO: DP表を埋めます。引数合わせて。
    fillDpTable(dp, source, target);

    // TODO: 出力はこれでいい？
    cout << dp[sourceSize][targetSize] << endl;
    return 0;
}