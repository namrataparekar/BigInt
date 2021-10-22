
#include<stdio.h>
#include<string.h>
#define SIZE 310
#define MINUS -1
#define PLUSE 1


typedef struct bignum{
	char number[SIZE];
	int sign;
	int lastdgt;
}BigInt;

int max(int a, int b);
void initializeNum(BigInt *num);
void conversion(char n1[], BigInt *num);
void Print(BigInt num);
int compare(BigInt num1, BigInt num2);
BigInt Add(BigInt num1, BigInt num2);
BigInt subtract(BigInt num1, BigInt num2);
BigInt multiply(BigInt num1, BigInt num2);

int main()
{ 
    char n1[SIZE],n2[SIZE];
    BigInt num1,num2,res1,res2,res3;

    printf("Enter the Number 1: ");
    scanf("%s",n1);									

    printf("Enter the Number 2: ");
    scanf("%s",n2);									


	
    initializeNum(&num1);	
    initializeNum(&num2);
    initializeNum(&res1);
    initializeNum(&res2);
    initializeNum(&res3);


    conversion(n1,&num1);
    conversion(n2,&num2);


    res1=Add(num1,num2);
	printf("\nAddition:\t");			
    Print(res1);

    res2=subtract(num1,num2);
	printf("\nSubtraction:\t");			
    Print(res2);

    res3=multiply(num1,num2);
	printf("\nMultiplication:\t");			
    Print(res3);
    
    return 0;
}
int max(int a, int b)					
{
    return (a>b)?a:b;
}

void initializeNum(BigInt *num)		
{
    num->number[SIZE-1]='\0';
    num->lastdgt=SIZE-1;
}

void  conversion(char n1[], BigInt *num)	
{
    int i,j,l,z=0;
    if(n1[0]=='-')								
    {
        num->sign=MINUS;
        z=1;
    }
    else
    num->sign=PLUSE;							
    l=strlen(n1);
    j=SIZE-1;
    num->number[SIZE-1]='\0';
    i=l-1;
    while(i>=z)							
    {
        j--;
        num->number[j]=n1[i];
        i--;
    }
    num->lastdgt=j;
    
}

int compare(BigInt num1, BigInt num2)			
{
    if(num1.lastdgt<num2.lastdgt)
    return 0;
    else if(num2.lastdgt<num1.lastdgt)
    return 1;
    else
    {
        int i=num1.lastdgt;
        while(num1.number[i]==num2.number[i] && i<=SIZE-2)
        {
            i++;
        }

        return (num1.number[i]>num2.number[i])?0:1;
    }
}

BigInt Add(BigInt num1, BigInt num2)	
{
    BigInt a;
    initializeNum(&a);
    
    
    if(num1.sign==num2.sign)
    {
        a.sign=num1.sign;
    }
    
    
    else
    {
        if(num1.sign==PLUSE && num2.sign==MINUS)		
        {
            num2.sign=PLUSE;
            a=subtract(num1,num2);
            int f=compare(num1,num2);				
            if(f==1)            					
            a.sign=MINUS;
            else
            a.sign=PLUSE;						
            return a;
        }
        else if(num1.sign==MINUS && num2.sign==PLUSE)	
        {
            num1.sign=PLUSE;
            a=subtract(num1,num2);
            int f=compare(num1,num2);			
            
			(f==1)?(a.sign=PLUSE):(a.sign=MINUS);
            						
            return a;
        }
    }

    int n,i,l,carry=0;
    l=max(num1.lastdgt,num2.lastdgt);
	i=SIZE-2;
    while(i>=l)			
    {
        n=(num1.number[i]-'0')+(num2.number[i]-'0')+carry;
        (a.lastdgt)--;
        a.number[a.lastdgt]=48+n%10;
        carry=n/10;
        i--;
    }

    if(num1.lastdgt<num2.lastdgt)		
    {
    	int i;
        while(i>=num1.lastdgt)
        {
            n=(num1.number[i]-'0')+carry;
            (a.lastdgt)--;
            a.number[a.lastdgt]=48+n%10;
            carry=n/10;
            i--;
        }

    }
    else if(num2.lastdgt<num1.lastdgt)		
    {
    	int i;
        while(i>=num2.lastdgt)
        {
            n=(num2.number[i]-'0')+carry;
            (a.lastdgt)--;
            a.number[a.lastdgt]=48+n%10;
            carry=n/10;
            i--;
        }
    }
    
    if(carry>0)
    {
        (a.lastdgt)--;
        a.number[a.lastdgt]=48+carry;
    }
    return a;
}

