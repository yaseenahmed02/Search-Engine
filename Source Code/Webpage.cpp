//
// Created by Yaseen Ahmed on 2022-04-27.
//

#include "Webpage.h"

Webpage::Webpage() {
    name = "";
    id = -1;
    CTR = 0.0;
    PR = 0.0;
    imp = 0;
    clicks = 0;
    score = 0.0;
}

void Webpage::set_id(int ID) {
    this->id = ID;
}

void Webpage::set_name(string n) {
    this->name = n;
}

void Webpage::set_imp(int i) {
    imp = i;
}

void Webpage::set_pr(float p) {
    this->PR = p;
}

int Webpage::get_id() {
    return id;
}

string Webpage::get_name() {
    return name;
}

int Webpage::get_imp() {
    return imp;
}

float Webpage::get_pr() {
    return PR;
}

void Webpage::calculate_score(float PR_norm) {

    //cout << "NORM is: " << PR_norm << endl;
    if (clicks == 0) CTR = 0.0;
    else
        float CTR = float(imp) / float(clicks);
    //cout << "CTR of" << name << " is: " << CTR << endl;
    float fraction = (1 - (0.1 * imp) / (1 + (0.1 * imp)));

    //cout << "Fraciton of" << name << " is: " << fraction << endl;

    score = 0.4 * PR_norm + (fraction * PR_norm + fraction * CTR) * 0.6;
    //score = 0.4 * PR_norm + ((  (1 - (   (0.1 * imp) / ( 1 + (0.1*imp) ) )  ) * PR_norm + (   (0.1 * imp) / (1 + (0.1*imp)) ) * CTR  )*0.6);
    //cout << "Score calculated is: " << score << endl;
}

void Webpage::update_imp() {
    imp++;
}

void Webpage::update_clicks() {
    clicks++;
}

float Webpage::get_score() {
    return score;
}

int Webpage::get_clicks() {
    return clicks;
}




