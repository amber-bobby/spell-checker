//Amber Gill
#include <iostream>
#include <string>

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
        if (node->children[i] == nullptr)
            node->children[i] = new TrieNode();
        node = node->children[i];
    }

    node->isEnd = true;
}

bool search(TrieNode* root, const string& word) {
    TrieNode* node = root;

    for (int i = 0; i < word.size(); i++) {
        if (node->children[i] == nullptr)
            return false;
        node = node->children[i];
    }

    return node->isEnd;
}
