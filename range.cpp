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

// endは排他的(exclusive)なので注意
vector<ll> range(ll end)
{
    vector<ll> result;
    for (ll i = 0; i < end; ++i)
    {
        result.push_back(i);
    }
    return result;
}

// endは排他的(exclusive)なので注意
vector<ll> range(ll begin, ll end)
{
    vector<ll> result;
    for (ll i = begin; i < end; ++i)
    {
        result.push_back(i);
    }
    return result;
}

// endは排他的(exclusive)なので注意
vector<ll> range(ll begin, ll end, ll step)
{
    vector<ll> result;
    for (ll i = begin; i < end; i += step)
    {
        result.push_back(i);
    }
    return result;
}

int main()
{
    vector<ll> a = range(10);
    vector<ll> b = range(5, 15);
    vector<ll> c = range(15, 35, 2);
    for (ll x : a)
    {
        cout << x << ' ';
    }
    cout << endl;
    for (ll x : b)
    {
        cout << x << ' ';
    }
    cout << endl;
    for (ll x : c)
    {
        cout << x << ' ';
    }
    cout << endl;
}