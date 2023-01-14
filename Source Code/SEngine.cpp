//
// Created by Yaseen Ahmed on 2022-04-29.
//

#include "SEngine.h"
SEngine::SEngine() {
    curr_id = 0; //base id starts at 1
    page_count = 0;
}

//updates impressions
void SEngine::update_imp(int id, int imp) {


    for (int i=0; i<webpages.size(); i++)
        if (webpages[i].get_id() == id) {
            webpages[i].set_imp(imp);
            //cout << "Impressions for this page: " << webpages[i].get_imp() << endl;
        }



//    for (auto page : webpages)
//        if (page.get_id() == id) {
//            cout << "Page name: " << page.get_name() << endl;
//
//            page.set_imp(imp);
//            cout << "Impressions for this page: " << page.get_imp() << endl;
////            cout << "Now setting page with id" << id << " to: " << imp << endl;
////            cout << "Impressions of this page: " << page.get_imp() << endl;
//            //return;
//        }

    //cout << "AFTER LOOP: " << webpages[1].get_imp() << endl;
    //cout << "Number of webpages: " << webpages.size() << endl;

//        for (int i=0; i<webpages.size(); i++) {
//            cout << "In LOOP" << endl;
//            cout << webpages[i].get_imp() << endl;
//        }

}


string SEngine::get_name_by_id(int id) {
    for (auto page: webpages) {
        if (page.get_id() == id) {
            return page.get_name();
        }
    }
}

float SEngine::get_pr_by_id(int id) {

    for (auto page : webpages) {
        if (page.get_id() == id) {
            //cout << "Pr returned is: " << page.get_pr() << endl;
            return page.get_pr();
        }

    }
//    for (int i=0; i<webpages.size(); i++) {
//        if (webpages[i].get_id() == id) {
////            cout << "Id of the page is: " << webpages[i].get_id() << endl;
//            cout << "Pr returned is: " << webpages[i].get_pr() << endl;
//            return webpages[i].get_pr();
//        }
//
//    }
//    for (auto page: webpages) {
//        if (page.get_id() == id) {
//            return page.get_pr();
//        }
//    }
}
void SEngine::increase_imp_by_one(int id) {

    for (int i=0; i<webpages.size(); i++) {
        if (webpages[i].get_id() == id) {
            int imp = webpages[i].get_imp();
            imp+=1;
            cout << "Impression now for page " << webpages[i].get_name() << " are: " << webpages[i].get_imp() << endl;
            webpages[i].set_imp(imp);
            break;
        }
    }
//    for (auto page : webpages)
//        if (page.get_id() == id) {
//            int imp = page.get_imp();
//            //cout << "Impressions are previously: " << imp << endl;
//            imp+=1;
//            page.set_imp(++imp);
//            cout << "Impression now for page " << page.get_name() << " are: " << page.get_imp() << endl;
//            return;
//        }
}

void SEngine::update_pr_by_id(int id, float p) {

    cout << "Value passed is: " << p << endl;
    for (auto page : webpages) {
        if (page.get_id() == id) {
            //cout << "Setting pr to: " << p << endl;
            page.set_pr(p);
            //cout << "PR set to: " << page.get_pr() << endl;
        }

    }
//    for (int i=0; i<webpages.size(); i++) {
//        if (webpages[i].get_id() == id) {
//            cout << "P IS " << p;
//            webpages[i].set_pr(p);
//            cout << "PR of " << id << " updated to: " << p << endl;
//        }
//    }
}

float SEngine::get_pr_by_name(string name) {

    for (auto page: webpages) {
        if (page.get_name() == name) {
            //cout << "Pr returned is: " << page.get_pr() << endl;
            return page.get_pr();
        }

    }
}

void SEngine::update_imp_by_id(int id) {
    for (int i=0; i<webpages.size(); i++) {
        if(webpages[i].get_id() == id) {
            webpages[i].update_imp();
            cout << "imp of " << webpages[i].get_name() << " updated to: " << webpages[i].get_imp();
        }

    }
}

void SEngine::update_clicks_by_name(string n) {
    for (int i=0; i<webpages.size(); i++) {
        if(webpages[i].get_name() == n) {
            webpages[i].update_clicks();
            //cout << "clicks for "<< webpages[i].get_name() << " are: " <<webpages[i].get_clicks() << endl;

        }

    }
}

float SEngine::get_score_by_id(int id) {

    for (auto page: webpages) {
        if (page.get_id() == id) {
            //cout << "Score returned is: " << page.get_score() << endl;
            return page.get_score();
        }

    }
}


void SEngine::set_pr_norm(float p) {
    pr_norm = p;
}

float SEngine::get_pr_norm() {
    return pr_norm;
}
int SEngine::get_imp_by_id(int id) {

    for (auto page: webpages) {
        if (page.get_id() == id) {
            //cout << "Score returned is: " << page.get_score() << endl;
            return page.get_imp();
        }

    }
}