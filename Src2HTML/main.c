#include "common.h"


int main()
{

	while(1)
	{
		printf("\nEnter the operation to perform\n1.SRC to HTML\n2.exit\n");
		int opt;
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:
			{
				convert();
				break;
			}
			case 2:
			{
				exit(0);
			}
			default:
			{
				printf("Enter the valid options\n");
			}
		}
	}
}