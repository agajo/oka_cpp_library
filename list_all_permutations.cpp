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

// 0からn-1までの中からm個選んで並べるnPmパターン全て列挙します。
set<vector<ll>> listAllPermutations(ll n, ll m)
{
    set<vector<ll>> result;
    vector<ll> v(m);
    rep(i, m) v[i] = i;
    do
    {
        result.insert(v);
    } while (std::next_permutation(v.begin(), v.end()));
    return result;
}

int main()
{
    set<vector<ll>> perms = listAllPermutations(12, 4);

    for (vector<ll> x : perms)
    {
        for (auto itr = x.begin(); itr != x.end(); ++itr)
        {
            cout << *itr << ' ';
        }
        cout << endl;
    }
}