//
// Created by Moran on 2022/1/3.
//

#include "stdev.h"

using namespace std;

//是一个用于计算标准方差的函数
double stdev(vector<double> v)
{
    double sum = accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();

    vector<double> diff(v.size());
    transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
    double sq_sum = inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = sqrt(sq_sum / (v.size() - 1));
    //cout << "stdev of waves = " << stdev << endl;
    return stdev;
}

