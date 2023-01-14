#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
//#include "Graph.h"
//#include "Webpage.h"
#include "SEngine.h"

bool pr_sorting(const Webpage &a, const Webpage &b);

map<string, int> pages; //page and their id's
vector<string> keywords;
vector<string> links;
const int base_id = 1000;
//if website appeared, increase impressions
//if they choose a webpage, update the second componenet of CTR
void display_main_menu();
void new_search();
void init_program(Graph&);
void read_webgraph_csv(Graph&);
void read_keywords_csv();
void read_impressions_csv();
void init_page_ranks(Graph&);
void display_webpage_choice(vector<pair<float, string>>);
void display_results(vector<string>);
void increase_imp_after_displaying(vector<string>);
void update_pr(Graph&);
void update_all_scores();
void save_impressions_csv();

SEngine engine;

int main() {



    Graph webgraph(40);
//    if (pages["www.test1.com"]) cout <<"YES" << endl;
//    else cout << "NO" << endl;
    init_program(webgraph); //reading the files
//    engine.webpages[2].set_pr(10000);
//    cout << engine.webpages[2].get_pr() << endl;
    display_main_menu();

//    for (int i=0; i<engine.webpages.size(); i++) {
//        cout << "Name: " << engine.webpages[i].get_name() << endl;
//        cout << "ID: " << engine.webpages[i].get_id();
//        cout << endl << endl;
//    }

//    for (int i=0; i<keywords.size(); i++) cout << keywords[i] << endl;
//    return 0;

//    for (int i=0; i<engine.keys.size(); i++) {
//        cout << engine.keys->first;
//        for (auto word : engine.keys->second) cout << word << endl;
//    }
}

void init_program(Graph &webgraph) {

    read_webgraph_csv(webgraph);
    //webgraph.display();
    read_keywords_csv();
    read_impressions_csv();
    init_page_ranks(webgraph);


    vector<string> temp = engine.index[4];
//    cout << "SIZE OF THIS VECTOR: " << temp.size() << endl;
//    cout << temp[3] << endl;
    //update_pr(webgraph);


//    for (int i=0; i<engine.webpages.size(); i++) {
//        cout << "Name: " << engine.webpages[i].get_name() << ", PR: " << engine.webpages[i].get_pr() << endl;
//    }

}

void display_main_menu() {

    string input;

    do {

        update_all_scores();
        //system("cls");
        cout << "-----Main Menu-----" << endl;
        cout << "1) New Search" << endl;
        cout << "2) Exit" << endl;


        cout << "\n==> ";
        getline(cin, input);

        while (input != "1" && input != "2")
        {
            cout << "Invalid Input!... Please try again" << endl;
            cout << "Please make another selection: ";
            cin >> input;
        }

        if (input == "1") {
            new_search();
        }
        else if (input == "2") {
            cout << "Thank you for using the program!";
            //udpate the files
            save_impressions_csv();
            exit(1);

        }

    } while (input != "2" && input != "Quit" && input != "quit");
}


