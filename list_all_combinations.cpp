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

// 0からn-1までの中からm個選ぶnCmパターン全て列挙します。
set<set<ll>> listAllCombinations(ll n, ll m)
{
    set<set<ll>> combis;
    queue<set<ll>> que;
    rep(i, n - m + 1) que.push(set<ll>{i});
    while (!que.empty())
    {
        set<ll> tempSet = que.front();
        que.pop();
        if (tempSet.size() < m)
        {
            ll last = *(--tempSet.end());
            ll stillNeed = m - tempSet.size();
            ll possibleMax = n - stillNeed;
            for (ll i = last; i < possibleMax; ++i)
            {
                set<ll> tempSet2 = tempSet;
                tempSet2.insert(i + 1);
                que.push(tempSet2);
            }
        }
        else
        {
            combis.insert(tempSet);
        }
    }
    return combis;
}

int main()
{
    set<set<ll>> combis = listAllCombinations(5, 3);

    for (set<ll> combi : combis)
    {
        for (auto itr = combi.begin(); itr != combi.end(); ++itr)
        {
            cout << *itr << ' ';
        }
        cout << endl;
    }
}