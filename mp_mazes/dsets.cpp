/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        _elems.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (_elems[elem] < 0) {
        return elem;
    }
    return find(_elems[elem]);
}

void DisjointSets::setunion(int a, int b) {
    int first = find(a);
    int second = find(b);
    if (first == second) {
        return;
    }
    if (_elems[first] > _elems[second]) {
        _elems[second] += _elems[first];
        _elems[first] = second;
    } else {
        _elems[first] += _elems[second];
        _elems[second] = first;
    }
}

int DisjointSets::size(int elem) {
    elem = find(elem);
    return -_elems[elem];
}