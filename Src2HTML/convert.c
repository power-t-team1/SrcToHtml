#include "common.h"

int convert()
{
	FILE *fp, *fd, *fp1;
	fp = fopen("dummy.c", "rb");
	//fp1	= fopen("mark.html", "rb");

	char *name = malloc(20 * sizeof(char));
	char *buffer = malloc(20 * sizeof(char));
	char *buff2 = malloc(20 * sizeof(char));
	//fp1 = fp;
	//fseek(fp1,10,SEEK_CUR);
	fd = fopen("mark.html", "wb");

	char ch;
	
	char ch1;
	fprintf(fd, "<pre>\n");
	fprintf(fd,"<span style=\"color:blue;font-weight:bold\"> %s </span>\n");
	fprintf(fd, "</pre>");
	fseek(fd,5,SEEK_SET);
	while((ch1 = fgetc(fp)) != EOF)
	{
		printf("dsfds\n");
		fputc(ch1, fd);
	}
	fprintf(fd,"<STYLE>body{backgroud-color:#190707; shubam}</STYLE>");
	//char *buf = malloc(sizeof(char) * 10);
	/*while((fscanf(fp,"%s",buf )) != EOF)
	{
		fprintf(fd,"%s",buf);
	}*/
	//while((ch = fgetc(fp)) != EOF)
	{
	//	fputc(ch, fd);
	}
	fclose(fd);
	fclose(fp);
	return SUCCESS;
}