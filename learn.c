#include "learn.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      fprintf(stderr, "Incorrect Input\n");
    }
  
  getTrainingData(argv[1]);
  //getTestData(argv[2]);

  return 0;
}
