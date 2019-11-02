#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char testString[6];

char inputChar(){
    char charToTest;     
    char selectTestChar[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
    if (!(rand() % 20)){ //Test select chars at a probability of ~0.05
      charToTest = selectTestChar[(rand() % 9)]; // Randomly select char from array
    }else{
      charToTest = ((rand() % 95) + 32); //otherwise randomply select ASCII space through ~
    }
    return charToTest;
}
 
char *inputString(){
    char selectTestChar[4] = {'r', 's', 'e', 't'};
    for (int i = 0; i < 5; i++){      //Loop to make string of 5 chars
      if (rand() % 10){               //Include select char at a probability of ~0.1
        testString[i] = selectTestChar[(rand() % 4)]; // Randomly select char from array
      }else{
        testString[i] = ((rand() % 95) + 32); //otherwise randomply select ASCII space through ~
      }
    }
    return testString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
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
