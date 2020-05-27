// Hamilton Nguyen 1000538439
//gcc lab3.c
//a.out < lab3fall19a.dat
//a.out < lab3fall19b.dat
//a.out < lab3fall19c.dat

#include <stdio.h>
#include <stdlib.h>
#define SET 50

//global arrays	
double cost[50][50];
int trace[50][50];
void HuffmanTree(int left,int right,int format);
void ExpectationTable(int n, int k,int i, double probNodeOfInterest, double allBits, double data[]);

int main()
{
	int n,i,j,k;
	double blackJack;
	
	scanf("%d",&n);

	double data[n];
	int counter;
	double summdoub = 0;
	double probNodeOfInterest; 
	double allBits = 0;
	
	for (i=0;i<n;i++)
		scanf("%lf",&data[i]);
	
	for (i=0;i<n;i++)
		cost[i][i]= trace[i][i]= 0;
	
	for (i=0;i<n;i++) 			
		for (j=0;j<n-i;j++)		
		{
			summdoub = 0;
			for (counter = j; counter <= j+i; counter++)
				summdoub += data[counter];
				
			cost[j][j+i+1] = 9999;

			for (k=j;k<j+i;k++)
			{		
				blackJack=cost[j][k]+cost[k+1][j+i]+summdoub;		
				
				if (cost[j][j+i]>blackJack)
				{
					cost[j][j+i]=blackJack;
					trace[j][j+i]= k;
				}				
			}
		}

	summdoub = 0;

	for (counter = 0; counter < n; counter++)
		summdoub += data[counter];
		
	printf("\nprobability sum to %lf\n", summdoub);
	printf("Code tree for exact:\n");
	
	HuffmanTree(0,n-1,0);
	
	ExpectationTable(n, k, i, probNodeOfInterest, allBits, data);
	
	return 0;
}


void HuffmanTree(int left,int right,int format)
{
	int i;
	if (left==right)
	{
		for (i=0;i<format;i++)
			printf("   ");
			
		printf("%d \n",left);
		return;
	}
	
	HuffmanTree(trace[left][right]+1,right,format+1);
	
	for (i=0;i<format;i++)
		printf("   ");
		
	printf("%d %d  cost %lf\n",left,right, cost[left][right]);
	HuffmanTree(left,trace[left][right],format+1);
}

void ExpectationTable(int n, int k,int i,double probNodeOfInterest, double allBits, double data[])
{
	char bitSequence[20];
	int number;
	int z;
	int left;
	int right;
	int position;
	printf("Codes & prob*# of bits\n");
	
	for (number = 0; number < n; number++)
	{
		position = 0;
		z = 0;
		k = trace[0][n-1];	
		left = 0;
		right = n -1;
		
		while(left != right)
		{
			if (number <= k)
			{
				bitSequence[z] = '0';
				right = k;
			}
			if (number > k)
			{
				bitSequence[z] = '1';
				left = k + 1;
			}
			k = trace[left][right];
			z++;
		}
		printf("%d ",number);
		
		for (i = 0; i < z; i++)
		{
			printf("%c", bitSequence[i]);
			position++;
		}
		
		probNodeOfInterest = data[number] * position;

		printf(" %lf \n",probNodeOfInterest);

		allBits +=probNodeOfInterest;
	}
	printf("Expected bits per symbol %lf\n\n", allBits);
}

