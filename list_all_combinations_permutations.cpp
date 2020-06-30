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
// 返り値は昇順ソート済みになる
vector<vector<ll>> listAllCombinations(ll n, ll m)
{
    vector<vector<ll>> combis;
    queue<vector<ll>> que;
    rep(i, n - m + 1) que.push(vector<ll>{i});
    while (!que.empty())
    {
        vector<ll> tempSet = que.front();
        que.pop();
        if (tempSet.size() < m)
        {
            ll last = *(--tempSet.end());
            ll stillNeed = m - tempSet.size();
            ll possibleMax = n - stillNeed;
            for (ll i = last; i < possibleMax; ++i)
            {
                vector<ll> tempSet2 = tempSet;
                tempSet2.push_back(i + 1);
                que.push(tempSet2);
            }
        }
        else
        {
            combis.push_back(tempSet);
        }
    }
    return combis;
}

// 0からn-1までの中からm個選んで並べるnPmパターン全て列挙します。
// 出力は辞書順ではないので注意！組み合わせ選んでからnext_permutationしてるため。
// listAllCombinationsを使ってるのでそれもコピペしてね。
vector<vector<ll>> listAllPermutations(ll n, ll m)
{
    vector<vector<ll>> combis = listAllCombinations(n, m);
    vector<vector<ll>> result;
    for (vector<ll> combi : combis)
    {
        do
        {
            result.push_back(combi);
        } while (next_permutation(combi.begin(), combi.end()));
    }
    return result;
}

int main()
{
    vector<vector<ll>> combis = listAllCombinations(5, 3);
    for (vector<ll> combi : combis)
    {
        for (auto itr = combi.begin(); itr != combi.end(); ++itr)
            cout << *itr << ' ';
        cout << endl;
    }
    cout << "===============================" << endl;
    vector<vector<ll>> perms = listAllPermutations(4, 3);
    for (vector<ll> perm : perms)
    {
        for (auto itr = perm.begin(); itr != perm.end(); ++itr)
            cout << *itr << ' ';
        cout << endl;
    }
}