#include <iostream>

class MyList {
private:
	class Node {  //private internal class of node of list
	private:
		char value;  //value is symbol
		Node* next;  //pointer to the next node
		Node* prev;  //pointer to the previous node
	public:
		Node() {  //constructor without value of node
			this->value = NULL;
			this->next = nullptr;
			this->prev = nullptr;
		};
		Node(char ch) {  //constructor with value of node
			this->value = ch;
			this->next = nullptr;
			this->prev = nullptr;
		};
		~Node() = default;  //default destructor
		Node* getPrev() {  //get previous node
			return prev;
		}
		Node* getNext() {  //get next node
			return next;
		}
		char getValue() {  //get value of node
			return value;
		}
		void setPrev(Node* prev) { //set previous node
			this->prev = prev;
			if (prev != nullptr)
				prev->next = this;
		}
		void setNext(Node* next) {  //set next node
			this->next = next;
			if (next != nullptr)
				next->prev = this;
		}
		void setValue(char ch) {  //set value of node
			this->value = ch;
		}
	};
	Node* head;  //head of list
	size_t length;  //size
public:
	MyList() {  //constructor without first node
		this->head = new Node();
		this->length = 0;
	}
	MyList(char ch) {  //constructor with first node
		this->head = new Node(ch);
		this->length = 1;
	}
	~MyList() {  //destructor of list
		if (length == 0 || length == 1) {
			delete head;
		}
		else {
			auto nextNode = head->getNext();
			for (size_t i = 1; i < length; i++) {
				delete nextNode->getPrev();
				nextNode = nextNode->getNext();
			}
			delete nextNode;
		}
		length = NULL;
	}
	void push_back(char ch) {  //pushing symbol in back of list 
		if (length == 0) {
			head->setValue(ch);
		}
		else {
			auto pushNode = new Node(ch);
			auto node = head;
			for (size_t i = 0; i < length - 1; i++) {
				node = node->getNext();
			}
			node->setNext(pushNode);
		}
		++length;
	}
	void push_front(char ch) {  //pushing symbol in front of list
		if (length == 0) {
			head->setValue(ch);
		}
		else {
			auto pushNode = new Node(ch);
			head->setPrev(pushNode);
			head = head->getPrev();
		}
		++length;
	}
	void pop_back() {  //removing last node of list
		if (length == 0) {
			return;
		}
		else if (length == 1) {
			delete head;
			head = new Node();
		}
		else {
			auto popNode = head;
			for (size_t i = 0; i < length - 1; i++) {
				popNode = popNode->getNext();
			}
			auto prevNode = popNode->getPrev();
			delete popNode;
			prevNode->setNext(nullptr);
		}
		--length;
	}
	void pop_front() {  //removing first node of list
		if (length == 0) {
			return;
		}
		else {
			auto newHead = head->getNext();
			delete head;
			head = newHead;
			--length;
		}
	}
	void insert(char ch, size_t index) {  //insert symbol 'ch' in list in the position of 'index'
		if (index == 0) {
			push_front(ch);
		}
		else if (index == length) {
			push_back(ch);
		}
		else if (index > length) {
			return;
		}
		else {
			auto node = new Node(ch);
			auto prevNode = head;
			for (size_t i = 1; i < index; i++) {
				prevNode = prevNode->getNext();
			}
			auto nextNode = prevNode->getNext();
			prevNode->setNext(node);
			nextNode->setPrev(node);
			++length;
		}
	}
	char at(size_t index) {  //get symbol on position 'index' of list
		if (length == 0 || index >= length) {
			return NULL;
		}
		else {
			auto node = head;
			for (size_t i = 0; i < index; i++) {
				node = node->getNext();
			}
			return node->getValue();
		}
	}
	void remove(size_t index) {  //remove symbol on position 'index' of list
		if (index == 0) {
			pop_front();
		}
		else if (index == length - 1) {
			pop_back();
		}
		else if (index >= length) {
			return;
		}
		else {
			auto prevNode = head;
			for (size_t i = 1; i < index; i++) {
				prevNode = prevNode->getNext();
			}
			auto nextNode = prevNode->getNext()->getNext();
			delete prevNode->getNext();
			prevNode->setNext(nextNode);
			nextNode->setPrev(prevNode);
			--length;
		}
	}
	size_t getSize() {  //getting size of list
		return length;
	}
	void print_to_console() {  //printing all symbols of list in console with delimiter ' '
		if (length == 0) {
			std::cout << " " << std::endl;
			return;
		}
		auto node = head;
		std::cout << node->getValue() << " ";
		for (size_t i = 1; i < length; i++) {
			node = node->getNext();
			std::cout << node->getValue() << " ";
		}
		std::cout << std::endl;
	}
	void clear() {  //removing all symbols of list
		if (length == 0) {
			return;
		}
		else if (length == 1) {
			delete head;
		}
		else {
			auto nextNode = head->getNext();
			for (size_t i = 1; i < length; i++) {
				delete nextNode->getPrev();
				nextNode = nextNode->getNext();
			}
			delete nextNode;
		}
		head = new Node();
		length = 0;
	}
	void set(size_t index, char ch) {  //setting symbol 'ch' instead of symbol in position of 'index'
		if (index >= length) {
			return;
		}
		else {
			auto node = head;
			for (size_t i = 0; i < index; i++) {
				node = node->getNext();
			}
			node->setValue(ch);
		}
	}
	bool isEmpty() {  //returns whether the list is empty
		return length == 0;
	}
	int find_first(MyList* list) {  //returns the first entry (index) of the list 'list' in original list
		auto listNode = head;  //original list
		for (size_t i = 0; i < length; i++) {  //iteration of nodes of original list
			if (length - i < list->length)  //if remaining length of list shorter than the length of 'list' so there are no entries
				return -1;
			auto otherListNode = list->head;  //'list'
			if (listNode->getValue() == otherListNode->getValue()) {
				auto listNode2 = listNode;
				bool flag = true;  //whether or not an entry is found
				for (size_t j = 1; j < list->length; j++) {  //iteration of nodes of 'list'
					listNode2 = listNode2->getNext();
					otherListNode = otherListNode->getNext();
					if (listNode2->getValue() != otherListNode->getValue()) {  //elements are not equal, so there is no entry
						flag = false;
						break;
					}
				}
				if (flag)  //entry found
					return i;  //index of first entry
			}
			listNode = listNode->getNext();
		}
		return -1;  //entry not found
	}
};

int main() {
	return 0;
}