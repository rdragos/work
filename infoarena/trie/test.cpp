#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <string>
#include <set>
#include <stack>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;


struct Node {
    Node *letter[26]; 
    int cnt, neighbours;
    
    Node() {
        cnt = neighbours = 0;
        memset(letter, 0, sizeof(letter));
    }
};


int convert(char x) {
    return x - 'a';
}
void trie_insert(Node *T, size_t pos, string &word) {
    if (pos >= word.size()) {
        T -> cnt += 1;
    } else {
        int _next = convert(word[pos]);
        if (T -> letter[_next] == 0) {
            T -> letter[_next] = new Node();
        }
        T -> neighbours += 1;
        trie_insert(T -> letter[_next], pos + 1, word);
    }
}
int trie_delete(Node *T, size_t pos, string &word) {
    if (pos >= word.size()) {
        T -> cnt -= 1;
    } else {
        int _next = convert(word[pos]);
        if (trie_delete(T -> letter[_next], pos + 1, word)) {
            T -> letter[_next] = 0;
        }
        T -> neighbours -= 1;
    }
    if (T -> cnt == 0 && T -> neighbours == 0) {
        delete T; return 1;
    }
    return 0;
}
int trie_frequence(Node *T, size_t pos, string& word) {
    if (pos >= word.size()) {
        return T -> cnt;
    } else {
        int _next = convert(word[pos]);
        if (T -> letter[_next]) {
            return trie_frequence(T -> letter[_next], pos + 1, word);
        } else {
            return 0;
        }
    }
}
int trie_lcp(Node *T, size_t pos, string &word) {
    if (pos >= word.size()) {
        return pos;
    } else {
        int _next = convert(word[pos]);
        if (T -> letter[_next] == 0) {
            return pos;
        }
        return trie_lcp(T -> letter[_next], pos + 1, word);
    }
}
int main() {
    ifstream cin("trie.in");
    ofstream cout("trie.out");
    

    Node *Trie = new Node();
    
    string word;
    int operation;

    Trie -> neighbours = 1;
    
    while(cin >> operation >> word) {
        if (operation == 0) {
            trie_insert(Trie, 0, word);
        } else if (operation == 1) {
            trie_delete(Trie, 0, word);
        } else if(operation == 2) {
            cout << trie_frequence(Trie, 0, word) << "\n";
        }else if(operation == 3) {
            cout << trie_lcp(Trie, 0, word) << "\n";
        }
    }
    return 0;
}
