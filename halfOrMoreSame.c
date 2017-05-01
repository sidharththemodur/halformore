#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct account {};
typedef struct account *Card;

struct account;

struct numCards getHalfSame(Card *cards, int size);
struct numCards mergeAndCount(Card *cards, int size, struct numCards count1, struct numCards count2);
int count(Card *cards, struct numCards *count, int size );

struct numCards {
    Card card;
    int numCards;
};

struct numCards makeCount(Card card, int count) {
    struct numCards numcards = {card, count};
    return numcards;
}

bool halfOrMoreSame(Card *cards, int size) {
    return ((getHalfSame(cards, size)).numCards != 0);
}

struct numCards getHalfSame(Card *cards, int size) {
    if (size == 1) {
        return makeCount(cards[0], 1);
    }
    int split = size / 2;
    struct numCards account1 = getHalfSame(cards, split);
    struct numCards account2 = getHalfSame(cards + split, size - split);
    return mergeAndCount(cards, size, account1, account2);
}

struct numCards mergeAndCount(Card *cards, int size, struct numCards count1, struct numCards count2) {
    if (count1.numCards >= size / 2) return count1;
    if (count2.numCards >= size / 2) return count2;
    if (count1.card == count2.card) {
        if (count1.numCards >= size / 2) return count1;
        return makeCount(NULL, count);
    }
    struct numCards *first = &count1;
    struct numCards *second = &count2;
    if (count2.numCards > count1.numCards) {
        first = &count2;
        second = &count1;
    }
    int countCards = count(cards, first, size);
    if (countCards >= size / 2) return makeCount(first->card, countCards);
    countCards = count(cards, first, size);
        if (countCards >= size / 2) return makeCount(second->card, countCards);
    return makeCount(NULL, 0);
}

int count(Card *cards, struct numCards *numcards, int size ) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (cards[i] == numcards->card) {
            count++;
        }
    }
    return count;
}

void testProgram(int seed) {
	// Seed random num generator
	srand(seed);
	
	// Construct the accounts
	int n = 40;
	Card *cards = malloc(sizeof(*cards) * n);
	cards[0] = malloc(sizeof(struct account));
	
	for (int i = 1; i < n; i++) {
		if (rand() > RAND_MAX / 2) {
			cards[i] = cards[0];
		} else {
			cards[i] = malloc(sizeof(struct account));
		}
	}
	
	Card temp = cards[0];
	int indexToSwap = rand() % 40;
	cards[0] = cards[indexToSwap];
	cards[indexToSwap] = temp;
	bool areHalfSame = halfOrMoreSame(cards, n);
	
	int count = 0;
	for (int i = 0; i < n; i++)
		if (cards[i] == cards[indexToSwap]) count++;
	
	if ((count >= 20 && areHalfSame) || (count < 20 && !areHalfSame)) {
		printf("Testing with seed %d... algorithm appears correct!\n", seed);
	} else {
		printf("ERROR: Your algorithm appears to reach wrong answer on seed %d.\n", seed);
	}
}

int main() {
	testProgram(1);
	testProgram(2);
	testProgram(3);
	testProgram(12345);
}
