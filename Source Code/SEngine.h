//
// Created by Yaseen Ahmed on 2022-04-29.
//

#ifndef SEARCHENGINEPROJECT_SENGINE_H
#define SEARCHENGINEPROJECT_SENGINE_H
#include "Webpage.h"
#include <map>
#include <set>

class SEngine {
private:
    float pr_norm;
public:
    vector<Webpage> webpages; //array of webpages
    int page_count;
    int curr_id;
    void update_imp(int, int);
    void update_pr_by_id(int, float);
    void increase_imp_by_one(int);
    string get_name_by_id(int);
    float get_pr_by_id(int);
    float get_pr_by_name(string);
    void update_imp_by_id(int); //updates views by the id
    void update_clicks_by_name(string);
    map<string, vector<int>> keys; //stores the keywords, and the id's of all the pages that have them
    map<int, vector<string>> index; //stores the id of the page and the list of words it contains for "AND" function
    map<int, int> imp_cnt; //stores the id and impressions
    SEngine();
    void sort_by_pr();
    float get_score_by_id(int);
    void calc_scores();
    void set_pr_norm(float);
    float get_pr_norm();
    int get_imp_by_id(int);


};


#endif //SEARCHENGINEPROJECT_SENGINE_H
