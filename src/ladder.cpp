#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cout << word1 << ", " << word2 << ": " << msg << std::endl;
}

//The common algorithm from the linked wikipedia page in the project writeup https://en.wikipedia.org/wiki/Edit_distance#Common_algorithm
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    vector<vector<int>> matrix(str1.size(), vector<int>(str2.size(), 0));

    for (size_t i = 0; i < str1.size(); ++i) matrix[i][0] = i;

    for (size_t j = 1; j < str2.size(); ++j) {
        for (size_t i = 1; i < str1.size(); ++i){
            int subcost = 0;
            if (str1[i] != str2[j]) subcost = 1;
            matrix[i][j] = min({matrix[i-1][j] + 1, matrix[i][j-1] + 1, matrix[i-1][j-1] + subcost});
        }
    }
    std::cout << "Distance between " << str1 << " and " << str2 << ": " << matrix[str1.size() - 1][str2.size() - 1] << std::endl; 
    return matrix[str1.size() - 1][str2.size() - 1] == d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


