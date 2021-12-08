#ifndef DONE_H
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#define DONE_H
#endif

using namespace std;

template<class T>
ostream &operator<<(ostream &, const vector<T> &);

int GetOptions(int, char **, int *, int *);