void read_webgraph_csv(Graph &g) {
    ifstream fin;
    fin.open("/Users/yaseenahmed/Workspace/AUC/Academics/Spring 2022/Analysis Lab/Project/Backup Recent/webgraph.csv");
    if (fin.fail()) {
        cout << "Could not open the webgraph file" << endl;
        exit(1);
    }
    else {

        //we have four scenarios when reading in a line which contains two pages:
        //1: Both of them exist from before
        //2: The first webpage exists from before but the second one does not
        //3: The second page exists from before but the first one does not
        //4: Both of them do not eixst from before

        /*
         Whenever we see a new webpage, we have to create a webpage object with its name and give it an id,
         we have to update the page count and last known id in the search engine object, we must update it's id value in the map
         and we have to add an edge from it to it in the graph.
        */
        while (!fin.eof()) {
            string name1, name2;
            getline(fin, name1, ',');
            getline(fin, name2, '\n');

            //get their id's from the map
            int id1 = pages[name1];
            int id2 = pages[name2];

            if (id1 && id2) { //if they are both not new pages
                g.add_edge(id1, id2);
                //cout << "Adding edge between " << id1 << " and " << id2 << endl;
            }

            else if (id1 && !id2) { //if only page 1 exists and page 2 does not
                Webpage w2;
                w2.set_name(name2);
                id2 = ++engine.curr_id;
                w2.set_id(id2); //adding a new id
                engine.page_count++; //updaing the page count
                engine.webpages.push_back(w2);
                pages[name2] = id2;

                g.add_edge(id1, id2);
                //cout << "Adding edge between " << id1 << " and " << id2 << endl;
            }
            else if (!id1 && id2) { //if only page 2 exists and page 1 does not
                Webpage w1;
                w1.set_name(name1);
                id1 = ++engine.curr_id;
                w1.set_id(id1); //adding a new id
                engine.page_count++; //updating the page count
                engine.webpages.push_back(w1);
                pages[name1] = id1;

                g.add_edge(id1, id2);
                //cout << "Adding edge between " << id1 << " and " << id2 << endl;
            }
            else if (!id1 && !id2) { //if only id1 exists and id2 does not
                Webpage w1, w2;
                w1.set_name(name1);
                id1 = ++engine.curr_id;
                w1.set_id(id1); //adding a new id
                engine.page_count++; //updaing the page count
                engine.webpages.push_back(w1);


                w2.set_name(name2);
                id2 = ++engine.curr_id;
                w2.set_id(id2); //adding a new id
                engine.page_count++; //updaing the page count
                engine.webpages.push_back(w2);

                pages[name1] = id1;
                pages[name2] = id2;

                g.add_edge(id1, id2);
                //cout << "Adding edge between " << id1 << " and " << id2 << endl;
            }
        }
    }


}

void read_keywords_csv() {

    ifstream fin;
    fin.open("/Users/yaseenahmed/Workspace/AUC/Academics/Spring 2022/Analysis Lab/Project/Backup Recent/keywords.csv");

    if (fin.fail()) {
        cout << "Could not open the keywords file" << endl;
        exit(1);
    }
    else {
        string line;
        int i = 1;
        while (getline(fin, line, '\n')) {
            //cout << "Line " << i++ << ": " << line <<  endl;

            string word, link;
            link = line.substr(0, line.find(','));
            line.erase(0, link.size()+1);
            stringstream str(line);
            //cout << "Line is now: " << line << endl;
            //cout << "Link: " << link << endl;
            while(getline(str, word, ',')) {
                //cout << "now adding: " << word << endl;
                keywords.push_back(word);
                engine.keys[word].push_back(pages[link]); //in the keys map in engine, we push back the id of that page
                engine.index[pages[link]].push_back(word);

            }


        }

    }

}

void read_impressions_csv() {

    ifstream fin;
    fin.open("/Users/yaseenahmed/Workspace/AUC/Academics/Spring 2022/Analysis Lab/Project/Backup Recent/impressions.csv");

    if (fin.fail()) {
        cout << "Could not open the impressions file" << endl;
        exit(1);
    }
    else {
        while(!fin.eof()) {
            string name, impressions;
            getline(fin, name, ',');
            getline(fin, impressions, '\n');
            if (name == "") break;
            engine.update_imp(pages[name], stoi(impressions));
            engine.imp_cnt[pages[name]] = stoi(impressions);
//            cout << "Name: " << name << endl;
//            cout << "Imp: " << stoi(impressions) << endl;

        }

    }

}

