#include "ladder.h"

int main() {
    string word1;
    string word2;
    set<string> word_list;
    std::cout << "Enter the start word: ";
    std::cin >> word1;
    std::cout << "Enter the end word: ";
    std::cin >> word2;
    if (word1 == word2) error(word1, word2, "Start and End words must be different!");
    load_words(word_list, "src/words.txt");
    if (!word_list.contains(word2)) error(word1, word2, "End Word is not in words list!");
    vector<string> word_ladder = generate_word_ladder(word1, word2, word_list);
    if (word_ladder.size() == 0) {
        std::cout << "No word ladder found." << std::endl;
        return 0;
    }
    std::cout << "Word ladder found: ";
    print_word_ladder(word_ladder);
    //verify_word_ladder();
    return 0;
}