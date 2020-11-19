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

// =========ここから下をコピペ===========

// agentsは、(親のインデックス, 自分をrootとするツリーのランク)というペアのvector
// ツリーを平均化しながら、xのrootのインデックスを返します。
ll find(vector<pair<ll, ll>> &agents, ll x)
{
    if (agents[x].first == x)
    {
        return x;
    }
    else
    {
        agents[x].first = find(agents, agents[x].first);
        return agents[x].first;
    }
}

// agentsは、(親のインデックス, 自分をrootとするツリーのランク)というペアのvector
int unite(vector<pair<ll, ll>> &agents, ll x, ll y)
{
    ll xRoot = find(agents, x);
    ll yRoot = find(agents, y);
    // rankが小さいものを大きいものにuniteします。rankが同じ時は統合後にrankを増やします。
    if (agents[xRoot].second > agents[yRoot].second)
    {
        agents[yRoot].first = xRoot;
    }
    else if (agents[xRoot].second < agents[yRoot].second)
    {
        agents[xRoot].first = yRoot;
    }
    else if (xRoot != yRoot)
    {
        agents[yRoot].first = xRoot;
        agents[xRoot].second++;
    }
    return 0;
}

int main()
{
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
    vector<pair<ll, ll>> agents;
    for (ll i = 0; i < n; ++i)
    {
        // 親は自分、rankは0
        agents.push_back(pair<ll, ll>{i, 0});
    }

    // edgesに従ってuniteしていきます。
    for (ll i = 0; i < e.size(); ++i)
    {
        unite(agents, e[i].first, e[i].second);
    }

    // 最終的にrootになってるagentの個数を数えます
    ll result = 0;
    for (ll i = 0; i < n; ++i)
    {
        if (agents[i].first == i)
        {
            result++;
        }
    }
    cout << result << endl;
}