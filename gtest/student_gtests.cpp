#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(EditDistanceTests, SameWord) {
  string word1 = "hello";
  string word2 = "hello";
  EXPECT_TRUE(edit_distance_within(word1, word2, 0));
}


TEST(EditDistanceTests, SameLength) {
  string word1 = "hgffo";
  string word2 = "hello";
  EXPECT_TRUE(edit_distance_within(word1, word2, 3));
}


TEST(EditDistanceTests, OnlyNewLettersAtEnd) {
  string word1 = "hellow";
  string word2 = "hello";
  EXPECT_TRUE(edit_distance_within(word1, word2, 1));
}


TEST(EditDistanceTests, OnlyNewLettersAtStart) {
  string word1 = "worldhello";
  string word2 = "hello";
  EXPECT_TRUE(edit_distance_within(word1, word2, 5));
}


TEST(EditDistanceTests, NewLettersAndDifferent) {
  string word1 = "worldhgffo";
  string word2 = "hello";
  EXPECT_TRUE(edit_distance_within(word1, word2, 7));
}


TEST(isAdjacent, ReturnsFalse) {
  string word1 = "worldhgffo";
  string word2 = "hello";
  EXPECT_FALSE(is_adjacent(word1, word2));
}


TEST(isAdjacent, ReturnsTrueDifferingCharacter) {
  string word1 = "helgo";
  string word2 = "hello";
  EXPECT_TRUE(is_adjacent(word1, word2));
}


TEST(isAdjacent, ReturnsFalseTwoDifferingCharacters) {
  string word1 = "cat";
  string word2 = "trap";
  EXPECT_FALSE(is_adjacent(word1, word2));
}


TEST(isAdjacent, RandomWordsNotAdjacent) {
  string word1 = "Ada";
  string word2 = "stocked";
  EXPECT_FALSE(edit_distance_within(word1, word2, 1));
  EXPECT_FALSE(is_adjacent(word1, word2));
}
