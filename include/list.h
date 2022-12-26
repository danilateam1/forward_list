#include<iostream>
#include <initializer_list>
#include<vector>

template <class T>
class ForwardList {
private:
	struct Node {
		T elem = 0;
		Node* next = nullptr;
		Node() {}
		Node(T elem) : elem(elem) {}
		Node(const Node& v) {
			elem = v.elem;
			delete next;
			next = new Node();
			next = v.next;
		}
	};
	Node* first = nullptr;
	size_t size;
public:
	class iterator {
	private:
		Node* ptr;
	public:
		iterator() : ptr(nullptr) {}
		iterator(Node* ptr1) : ptr(ptr1) {}
		iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(this->ptr);
			ptr = ptr->next;
			return tmp;
		}
		iterator operator+(int n) {
			iterator tmp(this->ptr);
			for (int i = 0; i < n; ++i)
				ptr = ptr->next;
			return tmp;
		}
		T& operator*() {
			return ptr->elem;
		}
		friend bool operator!=(const iterator& x, const iterator& y) {
			return (x.ptr != y.ptr);
		}
		friend bool operator==(const iterator& x, const iterator& y) {
			return !(x != y);
		}
		Node* ptr_go() {
			return this->ptr;
		}

	};
	ForwardList() {}
	ForwardList(size_t size) {
		if (size <= 0)
			throw ("can't create list");
		first = new Node();
		this->size = size;
		Node* tmp = first;
		for (int i = 1; i < size; i++) {
			tmp->next = new Node();
			tmp = tmp->next;
		}
	}
	ForwardList(const ForwardList<T>& v) {
		this->size = v.size;
		delete first;
		Node* c = v.first;
		first = new Node(c->elem);
		Node* tmp = first;
		c = c->next;
		while (c) {
			tmp->next = new Node(c->elem);
			c = c->next;
			tmp = tmp->next;
		}
	}
	ForwardList(const std::initializer_list<T>& v) {
		delete first;
		first = new Node(*v.begin());
		Node* tmp = first;
		auto i = v.begin() + 1;
		for (i; i < v.end(); i++) {
			tmp->next = new Node(*i);
			tmp = tmp->next;
		}
		this->size = v.size();
	}
	ForwardList(ForwardList&& v) {
		Node* tmp = v.first;
		this->first = tmp;
		this->size = v.size;
		v.first = nullptr;
	}
	~ForwardList() {
		Node* tmp = first;
		while (tmp) {
			Node* tmp1 = tmp->next;
			delete[] tmp;
			tmp = tmp1;
		}
	}

	void clear() {
		Node* tmp = first;
		while (tmp) {
			Node* tmp1 = tmp->next;
			delete[] tmp;
			tmp = tmp1;
		}
	}

	const ForwardList& operator=(const ForwardList& v) {
		if (this == &v)
			return *this;
		ForwardList tmp(v);
		this->clear();
		this->first = tmp.first;
		this->size = tmp.size;
		return *this;
	}
	const ForwardList& operator=(ForwardList&& v) {
		if (this == &v)
			return *this;
		this->clear();
		this->size = v.size;
		Node* tmp = v.first;
		this->first = tmp;
		v.first = nullptr;
	}
	size_t get_size() {
		return size;
	}

	void print() {
		Node* tmp = first;
		for (iterator i = begin(); i != end(); i++) {
			std::cout << tmp->elem << "\t";
			tmp = tmp->next;
		}
	}

	bool empty() {
		return (size == 0);
	}

	void pop_front() {
		if (size == 0)
			throw("empty list");
		Node* tmp = first->next;
		delete first;
		first = tmp;
		size--;
	}

	void pop_back() {
		if (size == 0)
			throw("empty list");
		Node* tmp1 = (this->ind(size - 2)).ptr_go();
		Node* tmp = tmp1->next;
		delete tmp;
		tmp1->next = nullptr;
		size--;
	}

	void push_front(const T& val) {
		Node* tmp1 = new Node(val);
		Node* tmp2 = first;
		first = tmp1;
		first->next = tmp2;
		size++;
	}

	void push_back(T val) {
		Node* tmp = (this->pre_end()).ptr_go();
		tmp->next = new Node(val);
		size++;
	};

	iterator insert_after(iterator it, T val) {
		Node* tmp = new Node(val);
		tmp->next = (it.ptr_go())->next;
		(it.ptr_go())->next = tmp;
		size++;
		return iterator(tmp);
	}
	iterator erase_after(iterator it) {
		Node* tmp1 = it.ptr_go();
		Node* tmp2 = tmp1->next;
		tmp1->next = tmp2->next;
		delete[] tmp2;
		size--;
		return iterator(tmp1->next);
	}

	iterator begin() {
		return iterator(first);
	}
	iterator ind(int n) {
		Node* tmp = first;
		for (int i = 0; i < n; i++) {
			tmp = tmp->next;
		}
		return iterator(tmp);
	}
	iterator pre_end() {
		Node* tmp = first;
		for (int i = 1; i < size; i++) {
			tmp = tmp->next;
		}
		return iterator(tmp);
	}
	iterator end() {
		return iterator(nullptr);
	}

	std::vector<T> find_middle() {
		std::vector<T> el;
		auto ptr1 = this->begin();
		auto ptr2 = this->begin();
		auto ptr3 = ptr1;
		ptr3++;
		if (ptr3 == nullptr) {   // 1 element v liste
			el.push_back(*ptr1);
			return el;
		}
		while (true) {
			auto ptr3 = ptr2;
			ptr3++;
			if (ptr3 == nullptr) {   
				ptr1++;
				el.push_back(*ptr1);
				return el;
			}
			ptr3++;
			if (ptr3 == nullptr) {
				el.push_back(*ptr1);
				ptr1++;
				el.push_back(*ptr1);
				return el;
			}
			ptr1++;
			ptr2 + 2;
		}
	}
	
};