BigInt subtract(BigInt num1, BigInt num2)		
{
    BigInt a;
    initializeNum(&a);
    
    
    if(num1.sign!=num2.sign)				
    {
        if(num1.sign==PLUSE && num2.sign==MINUS)		
        {
            num2.sign=PLUSE;								
            a=Add(num1,num2);
            return a;
        }
        else if(num1.sign==MINUS && num2.sign==PLUSE)	 
        {
            num1.sign=PLUSE;								
            a=Add(num1,num2);
            a.sign=MINUS;								
            return a;
        }
    }
    
    else										
    {
        int f=compare(num1,num2);			
        if(f==1)
        {
            if(num1.sign==PLUSE)
            a.sign=MINUS;
            else
            a.sign=PLUSE;
            BigInt temp;
            initializeNum(&temp);
            temp=num1;
            num1=num2;
            num2=temp;
            
        }
        else
        {
            a.sign=num1.sign;
        }
        int sub,i,carry;
        carry=0;
        i=SIZE-2;
        while(i>=num2.lastdgt)		 
        {
            sub=((num1.number[i]-'0')-(num2.number[i]-'0'))-carry;
            if(sub<0)							
            {
                sub=sub+10;
                carry=1;
            }
            else								
            {
                carry=0;
            }
            (a.lastdgt)--;					
            a.number[a.lastdgt]=48+sub;
            i--;
        }

        for(;i>=num1.lastdgt;i--)
        {
            sub=(num1.number[i]-'0')-carry;		
            if(sub<0)
            {
                sub=sub+10;
                carry=1;
            }
            (a.lastdgt)--;
            a.number[a.lastdgt]=48+sub;
        }
    }
    return a;
}

BigInt multiply(BigInt num1, BigInt num2)		
{
    BigInt a;
    initializeNum(&a);
    int i,j;
    int mul[SIZE];
    i=0;
    while(i<SIZE)
    {
        mul[i]=0;
        i++;
    }

    if(num1.sign!=num2.sign)		
    a.sign=MINUS;
    else								
    a.sign=PLUSE;

    int f=compare(num1,num2);		
    if(f==1)
    {
        BigInt temp;
        initializeNum(&temp);
        temp=num1;
        num1=num2;
        num2=temp;
    }

    int carry,sum,n1,n2,m1,m2;
    carry=0;
    m1=0;
    m2=0;
    for(i=SIZE-2;i>=num2.lastdgt;i--)
    {
        carry=0;
        n1=num2.number[i]-'0';
        m1=0;
        for(j=SIZE-2;j>=num1.lastdgt;j--)
        {
            n2=num1.number[j]-'0';

            sum=(n1*n2) + mul[m1+m2] + carry;
            carry=sum/10;

            mul[m1+m2]=sum%10;
            m1++;
        }

        if(carry>0)
        mul[m1+m2]+=carry;

        m2++;
    }

    i=SIZE-1;
    while(i>=0 && mul[i]==0)
    i--;

    j=i;
    if(i==-1)
    {
        (a.lastdgt)--;
        a.number[a.lastdgt]='0';
    }
    else
    {
        for(i=0;i<=j;i++)
        {
            (a.lastdgt)--;
            a.number[a.lastdgt]=48+mul[i];
        }
    }
    return a;
}

void Print(BigInt num)					
{
    if(num.sign==MINUS)						 
    {
        printf("-");
    }
    int i;
    for(i=num.lastdgt;i<=SIZE-2;i++)			
    {
        printf("%c",num.number[i]);
    }
}

