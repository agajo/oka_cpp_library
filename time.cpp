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
#include <chrono>

using namespace std;
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)

int main()
{

    vector<ll> testVector;
    ll testCount = 0;
    ll elappsedTime = 0;
    auto startTimeAt = chrono::system_clock::now();
    while (elappsedTime < 5000)
    {
        testVector.push_back(testCount);
        testCount++;
        auto endTimeAt = chrono::system_clock::now();
        elappsedTime = chrono::duration_cast<chrono::milliseconds>(endTimeAt - startTimeAt).count();
    }
    cout << testVector.size() << endl;
    cout << elappsedTime << endl;
    return 0;
}