void init_page_ranks(Graph &g) {

    //cout << "Size of map is: " << pages.size() << endl;
    float sum = 0.0;
    float pr = 1/float(pages.size());
    //cout << "starting pr is: " << pr << endl;

    for (int i=0; i<engine.webpages.size(); i++) {
        engine.webpages[i].set_pr(pr);
    }

    vector<pair<int, float>> new_pr; //stores the id and the pr of the nodes

    map<string, int>::iterator it;
    for (int i=0; i<2; i++) {
        //cout << "HERE first loop" << endl;
        for (it = pages.begin(); it!= pages.end(); it++) {
            //cout << "HERE second loop" << endl;
            int curr_id = it->second;

            //cout << "Curr id: " << curr_id << endl;
            //cout << "Pages size: " << pages.size() << endl;
            //g.displayGraph();
            Graph temp = g.get_transpose();
            //temp.display();

            vector<int> nodes_pointing_to_curr = temp.get_nodes_pointing_to_v(curr_id);
            //cout << "NODES POINTING TO " << curr_id << " ARE: " << endl;
            //for (auto node: nodes_pointing_to_curr) cout << node << ", ";
            //vector<int> nodes_pointing_to_curr = g.get_nodes_pointing_to_v(curr_id); //stores the id's of the node's pointing to V

            //cout << "Current node: " << curr_id << endl;
            //cout << "SIZE is: " << nodes_pointing_to_curr.size() << endl;
            //for (auto node : nodes_pointing_to_curr) cout << "node: " << node << endl;
            float page_rank = 0.0;

            // cout << "BLHA BLAH " << engine.webpages[2].get_pr() << endl;

            //the summation
            for (int j=0; j<nodes_pointing_to_curr.size(); j++) {
                //cout << "IN THIRD LOOP" << endl;
                int curr_node_pointing = nodes_pointing_to_curr[j];
                //cout << "ID OF current node: " << curr_node_pointing << endl;
                float prev_pr = engine.get_pr_by_id(curr_node_pointing);
                //cout << "Prev pr for "<< engine.get_name_by_id(curr_id) << " is: " << prev_pr << endl;
                float temp_pr = prev_pr / g.num_edges_out(curr_node_pointing);

                page_rank+= temp_pr;
            }

            //damping factor
            page_rank = 0.85 * page_rank;
            page_rank = page_rank + ((1 - 0.85) / pages.size());
            //cout << "The final page rank for: " << engine.get_name_by_id(curr_id) << " is: " << page_rank << endl;
            //cout << "PAGE RANK IS " << page_rank << endl;
            //engine.update_pr_by_id(curr_id, page_rank);

            if (i == 1) {
                new_pr.push_back(make_pair(curr_id, page_rank));
                sum += page_rank; //stores sum of all pr's to calculate the pr norm
                //cout << "Sum is now: " << sum << endl;
            }

        }

    }


//    for (int i=0; i<new_pr.size(); i++)
//        cout << new_pr[i].first << ", " << new_pr[i].second << endl;

    for (int i=0; i<engine.webpages.size(); i++) {
        engine.webpages[i].set_pr(new_pr[i].second);
    }

    engine.set_pr_norm(sum / engine.index.size()); //calculating norm pr
}


void new_search() {

    /*
     * We have four cases
     * Case 1: one keyword like "data structures" with quotations
     * Case 2: two keywords separated by "AND"
     * Case 3: two keywords separated by "OR"
     * Case 4: two keywords like data structures without quotations
     * */


    //update_all_scores();
    string line;
    vector<string> words;
    cout << "Type in your choice: ";
    getline(cin, line);


    //case 1
    if (line.find('\"') != string::npos) {
        string keyword = line.substr(1, line.size()-2); //to remove the quotations
        if (engine.keys[keyword].size() == 0) {
            cout << "This keyword is not found" << endl;
            return;
        }
        else {//loop over the links which store this keyword
            cout << "Search Results: " << endl;
            words.clear();
            words.push_back(keyword);
            display_results(words);

//            for (int i=0; i<engine.keys[keyword].size(); i++) {
//                cout<< i+1 << ". " << engine.get_name_by_id(engine.keys[keyword][i]) << endl;
//                engine.increase_imp_by_one(engine.keys[keyword][i]);
//            }
//            for (auto page_id : engine.keys[keyword]) {
//                //display the pages, update their impressions, update page ranks, ask for input on which one they would like
//                int i=1;
//                //need to display based on page ranks
//                cout << i << ". " << engine.get_name_by_id(page_id) << endl;
//                engine.increase_imp_by_one(page_id);
//                i++;
//                //resort webpages array based on page ranks
//
//            }


            return;
        }
    }
    else if (line.find("AND") != string::npos) {
        words.clear();
        string first_word = line.substr(0, line.find("AND")-1);
        line.erase(0, line.find("AND") + 4);
        string second_word = line.substr(0, line.size());

        words.push_back(first_word);
        words.push_back(second_word);
        words.push_back("AND");
        display_results(words);


    }
    else if (line.find("OR") != string::npos) {
        words.clear();
        string first_word = line.substr(0, line.find("OR")-1);
        line.erase(0, line.find("OR") + 3);
        string second_word = line.substr(0, line.size());
        //cout << "FIrst word:" << first_word << "," << second_word << endl;
        words.push_back(first_word);
        words.push_back(second_word);
        display_results(words);

    }
    else {
        words.clear();
        stringstream ss(line);
        string token;
        while(getline(ss, token, ' '))
            words.push_back(token);

        string first_word = words[0], second_word = words[1];
        words.push_back(first_word);
        words.push_back(second_word);
        display_results(words);
    }

//    //Case 1: Quotations
//    if (words.size() == 1 && words[0][0] == '\"') {
//        cout << "In Quotations Case" << endl;
//        string keyword = words[0];
//
//        if (engine.keys[keyword].size() == 0) {
//            cout << "This keyword is not found" << endl;
//            return;
//        }
//        else {//loop over the links which store this keyword
//            cout << "Search Results: " << endl;
//            for (auto page_id : engine.keys[keyword]) {
//                //display the pages, update their impressions, update page ranks, ask for input on which one they would like
//                cout << engine.get_name_by_id(page_id) << endl;
//            }
//
//        }
//
//
//    }
//    //Case 2: AND
//    else if (words[1] == "AND") {
//
//    }
//    //Case 3: OR
//    else if (words[1] == "OR") {
//
//    }
//    //Case 4
//    else {
//
//    }

    return;
}



