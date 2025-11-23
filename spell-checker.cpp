//Amber Gill

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct TrieNode{

    TrieNode* children[26];
    bool isEnd;

    TrieNode(){
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;}
        isEnd = false;
        
    }
};



void insert(TrieNode* root, const string& word){
    TrieNode* node = root;

    for (int i = 0; i < word.size(); i++) {
    int index = word[i] - 'a';
    if (node->children[index] == nullptr)
        node->children[index] = new TrieNode();
    node = node->children[index];
    }
    node->isEnd = true;
}

bool search(TrieNode* root, const string& word) {
    TrieNode* node = root;

    for (int i = 0; i < word.size(); i++) {
        int index = word[i] - 'a';
        if (node->children[index] == nullptr){
            return false;}
        node = node->children[index];    
    }
    
    return node->isEnd;
}

bool remove(TrieNode* node, const string& word, int depth = 0) {
    if (node == nullptr) {
        return false;
    }

    if (depth == word.size()) {
        if (node->isEnd == false) {
            return false; 
        }

        node->isEnd = false;

        bool hasChildren = false;
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                hasChildren = true;
                break;
            }
        }

        if (hasChildren == false) {
            return true; 
        } else {
            return false; 
        }
    }

    
    int index = word[depth] - 'a';
    if (node->children[index] == nullptr) {
        return false; 
    }

    bool shouldDelete = remove(node->children[index], word, depth + 1);

    if (shouldDelete == true) {
        delete node->children[index];
        node->children[index] = nullptr;

        bool hasChildren = false;
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                hasChildren = true;
                break;
            }
        }

        if (node->isEnd == false && hasChildren == false) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}
void loadDictionary(TrieNode* root, const string& filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        insert(root, word);
    }
    file.close();
}

string checkWord(TrieNode* root, const string& word) {
    if (search(root, word)) {
        return word + " is correct.";
    } else {
        return word + " is incorrect. Suggestions: ...";
    }
}

vector<string> getSuggestions(TrieNode* root, const string& word) {
    vector<string> suggestions;
    string alphabets = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < word.size(); i++) {
        string temp = word;
        for (int j = 0; j < alphabets.size(); j++) {
            char newChar = alphabets[j];
            temp[i] = newChar;
            if (search(root, temp) && temp != word) {
                suggestions.push_back(temp);
            }
        }
    }
    return suggestions;
}

void displayAllWords(TrieNode* node, string currentWord = "") {
    if (node == nullptr) return;

    if (node->isEnd) {
        cout << currentWord << endl;
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            char nextChar = 'a' + i;
            displayAllWords(node->children[i], currentWord + nextChar);
        }
    }
}


int main() {
    TrieNode* root = new TrieNode();

    loadDictionary(root, "dict.txt");

    int choice;
    string word;

    cout << "Interactive Trie Spell Checker\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Remove a word\n";
        cout << "4. Suggested corrections for a word\n";
        cout << "5. Display all words\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word to insert: ";
                cin >> word;
                insert(root, word);
                cout << word << " inserted.\n";
                break;

            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                if (search(root, word))
                    cout << word << " exists in the trie.\n";
                else
                    cout << word << " not found.\n";
                break;

            case 3:
                cout << "Enter word to remove: ";
                cin >> word;
                if (remove(root, word))
                    cout << word << " removed from the trie.\n";
                else
                    cout << word << " not found or cannot remove.\n";
                break;
            
            case 4:
                cout << "Enter word to get suggestions: ";
                cin >> word;
                getSuggestions(root, word);
                break;

            case 5:
                displayAllWords(root);  
                break;

            case 6:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

