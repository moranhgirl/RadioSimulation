//
// Created by Moran on 2022/1/3.
//
#include "one_hop.h"
#include "stdev.h"

using namespace std;

//隧道每一段的电台信息计算
vector<double> one_hop(double length, double freqnc, double bandwidth, double radius, double curve, double slope) {
        double sides = 2,
            signal_hops = 2,
            tunn_hei = 8,
            radio_hei = 2,
            tunn_wid = 16,
            radio_clear = 1,
            delay = 0.1,
            loss_per_deg_km = 30;
        int radio_hops;
        double wave_len, E_Fresnel_r1, E_Fresnel_d, E_Fresnel_D, E_Fresnel_d1, E_Fresnel_d1s, E_Fresnel_Dtr, M_Fresnel_r1, M_Fresnel_d, M_Fresnel_D, M_Fresnel_d2, M_Fresnel_d2s, M_Fresnel_Dtr, degree, loss_per_km, loss_slope, line_sight, turn_degree, loss_per_secant, loss_turn, sky_wave, ground_wave, side_wave, other_wave, bandwid_new, delay_new, average, quality, decibel, min_wave, max_wave;


        //计算电台在隧道中的直视距离
        radio_hops = signal_hops / 2;
        wave_len = 299792458 / (freqnc * 1000000000);
        E_Fresnel_r1 = (tunn_hei * tunn_wid + tunn_wid * tunn_hei) / (tunn_hei + tunn_wid) / 2;
        E_Fresnel_d = pow(E_Fresnel_r1,2) / wave_len;
        E_Fresnel_D = 2 * E_Fresnel_d;
        E_Fresnel_d1 = pow(radio_hei,2) / wave_len;
        E_Fresnel_d1s = (E_Fresnel_d1 * (E_Fresnel_D - E_Fresnel_d1)) / E_Fresnel_D;
        E_Fresnel_Dtr = 2 * E_Fresnel_d1s * 2 / sides;

        M_Fresnel_r1 = (pow(tunn_hei, 2) + pow(tunn_wid, 2)) / (tunn_hei + tunn_wid) / 2;
        M_Fresnel_d = pow(M_Fresnel_r1, 2) / wave_len;
        M_Fresnel_D = 2 * M_Fresnel_d;
        M_Fresnel_d2 = pow(radio_clear, 2) / wave_len;
        M_Fresnel_d2s = (M_Fresnel_d2 * (M_Fresnel_D - M_Fresnel_d2)) / M_Fresnel_D;
        M_Fresnel_Dtr = 2 * M_Fresnel_d2s * 2 / sides;

        degree = atan(slope / 100) * 180 / M_PI;
        loss_per_km = loss_per_deg_km * abs(degree);
        loss_slope = (loss_per_km * length) / 1000;
        line_sight = sqrt(2 * tunn_wid * radius - pow(tunn_wid, 2));
        turn_degree = atan(tunn_wid / line_sight) * 180 / M_PI;
        loss_per_secant = loss_per_deg_km * turn_degree;
        loss_turn = curve * loss_per_secant / (line_sight * 2 * sides);

        sky_wave = 2 * E_Fresnel_D * signal_hops - loss_slope;
        ground_wave = E_Fresnel_Dtr + sky_wave;
        side_wave = 2 * M_Fresnel_D * signal_hops - loss_turn;
        other_wave = M_Fresnel_Dtr + side_wave;
        average = (sky_wave + ground_wave + side_wave + other_wave) / 4;

        if (sky_wave - ground_wave >= 0)
            min_wave = ground_wave;
        else
            min_wave = sky_wave;
        if (side_wave - other_wave >= 0)
            max_wave = side_wave;
        else
            max_wave = other_wave;

        vector<double> waves = {sky_wave, ground_wave, side_wave, other_wave};
        quality = exp(-signal_hops * stdev(waves) / average) * 100;

        bandwid_new = bandwidth * (quality / 100);
        delay_new = delay * (1 - quality / 100) / (quality / 100);
        decibel = 10 * log(quality / 100) / log(10);

        vector<double> summary = {average, min_wave, max_wave, bandwid_new, delay, quality};
        return summary;
}

