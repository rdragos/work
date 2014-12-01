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


class Tree {

  struct Node {
    Node* left;
    Node* right;
    int val;

    Node() {
      val = 0;
      left = right = NULL;
    }
    Node(int _val) {
      val = _val;
    }
  };
  Node* root;

  public:
    Tree(const vector <int>&input) {
      construct(&root, 0, input);
    }
    void flatten() {
      pair<Node*, Node*> head = _flatten(&root);
      for (Node*p = head.first; p; p = p->left) {
        cerr << p->val << " ";
      }

      cerr << "\nlol\n";
      _print(root);
    }
    void print() {
      _print(root);
    }
  private:
    void construct(Node** cur, int idx, const vector<int>&input) {
      vector<Node*> all(input.size());

      all[1] = new Node(input[1]);
      for (int i = 1; i < input.size(); ++i) {
        if (2 * i < input.size()) {
          all[2 * i] = new Node(input[2 * i]);
          all[i]->left = all[2 * i];
        }
        if (2 * i + 1 < input.size()) {
          all[2 * i + 1] = new Node(input[2 * i + 1]);
          all[i]->right = all[2 * i + 1];
        }
      }
      *cur = all[1];
    }

    pair<Node*, Node*> _flatten(Node** cur) {
      Node* first = *cur;

      if (first ==NULL) {
        Node *x = NULL;
        return make_pair(x,x);
      }
      if (first) {
        if (first->left == NULL && first->right == NULL) {
          return make_pair(first, first);
        }
      }
      pair<Node*, Node*> res_left;
      pair<Node*, Node*> res_right;

      if (first->left) {
        res_left = _flatten(&first->left);
      }
      if (first->right) {
        res_right = _flatten(&first->right);
      }
      first->right = NULL;
      res_left.second->left = res_right.first;
      return make_pair(*cur, res_right.second);
    }
    void _print(Node* root) {
      if (root->left) {
        cerr << "L: of " << root->val << " is: " << root->left->val << "\n";
        _print(root->left);
      }
      if (root->right) {
        cerr << "R: of " << root->val << " is: " << root->right->val << "\n";
        _print(root->right);
      }
    }

};
int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("test.in");
  ofstream cout("test.out");
#endif

  int N; cin >> N;
  vector <int> v(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> v[i];
  }
  Tree T(v);
  T.print();
  T.flatten();
  return 0;
}
