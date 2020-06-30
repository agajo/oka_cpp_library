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

// TODO: 終了判定を改造する
// 終了判定
bool check(ll x, ll y)
{
    return x * x + y * y == 22690;
}

pair<ll, ll> squareSearch(ll initialX, ll initialY)
{
    ll x = initialX;
    ll y = initialY;
    bool done = false;
    ll finalX;
    ll finalY;

    if (check(x, y))
    {
        finalX = x;
        finalY = y;
        done = true;
    }

    ll k = 0;

    while (!done)
    {
        k += 2;
        --x;
        --y;
        for (ll i = 0; i < k; ++i)
        {
            ++x;
            if (check(x, y))
            {
                finalX = x;
                finalY = y;
                done = true;
            }
        }
        for (ll i = 0; i < k; ++i)
        {
            ++y;
            if (check(x, y))
            {
                finalX = x;
                finalY = y;
                done = true;
            }
        }
        for (ll i = 0; i < k; ++i)
        {
            --x;
            if (check(x, y))
            {
                finalX = x;
                finalY = y;
                done = true;
            }
        }
        for (ll i = 0; i < k; ++i)
        {
            --y;
            if (check(x, y))
            {
                finalX = x;
                finalY = y;
                done = true;
            }
        }
    }
    return pair{finalX, finalY};
}

int main()
{
    pair<ll, ll> result = squareSearch(100, 0);
    cout << get<0>(result) << " " << get<1>(result) << endl;
}