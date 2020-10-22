#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1/lab1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab1
{
	TEST_CLASS(UnitTestLab1)
	{
	private:
		MyList* myList = new MyList();
	public:
		TEST_METHOD_INITIALIZE(init) {
			myList->push_back('a');
			myList->push_back('b');
			myList->push_back('c');
		}
		TEST_METHOD(test_push_back) {
			myList->push_back('d');
			Assert::AreEqual(myList->at(3), 'd');
		}
		TEST_METHOD(test_push_front) {
			myList->push_front('0');
			Assert::AreEqual(myList->at(0), '0');
		}
		TEST_METHOD(test_pop_back) {
			myList->pop_back();
			Assert::AreEqual(myList->getSize(), (size_t)2);
		}
		TEST_METHOD(test_pop_front) {
			myList->pop_front();
			Assert::AreEqual(myList->at(0), 'b');
		}
		TEST_METHOD(test_insert) {
			myList->insert('0', 0);
			myList->insert('1', 2);
			myList->insert('2', 4);
			Assert::AreEqual(myList->at(0), '0');
			Assert::AreEqual(myList->at(2), '1');
			Assert::AreEqual(myList->at(4), '2');
		}
		TEST_METHOD(test_at) {
			Assert::AreEqual(myList->at(1), 'b');
		}
		TEST_METHOD(test_remove) {
			myList->remove(1);
			Assert::AreEqual(myList->at(1), 'c');
		}
		TEST_METHOD(test_get_size) {
			Assert::AreEqual(myList->getSize(), (size_t)3);
		}
		TEST_METHOD(test_print_to_console) {
			myList->print_to_console();
		}
		TEST_METHOD(test_clear) {
			myList->clear();
			Assert::IsTrue(myList->isEmpty());
		}
		TEST_METHOD(test_set) {
			myList->set(1, 'f');
			Assert::AreEqual(myList->at(1), 'f');
		}
		TEST_METHOD(test_is_empty) {
			Assert::IsFalse(myList->isEmpty());
			myList->clear();
			Assert::IsTrue(myList->isEmpty());
		}
		TEST_METHOD(test_find_first) {
			MyList* list2 = new MyList();
			MyList* list3 = new MyList('a');
			MyList* list4 = new MyList('b');
			MyList* list5 = new MyList('a');
			list4->push_back('c');
			list5->push_back('b');
			list5->push_back('c');
			list5->push_back('d');
			Assert::AreEqual(myList->find_first(list2), -1);
			Assert::AreEqual(myList->find_first(list3), 0);
			Assert::AreEqual(myList->find_first(list4), 1);
			Assert::AreEqual(myList->find_first(list5), -1);
		}
	};
}
