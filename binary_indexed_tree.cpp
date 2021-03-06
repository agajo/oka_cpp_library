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

// BIT
// Binary Indexed Tree
// Fenwick Tree
// 更新と出力の両方が頻繁にあり、普通にやっても累積和でやってもだめな場合の折衷案として使えます。

// Inverse Semigroup で使えますが、普通は群でしょう。
// 可逆でなく、単なるモノイドの場合はセグメントツリーを使うこと。

// 0番は空けて、1-indexedです。

// 3 1 4 1 5 9 2 6 5 3 5を1回更新して1回区間和を出す例題になってます。

// 更新メソッド
// incrementは増分。新しい値そのものではないので注意！
int updateTree(vector<ll> &tree, int index, ll increment)
{
    while (index < tree.size())
    {
        // TODO: 群の演算。問題によって違う。
        tree[index] = tree[index] + increment;
        // 1110 = 1110 + 0010 → 10000 みたいな。一番下位の1を足す。
        index += (index & (-index));
    }
    return 0;
}

// 累積和取得メソッド。区間和の取得はこれの差で。
ll getSum(vector<ll> &tree, int index)
{
    ll result = 0;
    while (index > 0)
    {
        // TODO: 群の演算。問題によって違う。
        result = result + tree[index];
        index -= (index & (-index));
    }
    return result;
}

int main()
{
    // TODO: 入力を受け取る。
    ll n = 11;
    vector<ll> a{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    // 構築。
    vector<ll> tree(n + 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        updateTree(tree, i, a[i - 1]);
    }

    // TODO: クエリの処理
    updateTree(tree, 7, 100);
    ll result = getSum(tree, 9) - getSum(tree, 4);
    cout << result << endl;          // 127
    cout << getSum(tree, 0) << endl; // 0

    return 0;
}