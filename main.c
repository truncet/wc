#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]);

int show_help();


int show_help(){
  fputs("Usage: wc [OPTION]... [FILE]\n", stdout);

  fputs("Print newline, word, and byte counts for each FILE, and a total line if\n\
more than one FILE is specified.  A word is a non-zero-length sequence of\n\
characters delimited by white space.\n", stdout);

  fputs("\nWith no FILE, or when FILE is -, read standard input.\n", stdout);

  fputs("\nThe options below may be used to select which counts are printed, always in\n\
the following order: newline, word, character, byte, maximum line length.\n", stdout);

  fputs("\t-c, --bytes                print the byte counts\n", stdout);
  fputs("\t-m, --chars                print the character counts\n", stdout);
  fputs("\t-L, --max-line-length      print the maximum display width\n", stdout);
  fputs("\t-w, --words                print the word counts\n", stdout);
  fputs("\t    --help         display this help and exit\n", stdout);
  fputs("\t    --version      output version information and exit\n", stdout);

}

int main(int argc, char *argv[]){

  int option_val;

  char *value = NULL;

  struct option long_options[] = {
    {
      "bytes", required_argument, 0, 'c'
    },
    {
      "chars", required_argument, 0, 'm'
    },
    {
      "lines", required_argument, 0, 'l'
    },
    {
      "max-line-length", no_argument, 0, 'L'
    },
    {
      "words", required_argument, 0, 'w'
    },
    {
      "version", no_argument, 0, 0
    },
    {
      "help", no_argument, 0, 0
    },
    {0, 0, 0, 0}
  };

  int option_index = 0;

  while ( (option_val = getopt_long(argc, argv, "c:m:l:Lw:", long_options, &option_index)) != -1) {
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
        show_help();
        break;
      
      case 0:
        if (strcmp(long_options[option_index].name, "version") == 0){
          fputs ("truncet-wc-0.1\n", stdout);
        }
        else if (strcmp(long_options[option_index].name, "help") == 0){
          show_help();
        }
        break;
      
      case '?':
        fputs ("Try 'wc --help' for more information.\n", stdout);
        break;

      default:
        
        exit(0);
    }
  }

  return 0;
}