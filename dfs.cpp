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

// ABC139 E League に提出してACするコードです。
// 深さ優先探索で、各頂点からスタートした場合の最長パスの長さを格納します。
// 閉路を見つけると-1を返します。
// 頂点が(i,j)と二変数で、いろいろを二次元vectorで管理してるので冗長。

// 完了と訪問済みを分けて管理するのがポイント。
// 「未完了だが訪問済み」の場所に再訪問した場合、閉路がある。
ll dfs(ll i,
       ll j,
       vector<vector<vector<pair<ll, ll>>>> &targets,
       vector<vector<bool>> &done,
       vector<vector<bool>> &visited,
       vector<vector<ll>> &scores)
{
    if (done[i][j])
    {
        return scores[i][j];
    }
    else if (visited[i][j])
    {
        done[i][j] = true;
        scores[i][j] = -1;
        return -1;
    }
    else
    {
        visited[i][j] = true;
        if (targets[i][j].empty())
        {
            // TODO: 端まで到達していたときのscore
            scores[i][j] = 1;
            done[i][j] = true;
            return 1;
        }
        else
        {
            ll result = 0;
            for (pair<ll, ll> t : targets[i][j])
            {
                ll tempI = t.first;
                ll tempJ = t.second;
                ll d = dfs(tempI, tempJ, targets, done, visited, scores);
                if (d == -1)
                {
                    scores[i][j] = -1;
                    done[i][j] = true;
                    return -1;
                }
                // TODO: 結果を受けて、scoreをどう更新するか
                result = max(result, d + 1);
            }
            scores[i][j] = result;
            done[i][j] = true;
            return result;
        }
    }
}

int main()
{
    // TODO: 入力とか
    const ll n = *istream_iterator<ll>(cin);
    vector<vector<ll>> a(n, vector<ll>(n - 1));
    rep(i, n)
    {
        rep(j, n - 1)
        {
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    vector<vector<vector<pair<ll, ll>>>> targets(n, vector<vector<pair<ll, ll>>>(n));
    rep(i, n)
    {
        rep(j, n - 2)
        {
            ll me = i;
            ll youFrom = a[i][j];
            ll youTo = a[i][j + 1];

            targets[min(me, youFrom)][max(me, youFrom)].push_back({min(me, youTo), max(me, youTo)});
        }
    }

    vector<vector<bool>> done(n, vector<bool>(n));
    vector<vector<bool>> visited(n, vector<bool>(n));
    vector<vector<ll>> depthFrom(n, vector<ll>(n));
    ll result = -1;
    for (ll i = 0; i < n - 1; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            // 一回でも-1が返ったら-1を表示して終了。
            ll d = dfs(i, j, targets, done, visited, depthFrom);
            if (d == -1)
            {
                cout << -1 << endl;
                return 0;
            }
            result = max(result, d);
        }
    }
    cout << result << endl;

    return 0;
}