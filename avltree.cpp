#include<iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

template <typename T>
class Node {
private:
	T el;
	Node<T>* left;
	Node<T>* right;
	int height;
public:
	Node() { left = right = nullptr; height = -1; }
	Node(T d) { left = right = nullptr; height = 0; el = d; }
	~Node() { el = -9999; left = right = nullptr; height = -1; }
	friend class Adelson_Velskii_Landis_Tree<T>;
};

template <typename T>
class Adelson_Velskii_Landis_Tree {
private:
	Node<T>* root;
public:
	Adelson_Velskii_Landis_Tree() { root = new Node<T>; }

	Adelson_Velskii_Landis_Tree(T d) { root = new Node<T>(d); }

	void deleteThisDamnTree(Node<T>* x) {
		if (x == nullptr) return;
		deleteThisDamnTree(x->left);
		deleteThisDamnTree(x->right);
		delete x;
	}
	~Adelson_Velskii_Landis_Tree() {
		deleteThisDamnTree(root);
	}
	Node<T>* insert(T x, Node<T>* t) {
		if (t == nullptr) t = new Node<T>(x);
		else if (x < t->data) {
			t->left = insert(x, t->left);
			if (height(t->left) - height(t->right) == 2) {
				if (x < t->left->data) t = singleRightRotate(t);
				else t = doubleRightRotate(t);
			}
		}
		else if (x > t->data) {
			t->right = insert(x, t->right);
			if (height(t->right) - height(t->left) == 2) {
				if (x > t->right->data) t = singleLeftRotate(t);
				else t = doubleLeftRotate(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	void insert(T x) {
		root = insert(x, root);
	}

	Node<T>* singleRightRotate(Node<T>*& t) {
		Node<T>* temp = t->left;
		t->left = temp->right;
		temp->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		temp->height = max(height(temp->left), t->height) + 1;
		return temp;
	}

	Node<T>* singleLeftRotate(Node<T>*& t) {
		Node<T>* temp = t->right;
		t->right = temp->left;
		temp->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		temp->height = max(height(t->right), t->height) + 1;
		return temp;
	}

	Node<T>* doubleLeftRotate(Node<T>*& t) {
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	Node<T>* doubleRightRotate(Node<T>*& t) {
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	Node<T>* findMin(Node<T>* t) {
		if (t == nullptr) return nullptr;
		else if (t->left == nullptr) return t;
		else return findMin(t->left);
	}

	Node<T>* findMax(Node<T>* t) {
		if (t == nullptr) return nullptr;
		else if (t->right == nullptr) return t;
		else return findMax(t->right);
	}

	Node<T>* remove(T x, Node<T>* t) {
		Node<T>* temp;
		// Element not found
		if (t == nullptr) return nullptr;
		// Searching for element
		else if (x < t->data) t->left = remove(x, t->left);
		else if (x > t->data) t->right = remove(x, t->right);

		// Element found
		// With 2 children
		else if (t->left && t->right) {
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = remove(t->data, t->right);
		}
		// With one or zero child
		else {
			temp = t;
			if (t->left == nullptr) t = t->right;
			else if (t->right == nullptr) t = t->left;
			delete temp;
		}
		if (t == nullptr) return t;

		t->height = max(height(t->left), height(t->right)) + 1;

		// If node is unbalanced
		// If left node is deleted, right case
		if (height(t->left) - height(t->right) == 2) {
			// right right case
			if (height(t->left->left) - height(t->left->right) == 1) return singleLeftRotate(t);
			// right left case
			else return doubleLeftRotate(t);
		}
		// If right node is deleted, left case
		else if (height(t->right) - height(t->left) == 2) {
			// left left case
			if (height(t->right->right) - height(t->right->left) == 1) return singleRightRotate(t);
			// left right case
			else return doubleRightRotate(t);
		}
		return t;
	}

	void remove(int x) {
		root = remove(x, root);
	}

	int height(Node<T>* t) {
		return (t == nullptr ? -1 : t->height);
	}

	int getBalance(Node<T>* t) {
		if (t == nullptr) return 0;
		else return height(t->left) - height(t->right);
	}

	void inOrderTraversal(Node<T>* t) {
		if (t == nullptr) return;
		inOrderTraversal(t->left);
		cout << t->el << " ";
		inOrderTraversal(t->right);
	}

	void display() {
		inOrderTraversal(root);
		cout << endl;
	}
};

int main() {
	Adelson_Velskii_Landis_Tree<int> t;
	t.insert(20);
	t.insert(25);
	t.insert(15);
	t.insert(10);
	t.insert(30);
	t.insert(5);
	t.insert(35);
	t.insert(67);
	t.insert(43);
	t.insert(21);
	t.insert(10);
	t.insert(89);
	t.insert(38);
	t.insert(69);
	t.display();
	t.remove(5);
	t.remove(35);
	t.remove(65);
	t.remove(89);
	t.remove(43);
	t.remove(88);
	t.remove(20);
	t.remove(38);
	t.display();
}
