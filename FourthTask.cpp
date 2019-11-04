#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <stack>
#include <random>

using namespace std;

template<typename Stack>
void moveTop(Stack& source, Stack& dest) {
	dest.push(source.top());
	source.pop();
}

template<typename Stack>
void moveStack(Stack& dest, Stack& source) {
	while (dest.size()) moveTop(dest, source);
}

template<typename T>
class stackm
{
private:
	size_t count;
	T* data;
public:
	stackm(size_t capacity = 50000);
	~stackm();
	void push(const T& value);
	void pop();
	T& top() const;
	size_t size() const;
	void myswap( stackm<T>& s);
};

template <typename T>
stackm<T>::stackm(size_t capacity) {
	count = 0;
	data = new T[capacity];
}

template <typename T>
stackm<T>::~stackm() {
	delete[] data;
}

template <typename T>
void stackm<T>::push(const T& value) {
	data[count++] = value;
}

template <typename T>
void stackm<T>::pop() {
	--count;
}

template <typename T>
T& stackm<T>::top() const {
	return data[count - 1];
}

template <typename T>
size_t stackm<T>::size() const {
	return count;
}

template <typename T>
void stackm<T>::myswap( stackm<T>& s){
	swap(data, s.data);
	swap(count, s.count);
}

template<typename Stack>
void packet_test(size_t m, size_t n, Stack& s)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) s.push(j);
		for (int k = 0; k < n; k++) s.pop();
	}
}

template <typename Stack>
bool isStackEqual(const Stack& firstStack, const Stack& secondStack) {
	if (firstStack.size() != secondStack.size()) return false;
	bool flag = false;
	while (firstStack.size() != 0 || secondStack.size() != 0) {
		if (firstStack.top() == secondStack.top()) {
			flag = true;
			firstStack.pop();
			secondStack.pop();
		}
		else {
			return false;
		}
	}
	return flag;
}

template <typename Stack>
void prob_packet_test(size_t m, size_t n, double p, Stack &s) {
	p *= 100;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, 100);
	for (int i = 0; i < m; i++) {
		if (dist(mt) <= p) {
			for (int j = 0; j < n; j++) {
				s.push(j);
			}
		}
		else if (s.size() != 0) {
			for (int j = 0; j < n; j++) {
				s.pop();
			}
		}
	}
}

template <typename T>
struct Node {
	T data;
	Node <T> *next;
	Node(const T& newData, Node<T> *nextnode) {
		data = newData;
		next = nextnode;
	}
};

template <typename T>
class stackList {
private:
	size_t count;
	Node<T> *currentTop;
public:
	stackList();
	~stackList();
	void push(const T& value);
	void pop();
	size_t size();
	T& top();
	void myswap(stackList<T>& s);
};

template<typename T>
stackList<T>::stackList() {
	count = 0;
	currentTop = nullptr;
}

template<typename T>
stackList<T>::~stackList() {
	while (size())
		pop();
}

template<typename T>
void stackList<T>::push(const T& value) {
	count++;
	currentTop = new Node <T>(value, currentTop);;
}

template<typename T>
void stackList<T>::pop() {
	count--;
	auto tmpTop = currentTop->next;
	delete currentTop;
	currentTop = tmpTop;
}

template<typename T>
T& stackList<T>::top() {
	return currentTop->data;
}

template<typename T>
size_t stackList<T>::size() {
	return count;
}

template <typename T>
void stackList<T>::myswap(stackList<T>& s) {
	swap(currentTop, s.currentTop);
	swap(count, s.count);
}

template<typename Stack>
void sortStack(Stack& s) {
	Stack tmp,result;
	auto t = s.top(),
		 t2 = s.top();
	while (s.size()) {
		t = s.top();
		s.pop();
		tmp.push(t);
		while (s.size())
		{
			t2 = s.top();
			s.pop();
			if (t2 > t) t = t2;
			tmp.push(t2);
		}
		while (tmp.size())
		{
			t2 = tmp.top();
			tmp.pop();
			(t2 == t) ? result.push(t2) : s.push(t2);
		}
	}
	while (result.size()) {
		s.push(result.top());
		result.pop();
	}
}

template<typename Stack>
void sortStackTwo(Stack& s) {
	if (s.size() < 2) return;
	Stack tmp, result;
	while (s.size()) {
		auto tmpMax = s.top();
		s.pop();
		while (s.size()) {
			if (s.top() >= tmpMax) {
				tmp.push(tmpMax);
				tmpMax = s.top();
			}
			else {
				moveTop(s, tmp);
			}
		}
		result.push(tmpMax);
		while (tmp.size()) {
			moveTop(tmp, s);
		}
	}
	while (result.size()) {
		moveTop(result, tmp);
	}
}

