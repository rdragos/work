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
#include <deque>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;


struct Node {
  int val;
  Node *next;
  Node(int _val) {
    val = _val;
    next = NULL;
  }
  Node() {
    val = 0; next = NULL;
  }
};

class LinkedList {
  Node* Head;

  void reverse(Node** current) {
    if (*current == NULL) {
      return ;
    }
    Node* first = (*current);
    Node* rest = first->next;
    if (rest == NULL) {
      return ;
    }
    //cerr << "before: " << rest->val << "\n";
    reverse(&rest);
    first->next->next = first;
    first->next = NULL;
    //cerr << "after: " << rest->val << "\n";
    *current = rest;
  }
  public:
  LinkedList(const vector <int>&v) {
    Head = new Node;
    Node* p = Head;
    for(const auto&el : v) {
      p->next = new Node(el);
      p = p->next;
    }
  }
  void Reverse() {
    for (Node* p = Head; p; p = p->next) {
      cerr << p->val << " " ;
    }
    cerr << "\n";
    reverse(&Head);
    cerr << "\n";
    for (Node*p = Head; p; p = p->next) {
      cerr << p->val << " " ;
    }
    cerr << "\n";
  }
};
int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("test.in");
  ofstream cout("test.out");
#endif

  int N; cin >> N;

  vector <int> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
  }
  LinkedList L(v);
  L.Reverse();
  return 0;
}