void display_results(vector<string> keywords) {

    vector<pair<float, string>> pages_to_display; //vector to store the pr, and the name
    map<string, int> prev_appended;

    if(keywords[2] == "AND") {

        map<int, vector<string>>::iterator it;
        for(it = engine.index.begin();  it != engine.index.end(); ++it) {
            int id = it->first;

            vector<string> links = it->second;
            vector<string>::iterator v_it;

            if (find(links.begin(), links.end(), keywords[0]) != links.end() && find(links.begin(), links.end(), keywords[1]) != links.end()) {
                //float pr = engine.get_pr_by_id(id);
                float score = engine.get_score_by_id(id);
                string name = engine.get_name_by_id(id);
                pages_to_display.push_back(make_pair(score,name));
                engine.imp_cnt[id]++;
                //engine.update_imp_by_id(id);

            }

        }

    }
    else
        for (int j=0; j<keywords.size(); j++) {
            for (int i=0; i<engine.keys[keywords[j]].size(); i++) {
                string name = engine.get_name_by_id(engine.keys[keywords[j]][i]);
                float pr = engine.get_pr_by_id(engine.keys[keywords[j]][i]);
                float score = engine.get_score_by_id(engine.keys[keywords[j]][i]);
                //cout << "Pr of " << name << " is: " << pr << endl;
                //cout << "Score of " << name << " is: " << score << endl;

                if (!prev_appended[name]) {
                    pages_to_display.push_back(make_pair(score,name));
                    prev_appended[name] = true;
                    engine.imp_cnt[engine.keys[keywords[j]][i]]++;
                    //engine.update_imp_by_id(engine.keys[keywords[j]][i]); //updating views
                   // engine.increase_imp_by_one(engine.keys[keywords[j]][i]); //updating impressions
                }



            }

                //cout<< i+1 << ". " << engine.get_name_by_id(engine.keys[keywords[j]][i]) << endl;
                //engine.increase_imp_by_one(engine.keys[keywords[j]][i]);
        }


    vector<pair<float, string>> pages_to_display2 = pages_to_display;

    sort(pages_to_display2.rbegin(), pages_to_display2.rend()); //sort by pr in descending order

    for (int i=0; i<pages_to_display2.size(); i++) {
        cout << i+1 << ". " << pages_to_display2[i].second << endl;
    }
//    for (auto page : pages_to_display) {
//        cout << page.second << ": " << page.first << endl;
//    }
    //increase_imp_after_displaying(keywords);

    display_webpage_choice(pages_to_display);


}

void display_webpage_choice(vector<pair<float, string>> pages_displayed) {

    string input;

    cout << endl << endl;
    do {

        cin.clear();
        //cin.ignore();

        //system("cls");
        cout << "-----Webpage Choice-----" << endl;
        cout << "1) Choose a webpage to open" << endl;
        cout << "2) New Search" << endl;
        cout << "3) Exit" << endl;

        cout << "\n==> ";
        cin >> input;

        while (input != "1" && input != "2" && input != "3")
        {
            cout << "Invalid Input!... Please try again" << endl;
            cout << "Please make another selection: ";
            cin >> input;
        }

        if (input == "1") {
            int choice;
            cout << endl << "Enter the webpage number: ";
            cin >> choice;
            while (choice < 1 || choice > pages_displayed.size()) {
                cout << "Invalid choice, try again: ";
                cin >> choice;
            }

            int idx = choice-1;
            engine.update_clicks_by_name(pages_displayed[choice-1].second); //updating the number of clicks
            cout << "Contents of " << pages_displayed[choice-1].second << ": " << endl;

        }
        else if (input == "2") {
            cin.clear();
            cin.ignore();
            return;
        }
        else if (input == "3") {
            //save files
            save_impressions_csv();
            exit(1);
        }

    } while (input != "3");

}

