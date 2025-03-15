#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << endl;
    cerr << "Word 1: " << word1 << endl;
    cerr << "Word 2: " << word2 << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d){
    size_t len1 = str1.length();
    size_t len2 = str2.length();

    if (abs(static_cast<int>(len1 - len2)) > d) {
        return false;
    }
    if (len1 == 0) return len2 <= static_cast<size_t>(d);
    if (len2 == 0) return len1 <= static_cast<size_t>(d);
    if (len1 == len2) {
        // If same length check if they differ by at most one character
        int diff = 0;
        for (size_t i = 0; i < len1; ++i) {
            if (str1[i] != str2[i]) {
                diff++;
                if (diff > d) return false;
            }
        }
        return true;
} else if (len1 == len2 + 1 || len2 == len1 + 1) {
        // If lengths differ by 1, check if one is a substring of the other with one char inserted
        const string& shorter = (len1 < len2) ? str1 : str2;
        const string& longer = (len1 < len2) ? str2 : str1;
        
        size_t i = 0, j = 0;
        bool skipped = false;
        
        while (i < shorter.length() && j < longer.length()) {
            if (shorter[i] == longer[j]) {
                i++;
                j++;
            } else if (!skipped) {
                // Skip one character in the longer string
                skipped = true;
                j++;
            } else {
                return false;
            }
        }
        return true;
    } 
    return false;
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    // Set of visited words
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = ladder.back();
        
        // Check if end word is adjacent to the last word
        if (is_adjacent(last_word, end_word)) {
            ladder.push_back(end_word);
            return ladder;
        }
        
        // try all words in dictionary
       for (const string& word : word_list) {
    if (!visited.count(word) && is_adjacent(last_word, word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
}
void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        cerr << "Error: Cannot open dictionary file " << file_name << endl;
        return;
    }
    
    string word;
    while (in >> word) {
        transform(word.begin(), word.end(), word.begin(),::tolower);
        word_list.insert(word);
    }
    
    in.close();
}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (const auto& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}