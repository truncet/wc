#include<stdio.h>
#include<getopt.h>

int main(int argc, char *argv[]);

int show_help();


int show_help(){

  printf("help called");
  return 0;
}

int main(int argc, char *argv[]){

  int option_val;

  char *value = NULL;

  struct option long_options[] = {
    {
      "bytes", required_argument, 0, 'c'
    },
    {
      "chars", no_argument, 0, 'm'
    },
    {
      "lines", required_argument, 0, 'l'
    },
    {0, 0, 0, 0}
  };

  int option_index = 0;

  while ( (option_val = getopt_long(argc, argv, "c:m:l:", long_options, &option_index)) != -1) {
    switch (option_val){
      case('c'):
        value = optarg;
        printf ("%s\n", value);
        break;
      
      case ('m'):
        value = optarg;
        printf ("%s\n", value);
        break;

      case ('l'):
        value = optarg;
        printf ("%s\n", value);
        break;
      
      case '?':
        printf ("Some kind of error detected\n");

      default:
        show_help();
    }
  }

  return 0;
}