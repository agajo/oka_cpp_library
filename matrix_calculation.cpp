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

// それぞれの行列が長方形になってるかのチェックはしてないので注意！
vector<vector<ll>> matrixProduct(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
    ll aHeight = a.size();
    ll inter;
    if (a.front().size() == b.size())
    {
        inter = b.size();
    }
    else
    {
        cout << "Can't make a matrix product!! Check the sizes!!" << endl;
        return vector<vector<ll>>();
    }
    ll bWidth = b.front().size();
    vector<vector<ll>> result(aHeight, vector<ll>(bWidth, 0));
    rep(i, aHeight)
    {
        rep(j, bWidth)
        {
            ll tempResult = 0;
            rep(k, inter)
            {
                tempResult += a[i][k] * b[k][j];
            }
            result[i][j] = tempResult;
        }
    }
    return result;
}

// 転置行列
vector<vector<ll>> matrixTranspose(vector<vector<ll>> &a)
{
    ll aHeight = a.size();
    ll aWidth = a.front().size();
    vector<vector<ll>> result(aWidth, vector<ll>(aHeight, 0));
    rep(i, aHeight)
    {
        rep(j, aWidth)
        {
            result[j][i] = a[i][j];
        }
    }
    return result;
}

int popcount(int x)
{
    int ret = 0;
    while (x > 0)
    {
        ret += x & 1;
        x = x >> 1;
    }
    ret += x & 1;
    return ret;
}

// アダマール行列
vector<vector<ll>> hadamard(ll n)
{
    ll m = 1;
    rep(i, n)
    {
        m *= 2;
    }
    vector<vector<ll>> result(m, vector<ll>(m));
    rep(i, m)
    {
        rep(j, m)
        {
            result[i][j] = (popcount(i & j) % 2) * 2 - 1;
        }
    }
    return result;
}

int main()
{
    ll n;
    cin >> n;
    vector<vector<ll>> h = hadamard(n);
    vector<vector<ll>> t = matrixTranspose(h);
    vector<vector<ll>> result = matrixProduct(h, t);
    rep(i, result.size())
    {
        rep(j, result.front().size())
        {
            cout << result[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