template<typename Stack>
void quickSortStack(Stack& s) {
	Stack l,g,e;
	mt19937_64 mtrand;
	if (s.size() < 2)return;
	Stack tmp2;
	auto index = mtrand() % s.size();
	for (auto i = 0; i < index; i++) {
		moveTop(s, tmp2);
	}
	auto tmp = s.top();
	moveStack(tmp2, s);
	while (s.size()) {
		if (tmp == s.top()) { 
			moveTop(s, e);
		}
		else {
			if (tmp < s.top()) {
				moveTop(s, l);
			}
			else {
				moveTop(s, g);
			}
		}
	}
	if (g.size()) quickSortStack(g);
	if (l.size()) quickSortStack(l);
	while (e.size()) {
		moveTop(e, g);
	}
	while (l.size()) {
		moveTop(l, e);
	}
	while (g.size()) {
		moveTop(g, e);
	}
	while (e.size()) {
		moveTop(e, s);
	}
} 

template <typename Stack>
void extract_sorted_segment(Stack& s, Stack& result) {
	if (!s.size()) return;
	auto tmp = s.top();
	result.push(s.top());
	s.pop();
	while (s.size() && tmp <= s.top()) {
		result.push(s.top());
		tmp = s.top();
		s.pop();
	}
}

template <typename Stack>
void extracted_sorted_segment(Stack& s, Stack& result) {
	if (!s.size()) return;
	moveTop(s, result);
	while (s.size() && s.top()>=result.top()) {
		moveTop(s, result);
	}
}

template <typename Stack>
void merge(Stack& s1, Stack& s2, Stack& result) {
	Stack tmp;
	while(s1.size() && s2.size()){
		if (s1.top() >= s2.top()) {
			moveTop(s1, tmp);
		}
		else{
			moveTop(s2, tmp);
		}
	}
	while (s1.size()) {
		moveTop(s1, tmp);
	}
	while(s2.size()) {
		moveTop(s2, tmp);
	}
	while (tmp.size()) {
		moveTop(tmp, result);
	}
}
template <typename Stack>
void merge_sort(Stack& s) {
	if (s.size() < 2)return;
	Stack s1, s2, result;
	auto count=0;
	do {
		while (s.size()) {
			extracted_sorted_segment(s, s1);
			extracted_sorted_segment(s, s2);
			merge(s1, s2, result);
			count++;
		}
		count = 0;
		s.myswap(result);
	} while (count > 1);
}

template <typename Stack>
void fill_stack(Stack& s, const vector<int> &data) {
	for (auto elem : data) {
		s.push(elem);
	}
}

template <typename F>
size_t getexectime(F f) {
	auto s = GetTickCount();
	f();
	return GetTickCount() - s;
}

int main()
{
	mt19937_64 mtrand;
	stackm<int> test3;
	stackList<int> t3;
	stack<int> t4;
	int N = 50000;
	vector<int> data(N);
	generate(begin(data), end(data), []() {return rand(); });
	fill_stack(test3, data);
	fill_stack(t3, data);
	fill_stack(t4, data); 
	cout << "stackArray QuickSort: " << getexectime([&]() {quickSortStack(test3); }) << endl;
	cout << "stackArray mergeSort: " << getexectime([&]() {merge_sort(test3); }) << endl;
	cout << "stackList QuickSort: " << getexectime([&]() {quickSortStack(t3); }) << endl;
	cout << "stackList mergeSort: " << getexectime([&]() {merge_sort(t3); }) << endl;
	stackm<int> test4;
	stackList<int> t44;
	stack<int> t5;
	vector<int> data1(N);
	for (int i = 0; i < data1.size()/2; i++) {
		data1[i] = i;
	}
	for (int i = data1.size() / 2; i < data1.size(); i++) {
		data1[i] = rand();
	}
	generate(begin(data), end(data), []() {return rand(); });
	fill_stack(test4, data1);
	fill_stack(t44, data1);
	fill_stack(t5, data1);
	cout << "stackArray QuickSort: " << getexectime([&]() {quickSortStack(test4); }) << endl;
	cout << "stackArray mergeSort: " << getexectime([&]() {merge_sort(test4); }) << endl;
	cout << "stackList QuickSort: " << getexectime([&]() {quickSortStack(t44); }) << endl;
	cout << "stackList mergeSort: " << getexectime([&]() {merge_sort(t44); }) << endl;
	stackm<int> tm1;
	stackList<int> tl1;
	stack<int> t55;
	vector<int> data2(N);
	generate(begin(data2), end(data2), []() {return rand(); });
	fill_stack(tm1, data2);
	fill_stack(tl1, data2);
	fill_stack(t55, data2);
	cout << "stackArray QuickSort: " << getexectime([&]() {quickSortStack(tm1); }) << endl;
	cout << "stackArray mergeSort: " << getexectime([&]() {merge_sort(tm1); }) << endl;
	cout << "stackList QuickSort: " << getexectime([&]() {quickSortStack(tl1); }) << endl;
	cout << "stackList mergeSort: " << getexectime([&]() {merge_sort(tl1); }) << endl; 
}
