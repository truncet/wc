#include<stdio.h>
#include<getopt.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

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

int get_bytes_val(char c){
  int numBytes = 0;
  while ((c & 0b10000000) == 0b10000000){
    c <<= 1;
    ++numBytes;
  }

  if (numBytes == 0){
    numBytes = 1;
  }
  return numBytes;
}


int find_params(char *file_name, int bytes_val, int char_val, int line_val, int words_val, int max_line_val){


  int no_of_chars = 0;
  int no_of_bytes = 0;
  int no_of_lines = 0;
  int no_of_words = 0;
  int max_line = 0;
  int max_in_a_line = 0;

  int results[5] = {-1, -1, -1, -1, -1};
  char c;

  char prev_value = '\0';

  FILE *file;
  
  file = fopen(file_name, "r");
  if(file == NULL){
    fputs("Error opening the file\n", stdout);
  }
  while((c =fgetc(file)) != EOF){
    ++no_of_chars;  // this is for calculating no of chars

    no_of_bytes += get_bytes_val(c);  // this is for calculating no of bytes

    if (isspace(prev_value) || prev_value == '\0'){
      if(!(isspace(c))){
        ++no_of_words;
      }
    }
    max_line += isspace(c)?0: 1;
    if (c == '\n'){
      ++no_of_lines;
      if (max_line > max_in_a_line){
        max_in_a_line = max_line;
        max_line = 0;
      }
    }

    prev_value = c;
  }
  if (line_val) results[0] = no_of_lines;
  if (words_val) results[1] = no_of_words;
  if (char_val) results[2] = no_of_chars;
  if (bytes_val) results[3] = no_of_bytes;
  if (max_line_val) results[4] = max_in_a_line > max_line? max_in_a_line: max_line;

  for (int i = 0; i < 5; ++i){
    if (results[i] != -1){
      printf("%d ", results[i]);
    }
  }
  printf("%s\n", file_name);

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
        bytes_val = 1;
        break;
      
      case ('m'):
        char_val = 1;
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

  if (!char_val && !bytes_val && !line_val && !max_line_val && !words_val) {
        line_val = words_val = char_val = 1;
  }

  for (int i = optind; i < argc; i++){
    if (check_length_limit(argv[i]))
      find_params(argv[i], char_val, bytes_val, line_val, words_val, max_line_val);
    else{
      printf("\nThe length of filename is longer than %d\n", MAX_INPUT_LENGTH);
    }
  }
  return 0;
}