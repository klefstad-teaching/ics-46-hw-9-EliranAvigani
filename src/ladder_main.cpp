#include "ladder.h"
#include <algorithm>
int main() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    cout << "Word Ladder Generator" << endl;
    cout << "---------------------" << endl;
    string begin_word, end_word;
    
    cout << "Enter start word: ";
    cin >> begin_word;
    
    cout << "Enter end word: ";
    cin >> end_word;

    transform(begin_word.begin(), begin_word.end(), begin_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);

    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must be different");
        return 1;
    }

    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word must be in the dictionary");
        return 1;
    }
    
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    
    if (ladder.empty()) {
        cout << "No word ladder exists between \"" << begin_word << "\" and \"" 
             << end_word << "\"." << endl;
    } else {
        cout << "Found word ladder:" << endl;
        print_word_ladder(ladder);
    }
    
    return 0;
}