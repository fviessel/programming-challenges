#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>

// Probability that Y follows X is `probabilities[256*X + Y]`
//double probabilities[256*256];
int counts[256*256] = {0};

int main(void) {
  printf("Feeding the markov chain..\n");

  // Read the contents of feed.txt into `text`
  FILE *feed;
  fopen_s(&feed, "feed.txt", "rb");
  fseek(feed, 0, SEEK_END);
  int size = ftell(feed);
  fseek(feed, 0, SEEK_SET);
  char *text = malloc(size+1);
  text[size] = 0;
  fread(text, size, 1, feed);

  // Count how many times each characters follows every other character
  char previous;
  char current = text[0];

  int index = 1;
  while(index != size) {
    previous = current;
    current = text[index];
    counts[256*previous + current] += 1;
    index += 1;
  }

  printf("Shitposting the output:\n");
  const int shit_count = 10000;
  const char shit_first_char = 'a';

  // Initialize rand gen
  time_t t;
  srand((unsigned) time(&t));

  int shit_index = 1;
  char last_char = shit_first_char;
  putc(shit_first_char, stdout);
  while(shit_index != shit_count) {
    
    // Roll the random to see which character to follow
    int total_count = 0;
    for(int i = 0; i < 256; i += 1) {
      total_count += counts[256*last_char + i];
    }
    int roll = rand() % total_count;
    int i = 0;
    while(roll >= counts[256*last_char + i]) {
      roll -= counts[256*last_char + i];
      i += 1;
    }
    char next_char = (char)i;

    // `i` should be the next character to chose
    putc(next_char, stdout);

    last_char = next_char;
    shit_index += 1;
  }

  return 0;
}
