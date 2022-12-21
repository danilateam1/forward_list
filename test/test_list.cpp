#include <gtest.h>
#include "list.h"
TEST(ForwardList, constructor_with_size) {
	ASSERT_NO_THROW(ForwardList<int> list(5));
}
TEST(ForwardList, constructor_with_initializer_list) {
	ASSERT_NO_THROW(ForwardList<int> list({ 1, 2, 3, 4, 5 }));
}
TEST(ForwardList, can_get_size) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	EXPECT_EQ(5,list.get_size());
}

TEST(ForwardList, word_constructor_copy) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> list1(list);
	ASSERT_NO_THROW(ForwardList<int> list1(list););
}

TEST(ForwardList, work_constructor_copy) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> list1(list);
	ASSERT_NO_THROW(ForwardList<int> list1(list));
}

TEST(ForwardList, constructor_move) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> tmp(std::move(list));
	ForwardList<int> ::iterator it = tmp.ind(2);
	EXPECT_EQ(5, tmp.get_size());
	EXPECT_EQ(3, *it);
}


TEST(ForwardList, can_move_operator) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> tmp({2,3});
	tmp = std::move(list);
	ForwardList<int> ::iterator it = tmp.ind(2);
	EXPECT_EQ(5, tmp.get_size());
	EXPECT_EQ(3, *it);
}

TEST(ForwardList, can_pop_front) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	list.pop_front();
	ForwardList<int> ::iterator it = list.begin();
	EXPECT_EQ(4, list.get_size());
	EXPECT_EQ(2, *it);
}
TEST(ForwardList, can_push_front) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	list.push_front(6);
	ForwardList<int> ::iterator it = list.begin();
	EXPECT_EQ(6, list.get_size());
	EXPECT_EQ(6, *it);
}

TEST(ForwardList, can_push_back) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	list.push_back(6);
	ForwardList<int> ::iterator it = list.pre_end();
	EXPECT_EQ(6, *it);
}

TEST(ForwardList, can_pop_back) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	list.pop_back();
	ForwardList<int> ::iterator it = list.pre_end();
	EXPECT_EQ(4, *it);
}

TEST(ForwardList, can_get_iterator_begin_and_end) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> ::iterator it1 = list.begin();
	ForwardList<int> ::iterator it2 = list.end();
	EXPECT_EQ(1, *it1);
	EXPECT_EQ(nullptr, it2);
}

TEST(ForwardList, can_insert_after) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> ::iterator it1 = list.ind(2);//index[2]
	list.insert_after(it1, 10);
	ForwardList<int> ::iterator it2 = list.ind(4);//index[4]
	EXPECT_EQ(3, *it1);
	EXPECT_EQ(4, *it2);
}

TEST(ForwardList, can_erase_after) {
	ForwardList<int> list({ 1, 2, 3, 4, 5 });
	ForwardList<int> ::iterator it1 = list.ind(2);//index[2]
	list.erase_after(it1);
	ForwardList<int> ::iterator it2 = list.ind(3);//index[4]
	EXPECT_EQ(3, *it1);
	EXPECT_EQ(5, *it2);
}

TEST(ForwardList, cans_find_middle_element) {
	ForwardList<int> list({ 1, 2, 1, 4, 5,-4,2,0,23,10 });
	std::vector<int> l = list.find_middle();
	EXPECT_EQ(l[0], 5);
	EXPECT_EQ(l[1], -4);
}
