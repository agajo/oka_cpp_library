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

random_device seed_gen;
mt19937 engine(seed_gen());
// 0, 1, 2 のどれかが得られる一様分布
// uniform_int_distribution<> dist(0, 2);
// cout << dist(engine) << endl;
// みたいに、先に確率分布を宣言して、そこにengineを与えて使う。

int main()
{
    uniform_int_distribution<> dist(0, 2);
    cout << dist(engine) << endl;
    return 0;
}