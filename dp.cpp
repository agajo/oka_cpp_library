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

// Levenshtein distanceを例に、メモ化再帰を実装しておきます。
// 引数のsとtが余計な感じがするので、例として不適かも？

// 漸化式。doneとdpは外から受け取ります。
// 今回は、f(i,j)は「sをi文字消し、tを左にj文字追加した状態までのコスト」とする。
ll f(string s, string t, ll i, ll j, vector<vector<bool>> &done, vector<vector<ll>> &dp)
{
    // 最重要！計算済みだったら即それを返す。
    if (done[i][j])
        return dp[i][j];
    done[i][j] = true;
    // 定義されてる値たち。
    if (i == 0 && j == 0)
    {
        dp[i][j] = 0;
        return 0;
    }
    else if (i == 0)
    {
        dp[i][j] = j;
        return j;
    }
    else if (j == 0)
    {
        dp[i][j] = i;
        return i;
    }
    // 漸化式。
    else
    {
        ll ans = LLONG_MAX;
        ans = min(ans, f(s, t, i - 1, j, done, dp) + 1);
        ans = min(ans, f(s, t, i, j - 1, done, dp) + 1);
        ans = min(ans, f(s, t, i - 1, j - 1, done, dp) + 1);
        if (s[i - 1] == t[j - 1])
        {
            ans = min(ans, f(s, t, i - 1, j - 1, done, dp));
        }
        dp[i][j] = ans;
        return ans;
    }
}

int main()
{
    string s = "kittenjlf;aksjdf;lkajwepoifma;lskdjfawefmvpkams;ldkfghqpowmnvdpoasdjkngpqoiwnrg@aksndfpjgqnwpoegjdnqpewodfnapjwenf;vklsdpoqwjnregpcqpijewbragdqwer";
    string t = "sittingas;dvkmapwiemf;laksdjfoqk2mef@oismdflknvq@o3irgnmlaksdfngopqiwenrmgpjfnqefgq3rvq;oim3fpovkmapi943nmfeopfnga973n4giufn0w9jgnq3p9rdfunqgp3rfnjaiepjfghpq89uw3nrjgpjiqw3gr";

    ll n = s.size();
    ll m = t.size();

    // 計算済みかどうかを記録する配列。下のメモ用配列で兼ねても良い。
    vector<vector<bool>> done(n + 1, vector<bool>(m + 1, false));

    // メモ用配列
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, false));

    // 出力
    cout << f(s, t, n, m, done, dp) << endl;
    return 0;
}