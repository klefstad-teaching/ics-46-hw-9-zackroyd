#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cout << word1 << ", " << word2 << ": " << msg << std::endl;
}

//The common algorithm from the linked wikipedia page in the project writeup https://en.wikipedia.org/wiki/Edit_distance#Common_algorithm
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    vector<vector<int>> matrix(str1.size() + 1, vector<int>(str2.size() + 1, 0));

    for (size_t i = 0; i <= str1.size(); ++i) matrix[i][0] = i;
    for (size_t j = 0; j <= str2.size(); ++j) matrix[0][j] = j;

    for (size_t j = 1; j <= str2.size(); ++j) {
        for (size_t i = 1; i <= str1.size(); ++i){
            int subcost = 0;
            if (str1[i - 1] != str2[j - 1]) subcost = 1;
            matrix[i][j] = min({matrix[i-1][j] + 1, matrix[i][j-1] + 1, matrix[i-1][j-1] + subcost});
        }
    }
    //std::cout << "Distance Between " << str1 << " and " << str2 << ": " << matrix[str1.size()][str2.size()] << std::endl;
    return matrix[str1.size()][str2.size()] <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> get_neighbors(string word) {
    char REPLACEMENT = '*';
    vector<string> res;
    int wordSize = word.size();
    for (int i = 0; i < wordSize; ++i) {
        string curr = word;
        curr[i] = REPLACEMENT;
        res.push_back(curr);
    }
    for (int i = 0; i < wordSize; ++i) {
        string curr = word.substr(0, 0 + i) + REPLACEMENT + word.substr(i);
        res.push_back(curr);
    }
    res.push_back(word + REPLACEMENT);
    return res;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    map<string, set<string>> neighbors;
    for (string word : word_list) for (string n : get_neighbors(word)) neighbors[n].insert(word);
    set<string> visited;
    queue<vector<string>> qV;
    qV.push(vector<string>{begin_word});
    visited.insert(begin_word);

    while (!qV.empty()) {
        vector<string> currVec = qV.front();
        qV.pop();
        string last_word = currVec.back();
        for (string n : get_neighbors(last_word)) {
            for (string word : neighbors[n]) {
                if (visited.contains(word)) continue;
                visited.insert(word);
                //std::cout << "Last word: " << last_word << " Adjacent word: " << word << std::endl;  
                vector<string> newVec = currVec;
                newVec.push_back(word);
                if (word == end_word) return newVec;
                qV.push(newVec);
            }
        }
    }

    return vector<string>{};
}
void load_words(set<string> & word_list, const string& file_name) {
    string line;
    ifstream fin;
    fin.open(file_name);
    while(getline(fin, line)) word_list.insert(line);
}


void print_word_ladder(const vector<string>& ladder) {
    for (string s : ladder) std::cout << s << ' ';
    std::cout << std::endl;
}


void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
