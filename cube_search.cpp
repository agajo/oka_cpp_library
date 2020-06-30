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

// ===== cube_search ここから下をコピペ ========

// TODO: 終了判定を改造する
// 終了判定
bool check(ll x, ll y, ll z)
{
    if (x == 0 || y == 0 || z == 0)
        return false;
    return x * x + y * y == z * z;
}

// sign これも必要
ll sign(ll x)
{
    return (x > 0) - (x < 0);
}

tuple<ll, ll, ll> cubeSearch(ll initialX, ll initialY, ll initialZ)
{
    bool done = false;
    ll finalX;
    ll finalY;
    ll finalZ;

    if (check(initialX, initialY, initialZ))
    {
        finalX = initialX;
        finalY = initialY;
        finalZ = initialZ;
        done = true;
    }

    // BFS(幅優先探索)を使います

    using point = array<ll, 3>;

    queue<point> ps;
    for (ll i = -1; i <= 1; ++i)
    {
        for (ll j = -1; j <= 1; ++j)
        {
            for (ll k = -1; k <= 1; ++k)
            {
                point tempP = point{initialX + i, initialY + j, initialZ + k};
                {
                    if (i != 0 || j != 0 || k != 0)
                        ps.push(tempP);
                }
            }
        }
    }
    while (!done)
    {
        point p = ps.front();
        ps.pop();
        ll x = get<0>(p);
        ll y = get<1>(p);
        ll z = get<2>(p);
        if (check(x, y, z))
        {
            finalX = x;
            finalY = y;
            finalZ = z;
            done = true;
        }
        else
        {
            ll dx = x - initialX;
            ll dy = y - initialY;
            ll dz = z - initialZ;
            if (abs(dx) == abs(dy) && abs(dy) == abs(dz))
                ps.push(point{x + sign(dx), y + sign(dy), z + sign(dz)});
            if (abs(dx) == abs(dy) && abs(dx) >= abs(dz))
                ps.push(point{x + sign(dx), y + sign(dy), z});
            if (abs(dy) == abs(dz) && abs(dy) >= abs(dx))
                ps.push(point{x, y + sign(dy), z + sign(dz)});
            if (abs(dz) == abs(dx) && abs(dz) >= abs(dy))
                ps.push(point{x + sign(dx), y, z + sign(dz)});
            if (abs(dx) >= abs(dy) && abs(dx) >= abs(dz))
                ps.push(point{x + sign(dx), y, z});
            if (abs(dy) >= abs(dx) && abs(dy) >= abs(dz))
                ps.push(point{x, y + sign(dy), z});
            if (abs(dz) >= abs(dy) && abs(dz) >= abs(dx))
                ps.push(point{x, y, z + sign(dz)});
        }
    }
    return tuple<ll, ll, ll>{finalX, finalY, finalZ};
}

int main()
{
    tuple<ll, ll, ll> result = cubeSearch(-100, 20, 105);
    cout << get<0>(result) << ' ' << get<1>(result) << ' ' << get<2>(result) << endl;
}