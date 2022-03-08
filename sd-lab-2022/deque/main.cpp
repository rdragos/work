#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define pb push_back

#define mp make_pair
#define f first
#define s second
#define ll long long

using namespace std;

struct Entry {
  ll value;
  Entry *next;
  Entry *prev;

  Entry(ll _value) : value(_value){};
};

struct Deque {
  Entry *c_begin;
  Entry *c_end;

  int _size;

  Deque() : _size(0) { c_begin = c_end = NULL; }

  void push_back(ll item) {
    Entry *entry = new Entry(item);

    if (c_end == NULL) {
      c_begin = c_end = entry;
    } else {
      c_end->next = entry;
      entry->prev = c_end;
      c_end = entry;
    }
    _size += 1;
  }

  void push_front(ll item) {
    Entry *entry = new Entry(item);
    if (c_begin == NULL) {
      c_begin = c_end = entry;
    } else {
      c_begin->prev = entry;
      entry->next = c_begin;
      c_begin = entry;
    }
    _size += 1;
  }

  void pop_back() {
    if (_size == 0) {
      throw runtime_error("omg");
    } else {
      Entry *tmp = c_end;
      c_end = c_end->prev;
      delete tmp;
    }
  }

  int back() { return c_end->value; };

  int front() { return c_begin->value; };

  int size() { return _size; }
};

int main() {
  ifstream cin("test.in");
  ofstream cout("test.out");

  Deque D;
  D.push_back(1);
  assert(D.front() == D.back());
  D.pop_back();
  D.push_front(1000);
  assert(D.front() == 1000);

  return 0;
}
