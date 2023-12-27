#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include<stdlib.h>

#define PROGRAM "wc"
#define VERSION "truncet-wc-0.1"

#define MAX_INPUT_LENGTH 256

static int bytes_val, char_val, words_val, line_val, max_line_val;

int main(int argc, char *argv[]);

int find_params(char *file_name, int bytes_val, int char_val, int line_val, int words_val, int max_line_val);

int show_help();

int implement_characters(char *value);

int implement_bytes(char *value);

int implement_lines(char *value);

int implement_words(char *value);


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

int check_length_limit(char *value){
  if (strlen(value) > MAX_INPUT_LENGTH)
    return 0;
  return 1;
}


int find_params(char *file_name, int bytes_val, int char_val, int line_val, int words_val, int max_line_val){
  return 0;
}

int implement_characters(char *value){
  printf("%s", value);
  return 0;

}

int implement_bytes(char *value){
  return 0;
}

int implement_lines(char *value){
  return 0;
}

int implement_words(char *value){
  return 0;
} 

int main(int argc, char *argv[]){

  int option_val;

  char *value = NULL;

  char_val = bytes_val = words_val = line_val = max_line_val = 0;

  struct option long_options[] = {
    {
      "bytes", no_argument, 0, 'c'
    },
    {
      "chars", no_argument, 0, 'm'
    },
    {
      "lines", no_argument, 0, 'l'
    },
    {
      "max-line-length", no_argument, 0, 'L'
    },
    {
      "words", no_argument, 0, 'w'
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

  while ( (option_val = getopt_long(argc, argv, "cmlLw", long_options, &option_index)) != -1) {
    switch (option_val){
      case('c'):
        char_val = 1;
        break;
      
      case ('m'):
        bytes_val = 1;
        break;
      
      case ('l'):
        line_val = 1;
        break;

      case ('L'):
        max_line_val = 1;
        break;

      case ('w'):
        words_val = 1;
        break;

     
      case 0:
        if (strcmp(long_options[option_index].name, "version") == 0){
          printf ("%s\n", VERSION);
        }
        else if (strcmp(long_options[option_index].name, "help") == 0){
          show_help();
        }
        break;
      
      case '?':
        fputs ("Try 'wc --help' for more information.\n", stdout);
        exit(1);

      default:
        exit(1);
    }

  }


  for (int i = optind; i < argc; i++){
    printf("Filename %s\n", argv[i]);
    find_params(argv[i], char_val, bytes_val, line_val, words_val, max_line_val);
  }

  return 0;
}