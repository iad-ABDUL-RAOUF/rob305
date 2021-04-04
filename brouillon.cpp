#include <stdio.h>
#include <cstdlib>
#include <time.h>


enum states {OK, KO};

struct vote
{
  /* data */
  bool error;
  int value;
};

void step (enum states *state, int *input, struct vote *output)
{
  
  bool error = (input[0] != input[1]);
  switch (*state){
    case OK:
      (*output).error = error;
      if (error){
        *state = KO;
      }
    break;
    case KO:
      (*output).error = true;
    break;
  }
  (*output).value = input[0];
}

void create_2values (int *values)
{
  values[1] = 13;
  double flag = rand() / (double) RAND_MAX;
  if (flag<0.95){
    values[0] = values[1];
  }
  else{
    values[0] = values[1]+37;
  }
  //printf("%f %d %d\n", flag, values[0], values[1]);
}

int main(void)
{
  srand (time(NULL));
  
  enum states state = OK;
  int input[2];
  struct vote output = {true, 0};
  unsigned int n = 0;
  //while (true)
  for (n = 0; n < 100; n++)
  {
    /* code */
    create_2values (input);
    step(&state, input, &output);
    printf("%d %d\n", output.value, output.error);
  }
  
  return EXIT_SUCCESS;
}