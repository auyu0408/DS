#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int convert(char a)//encoding table of hex digit, let english word into number
{
    int r;
    if(a>='0'&&a<='9')
    {
        return a-'0';
    }
    else if(a>='A'&&a<='F')
    {
        return a-'A'+10;
    }
    else
    {
         printf("INCORRECT WORD.\n");// if we find the word which is not in hex, print out and end the program
            return 1;
    }
}
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};//encoding table of base64

int main(int argc, char **argv)
{
    char ch='0';
    while(ch!=EOF)//read origin file one line a time
    {
        char *origin,*ans;// the array use to save original file./the final array.
        origin=(char *)malloc(301*sizeof(char));
        if(ch=='\n') printf("\n");//判斷是因為讀300次還是換行而暫停
        ch=getchar();
        int c=0;
        while(ch!='\n'&&ch!=EOF)//一次最多300字，換行可以停下，讀300先暫停
        {
            origin[c]=ch;
            c++;
            if(c==300) break;
            ch=getchar();
        }
        origin[c]='\0';
        int SIZEorigin=(int)strlen(origin),re=0;//know the size of origin array.
        int SIZEcon=(SIZEorigin*2/3)+2;//size of final array,we plus 2 to incase there're less than 3 to convert.
        ans=(char *)malloc((SIZEcon+1)*sizeof(char));
        memset(ans,0,SIZEcon);
        for(int count=0;count<SIZEcon-3;count=count+2)//we get 3 number in once and convert to 2 number in base64.
        {
            int real=0;//the value to calculate the sum of 3 number.
            for (int i=0;i<3;i++)
            {
                real=real+(int)(convert(origin[re+i])*pow(16,2-i));//add number from right to left.
            }
            int	k=real%64;//convert then with 64,check the code by encoding table.
            ans[count+1]=encoding_table[k];
            real=real/64;
            ans[count]=encoding_table[real];
            re=re+3;
        }
        if(SIZEorigin%3==1)//if we have one word left, paddel two 0 (multiple4)
        {
            int real=convert(origin[SIZEorigin-1]);
            real=real*4;
            ans[SIZEcon-2]=encoding_table[real];
            printf("%s=",ans);
        }
        else if(SIZEorigin%3==2)//if we have two word left, paddel four 0 (multiple16) to make it be 12 .
        {
            int real=convert(origin[SIZEorigin-2])*16+convert(origin[SIZEorigin-1]);
            real=real*16;
            int	r=real%64;
            ans[SIZEcon-2]=encoding_table[r];
            real=real/64;
            ans[SIZEcon-3]=encoding_table[real];
            printf("%s==",ans);
        }
        else printf("%s",ans);
        free(origin);
    }
    return 0;
}