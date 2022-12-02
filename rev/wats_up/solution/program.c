#include <stdio.h>
#include <string.h>
char* mask = "4242424242424242424242424242424242424242424242424242";
char* foo = "S\\QWU]J_PF[s\x18{esFUO%OG^IJ}";
char* flag = "glacierctf{THIS_IS_A_FUN_FLAG}";
char* flag2 = "glacierctf{THIS_IS_A_FUN_FLAG2}";

void encrypt(int magic_number,char* input, char* output)
{
  if(magic_number == 0xCAFEBABE)
  {
    if(strlen(input) == strlen(foo))
    {
      for(int i = 0; i < strlen(input);i++)
      {
        char x = (((i << 3) & 0xFF) >> 2) & 0xFF ^ input[i] ^ mask[i];
        if(x == 13)
          x += 37;
        if(x == 0)
          x += 50;
        
        output[i] = x;
      }
    }
  }
}

int main()
{
  char buffer[26] = {0,};
  encrypt(0xCAFEBABE,foo,buffer);
  printf("%s\n",buffer);
}

