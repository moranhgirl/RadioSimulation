#include <iostream>
#include <iomanip>
#include "one_hop.h"
#include "stdev.h"

using namespace std;

int main() {
    //定义变量
    int n, num;
    string if_curve, if_input_right;
    double length, freqnc, bandwidth, radius, curve, slope;
    vector<double> summary;
    double length_sum = 0,
        average_sum = 0,
        min_wave_sum = 0,
        max_wave_sum = 0,
        bandwidth_sum = 0,
        delay_sum = 0,
        quality_sum = 0;

    //请求键盘输入侧视图的隧道路段数
    cout << "Please enter part-number of the tunnel." << endl;
    cin >> n;

    //每段分别计算最短电台位置和最远电台位置
    for (int i = 0; n > i; i++) {
        //请求键盘输入是否此段隧道有弯道
        cout << "Do No." << i + 1 << " part of the tunnel have a curve? Yes: Please enter 'Y', No: Please enter 'N'.";
        cin >> if_curve;
        while ( if_curve != "Y" && if_curve != "N") {
            cout << "Wrong input, please try again. Yes: Please enter 'Y', No: Please enter 'N'." << endl;
            cin >> if_curve;
        }
        //如果有弯道，请求输入此段隧道的长度、电台频率、电台带宽、弯道半径、弯道长度及此段隧道和海平面的角度
        if (if_curve == "Y") {
            cout << "Please enter the length of this part of the tunnel (m): " << endl;
            cin >> length;
            cout << "Please enter the frequency of the radio (GHz): " << endl;
            cin >> freqnc;
            cout << "Please enter the bandwidth of the radio (mbps): " << endl;
            cin >> bandwidth;
            cout << "Please enter the radius of the curve (m): " << endl;
            cin >> radius;
            cout << "Please enter length of the curve (m): " << endl;
            cin >> curve;
            cout << "Please enter angle of the slope (%): " << endl;
            cin >> slope;
            //确认输入参数是否正确，如果错误，重新输入需要修改的参数
            cout << "Please confirm if the input is right: (Yes: Please enter 'Y', No: Please enter 'N')" << "\n"
            << "Tunnel length: " << length << "m" << "\n"
            << "Radio frequency: " << freqnc << "GHz" << "\n"
            << "Radio bandwidth: " << bandwidth << "mbps" << "\n"
            << "Curve radius: " << radius << "m" << "\n"
            << "Curve length: " << curve << "m" << "\n"
            << "Slope angle: " << slope << "%" << endl;
            cin >> if_input_right;
            //确认输入正确
            while ( if_input_right != "Y" && if_input_right != "N") {
                cout << "Wrong input, please try again. Yes: Please enter 'Y', No: Please enter 'N'." << endl;
                cin >> if_input_right;
            }
            //请求修改数据并反复确认直到正确
            while ( if_input_right == "N" ) {
                //输入需要修改的数据编号
                cout << "Please enter the number of the data that needs to be changed: 1.Tunnel length, 2.Radio frequency, 3.Radio bandwidth, 4.Curve radius, 5.Curve length, 6.Slope angle" << endl;
                cin >> num;
                cout << "Please enter the new data." << endl;
                switch (num) {
                    case 1:
                        cin >> length;
                        break;
                    case 2:
                        cin >> freqnc;
                        break;
                    case 3:
                        cin >> bandwidth;
                        break;
                    case 4:
                        cin >> radius;
                        break;
                    case 5:
                        cin >> curve;
                        break;
                    case 6:
                        cin >> slope;
                        break;
                }
                cout << "Please confirm if the input is right: (Yes: Please enter 'Y', No: Please enter 'N')" << "\n"
                     << "Tunnel length: " << length << "m" << "\n"
                     << "Radio frequency: " << freqnc << "GHz" << "\n"
                     << "Radio bandwidth: " << bandwidth << "mbps" << "\n"
                     << "Curve radius: " << radius << "m" << "\n"
                     << "Curve length: " << curve << "m" << "\n"
                     << "Slope angle: " << slope << "%" << endl;
                cin >> if_input_right;
                while ( if_input_right != "Y" && if_input_right != "N") {
                    cout << "Wrong input, please try again. Yes: Please enter 'Y', No: Please enter 'N'." << endl;
                    cin >> if_input_right;
                }
            }
            //确认参数输入无误后进行下一步运算
            if (if_input_right == "Y") {
                summary = one_hop(length, freqnc, bandwidth, radius, curve, slope);
                length_sum = length_sum + length;
                average_sum = average_sum + length * summary[0];
                min_wave_sum = min_wave_sum + length * summary[1];
                max_wave_sum = max_wave_sum + length * summary[2];
                bandwidth_sum = bandwidth_sum + length * summary[3];
                delay_sum = delay_sum + length * summary[4];
                quality_sum = quality_sum + length * (summary[5] / 100);
            }
        }
        //如果没有弯道，请求输入此段隧道的长度、电台频率、电台带宽及此段隧道和海平面的角度
        else {
            radius = DBL_MAX;
            curve = 0;
            cout << "Please enter the length of this part of the tunnel (m): " << endl;
            cin >> length;
            cout << "Please enter the frequency of the radio (GHz): " << endl;
            cin >> freqnc;
            cout << "Please enter the bandwidth of the radio (mbps): " << endl;
            cin >> bandwidth;
            cout << "Please enter angle of the slope (%): " << endl;
            cin >> slope;
            //确认输入参数是否正确，如果错误，重新输入需要修改的参数
            cout << "Please confirm if the input is right: (Yes: Please enter 'Y', No: Please enter 'N')" << "\n"
            << "Tunnel length: " << length << "m" << "\n"
            << "Radio frequency: " << freqnc << "GHz" << "\n"
            << "Radio bandwidth: " << bandwidth << "mbps" << "\n"
            << "Curve radius: " << radius << "m" << "\n"
            << "Curve length: " << curve << "m" << "\n"
            << "Slope angle: " << slope << "%" << endl;
            cin >> if_input_right;
            while ( if_input_right != "Y" && if_input_right != "N") {
                cout << "Wrong input, please try again. Yes: Please enter 'Y', No: Please enter 'N'." << endl;
                cin >> if_input_right;
            }
            while ( if_input_right == "N" ) {
                //输入需要修改的数据编号
                cout << "Please enter the number of the data that needs to be changed: 1.Tunnel length, 2.Radio frequency, 3.Radio bandwidth, 4.Curve radius, 5.Curve length, 6.Slope angle" << endl;
                cin >> num;
                cout << "Please enter the new data." << endl;
                switch (num) {
                    case 1:
                        cin >> length;
                        break;
                    case 2:
                        cin >> freqnc;
                        break;
                    case 3:
                        cin >> bandwidth;
                        break;
                    case 4:
                        cin >> radius;
                        break;
                    case 5:
                        cin >> curve;
                        break;
                    case 6:
                        cin >> slope;
                        break;
                }
                cout << "Please confirm if the input is right: (Yes: Please enter 'Y', No: Please enter 'N')" << "\n"
                     << "Tunnel length: " << length << "m" << "\n"
                     << "Radio frequency: " << freqnc << "GHz" << "\n"
                     << "Radio bandwidth: " << bandwidth << "mbps" << "\n"
                     << "Curve radius: " << radius << "m" << "\n"
                     << "Curve length: " << curve << "m" << "\n"
                     << "Slope angle: " << slope << "%" << endl;
                cin >> if_input_right;
                while ( if_input_right != "Y" && if_input_right != "N") {
                    cout << "Wrong input, please try again. Yes: Please enter 'Y', No: Please enter 'N'." << endl;
                    cin >> if_input_right;
                }
            }
            if (if_input_right == "Y") {
                summary = one_hop(length, freqnc, bandwidth, radius, curve, slope);
                length_sum = length_sum + length;
                average_sum = average_sum + length * summary[0];
                min_wave_sum = min_wave_sum + length * summary[1];
                max_wave_sum = max_wave_sum + length * summary[2];
                bandwidth_sum = bandwidth_sum + length * summary[3];
                delay_sum = delay_sum + length * summary[4];
                quality_sum = quality_sum + length * (summary[5] / 100);
            }
        }
    }

    //计算所有隧道运算结果的加权平均值，作为电台位置参考
    average_sum = average_sum / length_sum;
    min_wave_sum = min_wave_sum / length_sum;
    max_wave_sum = max_wave_sum / length_sum;
    bandwidth_sum = bandwidth_sum / length_sum;
    delay_sum = delay_sum / length_sum;
    quality_sum = (quality_sum / length_sum) * 100;

    //以小数点后两位的精度输出总结果
    cout << fixed << setprecision(2)<< "average = " << average_sum << "m"<< endl;
    cout << "min wave = " << min_wave_sum << "m"<< endl;
    cout << "max wave = " << max_wave_sum << "m"<< endl;
    cout << "bandwidth = " << bandwidth_sum << "mbps"<< endl;
    cout << "delay = " << delay_sum << "ms"<< endl;
    cout << "quality = " << quality_sum << "%"<< endl;

    return 0;
}