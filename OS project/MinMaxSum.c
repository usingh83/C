#include <stdio.h>
int main()
{
int i, max, min, size=25, sum;
int arr[25]={2,1,8,9,11,14,5,18,1,2,3,12,34,23,4566,34,432,23,234,256,15,77,8,5,12};
max = arr[0];
min = arr[0];
sum=0;
for(i=1; i<size; i++)
{
	if(arr[i]>max)
		{
		max = arr[i];
		}
	if(arr[i]<min)
		{
		min = arr[i];
		}
	sum+=arr[i];
}
printf("Maximum element = %d\n", max);
printf("Minimum element = %d\n", min);
printf("Sum of the elements = %d\n", sum);
printf("Mean of the elements = %d\n", sum/size);
printf("Median of the elements = %d\n",size%2==1?arr[(size/2)+1]:(arr[size/2]+arr[(size/2)+1])/2);

return 0;
}