void increase_imp_after_displaying(vector<string> keywords) {


    for (int j=0; j<keywords.size(); j++)
        for (int i=0; i<engine.keys[keywords[j]].size(); i++)
            engine.increase_imp_by_one(engine.keys[keywords[j]][i]);

}

void update_pr(Graph&g) {

    vector<pair<int, float>> new_pr; //stores the id and the pr of the nodes

    map<string, int>::iterator it;
    for (int i=0; i<2; i++) {
        //cout << "HERE first loop" << endl;
        for (it = pages.begin(); it!= pages.end(); it++) {
            //cout << "HERE second loop" << endl;
            int curr_id = it->second;

            //cout << "Curr id: " << curr_id << endl;
            //cout << "Pages size: " << pages.size() << endl;
            //g.displayGraph();
            Graph temp = g.get_transpose();
            //temp.display();

            vector<int> nodes_pointing_to_curr = temp.get_nodes_pointing_to_v(curr_id);
            //cout << "NODES POINTING TO " << curr_id << " ARE: " << endl;
            //for (auto node: nodes_pointing_to_curr) cout << node << ", ";
            //vector<int> nodes_pointing_to_curr = g.get_nodes_pointing_to_v(curr_id); //stores the id's of the node's pointing to V

            //cout << "Current node: " << curr_id << endl;
            //cout << "SIZE is: " << nodes_pointing_to_curr.size() << endl;
            //for (auto node : nodes_pointing_to_curr) cout << "node: " << node << endl;
            float page_rank = 0.0;

           // cout << "BLHA BLAH " << engine.webpages[2].get_pr() << endl;

            //the summation
            for (int j=0; j<nodes_pointing_to_curr.size(); j++) {
                //cout << "IN THIRD LOOP" << endl;
                int curr_node_pointing = nodes_pointing_to_curr[j];
                //cout << "ID OF current node: " << curr_node_pointing << endl;
                float prev_pr = engine.get_pr_by_id(curr_node_pointing);
                //cout << "Prev pr for "<< engine.get_name_by_id(curr_id) << " is: " << prev_pr << endl;
                float temp_pr = prev_pr / g.num_edges_out(curr_node_pointing);

                page_rank+= temp_pr;
            }

            //cout << "The final page rank for: " << engine.get_name_by_id(curr_id) << " is: " << page_rank << endl;
            //cout << "PAGE RANK IS " << page_rank << endl;
            engine.update_pr_by_id(curr_id, page_rank);

            if (i == 1)
                new_pr.push_back(make_pair(curr_id, page_rank));

        }

    }

//    for (auto page : engine.webpages) {
//
//    }
//    for (int i=0; i<new_pr.size(); i++) {
//        for (auto page : engine.webpages)  {
//            if (new_pr[i].first == page.get_id())
//                page.set_pr(new_pr[i].second);
//        }
    for (int i=0; i<new_pr.size(); i++)
        cout << new_pr[i].first << ", " << new_pr[i].second << endl;

}

void update_all_scores() {

    for (int i=0; i<engine.webpages.size(); i++) {
        engine.webpages[i].calculate_score(engine.get_pr_norm());
    }
}

void save_impressions_csv() {

    fstream fout;
    fout.open("/Users/yaseenahmed/Workspace/AUC/Academics/Spring 2022/Analysis Lab/Project/Backup Recent/impressions.csv");
    //cout << "Now updating impressions" << endl;
    map<int,vector<string>>::iterator it;

    for(it = engine.index.begin();  it != engine.index.end(); ++it) {
        int i=1;
        int id = it->first;
        string name = engine.get_name_by_id(id);
        int imp = engine.imp_cnt[id];
        //cout << "Impressions of " << name << " updated to: " << imp << endl;

        if (i == pages.size())
            fout << name << "," << imp;
        else {
            fout << name << "," << imp << "\n";
            i++;
        }

    }


}