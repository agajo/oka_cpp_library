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

// セグメントツリー。セグ木。
// 更新と出力の両方が頻繁にあり、普通にやっても累積和でやってもだめな場合の折衷案として使えます。
// モノイドで使えます。
// 可逆な場合(つまり群の場合)はBinary Indexed Treeの方がいいかも？

// 0番は空けて、1-indexedです。

// このコードは、ABC185のF問題に提出してACしたものです。

ll monoidSum(ll left, ll right)
{
    // TODO: 問題によってここは変わるはずです。和なのかminなのかxorなのか…。
    // 結合法則が成り立つ演算。
    return left ^ right;
}
// TODO: monoidSumの単位元を入れます。
ll identityElement = 0;

// targetIndexは0始まりです
int updateTree(vector<ll> &tree, ll tagetIndex, ll inputValue)
{
    // treeSizeよりもtree.size()のほうが1大きいので注意
    ll leafBegin = tree.size() / 2;
    ll targetIndexInTree = leafBegin + tagetIndex;
    // TODO: ここの更新内容は問題によって違うはず。
    tree[targetIndexInTree] = monoidSum(tree[targetIndexInTree], inputValue);
    ll t = targetIndexInTree / 2;
    while (t >= 1)
    {
        tree[t] = monoidSum(tree[t * 2], tree[t * 2 + 1]);
        t = t / 2;
    }
    return 0;
}

// left included. right included.
ll getRangeResult(vector<ll> &tree, vector<pair<ll, ll>> &scopeTree, ll targetIndexInTree, ll left, ll right)
{
    if (left > right)
        return identityElement;
    // treeSizeよりもtree.size()のほうが1大きいので注意
    ll leafBegin = tree.size() / 2;
    if (scopeTree[targetIndexInTree].first == left && right == scopeTree[targetIndexInTree].second)
    {
        return tree[targetIndexInTree];
    }
    else
    {
        return monoidSum(getRangeResult(tree, scopeTree, targetIndexInTree * 2, max(scopeTree[targetIndexInTree * 2].first, left), min(scopeTree[targetIndexInTree * 2].second, right)),
                         getRangeResult(tree, scopeTree, targetIndexInTree * 2 + 1, max(scopeTree[targetIndexInTree * 2 + 1].first, left), min(scopeTree[targetIndexInTree * 2 + 1].second, right)));
    }
}
int main()
{
    // TODO: 入力やqueryの内容も問題によって違うから直してね
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];
    vector<ll> ts(q);
    vector<ll> xs(q);
    vector<ll> ys(q);
    rep(i, q)
    {
        cin >> ts[i] >> xs[i] >> ys[i];
    }

    // セグメントツリーを構築します。BITと違い、updateTreeを使って構築すると効率が悪いので別でやります。
    ll treeSize = 1;
    ll leafBegin = 1;
    while (treeSize < a.size() * 2)
    {
        treeSize = treeSize * 2 + 1;
        leafBegin *= 2;
    }
    // tree配列は1からtreeSizeまでを使います。
    vector<ll> tree(treeSize + 1);
    // 各ノードがsummarizeの責任を持つleafの範囲を0-indexedで持ちます。
    vector<pair<ll, ll>> scopeTree(treeSize + 1);
    rep(i, treeSize / 2 + 1) // ちなみにtreeSize/2+1はleafBeginと一致する
    {
        if (i < a.size())
        {
            tree[leafBegin + i] = a[i];
        }
        else
        {
            tree[leafBegin + i] = identityElement;
        }
        scopeTree[leafBegin + i] = pair<ll, ll>{i, i};
    }
    for (ll i = leafBegin - 1; i != 0; i--)
    {
        tree[i] = monoidSum(tree[i * 2], tree[i * 2 + 1]);
        scopeTree[i] = pair<ll, ll>{scopeTree[i * 2].first, scopeTree[i * 2 + 1].second};
    }

    // queryを処理していきます
    // TODO: 入力やqueryの内容も問題によって違うから直してね
    rep(i, q)
    {
        ll t = ts[i];
        ll x = xs[i];
        ll y = ys[i];
        x--;
        if (t == 1)
        {
            // updateTreeのtargetIndexは0始まり
            updateTree(tree, x, y);
        }
        else
        {
            y--;
            // // left included. right included.
            cout << getRangeResult(tree, scopeTree, 1, x, y) << endl;
        }
    }
    return 0;
}