//
// Created by Yaseen Ahmed on 2022-04-27.
//

#ifndef SEARCHENGINEPROJECT_WEBPAGE_H
#define SEARCHENGINEPROJECT_WEBPAGE_H
#include "Graph.h"

class Webpage {
private:
    int id; //id to use in graph
    string name; //name
    float CTR; //click-through-rate
    float PR; //page rank
    int imp; //number of impressions (number of times it appeared)
    int clicks; //number of clicks
    //int views; //number of times this page has been displayed
    float score;
public:
    Webpage();
    void set_id(int);
    void set_name(string);
    void set_imp(int);
    void set_pr(float);
    string get_name();
    int get_id();
    int get_imp();
    float get_pr();
    void calculate_score(float); //takes norm pr
    void update_imp();
    void update_clicks();
    float get_score();
    int get_clicks();


};



#endif //SEARCHENGINEPROJECT_WEBPAGE_H
