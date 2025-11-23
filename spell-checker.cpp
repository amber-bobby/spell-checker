//Amber Gill

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

void loadDictionary(TrieNode* root, const string& filename) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        insert(root, word);
    }
    file.close();
}

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

string checkWord(TrieNode* root, const string& word) {
    if (search(root, word)) {
        return word + " is correct.";
    } else {
        return word + " is incorrect. Suggestions: ...";
    }
}

int main() {
    TrieNode* root = new TrieNode();

    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");

    cout << "Search apple: " << search(root, "apple") << endl;
    cout << "Search app: " << search(root, "app") << endl;

    remove(root, "apple");
    cout << "After removing apple, search apple: " << search(root, "apple") << endl;
    cout << "Search app (should still exist): " << search(root, "app") << endl;

    return 0;
}

