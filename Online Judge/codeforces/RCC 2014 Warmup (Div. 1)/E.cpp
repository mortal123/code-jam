#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

const int N = 1111;

struct Node {
	int a, b;
	Node() {
		a = 0, b = 0;
	}
	Node(int x) {
		a = x, b = x;
	}
};

int main() {
	Node* a = new Node[5];
	for(int i = 0; i < 5; i++) {
		a[i] = Node(3);
	} 
	printf("%d\n", a[3].a);
	return 0;
} 
