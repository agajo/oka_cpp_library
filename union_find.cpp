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

// =========ここから下をコピペ===========

// main関数までコピペするべき！！
// find, unite の中身も改造する必要があることでしょう。

// ツリーを平均化しながら、xのrootのインデックスを返します。
ll find(vector<ll> &parents, ll x)
{
    if (parents[x] == x)
    {
        return x;
    }
    else
    {
        parents[x] = find(parents, parents[x]);
        return parents[x];
    }
}

int unite(vector<ll> &parents, vector<ll> &ranks, ll x, ll y)
{
    ll xRoot = find(parents, x);
    ll yRoot = find(parents, y);
    // rankが小さいものを大きいものにuniteします。rankが同じ時は統合後にrankを増やします。
    if (ranks[xRoot] > ranks[yRoot])
    {
        parents[yRoot] = xRoot;
    }
    else if (ranks[xRoot] < ranks[yRoot])
    {
        parents[xRoot] = yRoot;
    }
    else if (xRoot != yRoot)
    {
        parents[yRoot] = xRoot;
        ranks[xRoot]++;
    }
    return 0;
}

int main()
{
    // TODO: 問題を受け取る
    // 問題条件
    ll n = 10;
    vector<pair<ll, ll>> e = vector<pair<ll, ll>>{
        pair<ll, ll>{0, 1},
        pair<ll, ll>{5, 4},
        pair<ll, ll>{2, 1},
        pair<ll, ll>{1, 6},
        pair<ll, ll>{7, 8},
        pair<ll, ll>{8, 3}
        // {0,1,2,6}, {3,7,8}, {4,5}, {9} という4つの組に分かれるはず。
    };

    // 初期化
    vector<ll> parents;
    vector<ll> ranks;
    for (ll i = 0; i < n; ++i)
    {
        // 親は自分、rankは0
        parents.push_back(i);
        ranks.push_back(0);
    }

    // edgesに従ってuniteしていきます。
    for (ll i = 0; i < e.size(); ++i)
    {
        unite(parents, ranks, e[i].first, e[i].second);
    }

    // TODO: 出力を書く
    // 最終的にrootになってるagentの個数を数えます
    ll result = 0;
    for (ll i = 0; i < n; ++i)
    {
        if (parents[i] == i)
        {
            result++;
        }
    }
    cout << result << endl;
}