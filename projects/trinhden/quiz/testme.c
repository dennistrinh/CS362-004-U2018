#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*****************************************************
 * char inputChar()
 * Generates a random character from space to tilde
 * following the ASCII table. Omitted special chars.
*****************************************************/
char inputChar()
{
    int min = 32; // ASCII Code for space
    int max = 126; // ASCII Code for tilde
    int diff = max - min; // Finds the difference
    char c = (rand() % (diff + 1)) + min; // Generate random char
    return c;
}

/**********************************************************
 * void *inputString(char str[])
 * This function takes a string and modifies the contents
 * to a random 5 character string. The range is from
 * ASCII code 101 ('e') to ASCII code 116 ('t').
***********************************************************/
void *inputString(char str[])
{
    int min = 101; // ASCII Code for 'e'
    int max = 116; // ASCII Code for 't'
    int diff = max - min; // Difference
    int i; // Counter
    for (i = 0; i < strlen(str); i++) { // Generates five characters
      str[i] = (rand() % (diff + 1)) + min;
    }
}

void testme()
{
  int tcCount = 0;
  char s[] = "abcde";
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    inputString(s);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
