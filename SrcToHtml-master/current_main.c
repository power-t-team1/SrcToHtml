#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char operator[16] = "+-*/(){}<>&=[],;";
char keyword[32][12] = {"auto", "break", "case", "char", "const", "continue", "default", "do", 
	"double", "else", "enum", "extern", "float", "for", " goto", "if",
	"int", "long","register", "return", "short", "signed", "sizeof", "static", 
	"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
char format_specifier[8][3] = {"%d", "%f", "%s", "%c", "%ld", "%x", "%o", "%i"};

void preprocessor(char *buffer, int size, FILE *fd);
int keyword_checking(char*buffer);
char operator_checking(char*buffer);

int main(int argc, char *argv[])
{
	int i = 0, ch, dist, dist1, flag;
	FILE *fp1, *fp, *fd, *fd1;

	char *buffer;
	char word[25];

	if (argc == 1)
	{
		printf("Insufficient Arguments..Provide a .c file\n");
		return -1;
	}

	fp = fopen(argv[1], "r");
	fp1 = fopen(argv[1], "r");
	fd = fopen("de.html", "w");
	fd1 = fopen("de.html", "w"); 

	fprintf(fd, "<!DOCTYPE html>\n");
	fprintf(fd, "<html lang=\"en-US\">\n");
	fprintf(fd, "<head>\n");
	fprintf(fd, "<title>%s</title>\n", "sode2html");
	fprintf(fd, "<meta charset=\"UTF-8\">\n");
	//fprintf(fd, "<link rel=\"stylesheet\" href=\"styles.css\">\n");
	fprintf(fd, "</head>\n");
	fprintf(fd, "<body style=\"background-color:black;\">\n");
	fprintf(fd, "<pre>\n");

	//fseek(fd1,ftell(fd),SEEK_SET);
	//printf("%ld\n",ftell(fd));
	//printf("%ld\n",ftell(fd1));
	//fclose(fd);
	//use span and not the css formatting for changing color.
	printf("%ld\n",ftell(fd));
	printf("%ld\n",ftell(fd1));
	//fprintf(fd, "         sexy\n");
	printf("%ld\n",ftell(fd));
	printf("%ld\n",ftell(fd1));
	//itirate thru and take buffer while writing it in file using fprintf and changing color
	while((ch = fgetc(fp1)) != EOF)
	{
		if (ch == '\n')
		{
			dist = ftell(fp1) - ftell(fp) - 1;

			buffer = malloc((dist) * sizeof(char));
			fseek(fp1, -(dist + 1), SEEK_CUR);
			fread(buffer, dist, 1, fp1);
			//Compare for preprocessor directives
			if(buffer[0] == '#')
			{
				fprintf(fd,"<span style='color: purple'>%s</span>",buffer);
				printf("xyzzzzzzzzzzzz:%s\n",buffer );
				preprocessor(buffer, dist, fd);
				fprintf(fd, "\n");
			}
			else
			{
				//fprintf(fd,"<span style='color: blue'>%s</span>", buffer);
				fprintf(fd, "\n");
				i = 0;
				while(i < dist)
				{
					char ch = '\0';
					int k = 0;
					int q;
					if(buffer[i] == 34)
					{
						printf("Litteral : ");
						do
						{
							fprintf(fd,"<span style='color: green'>%c</span>", buffer[i]);
							printf("%c", buffer[i]);
							i++;
						}while(buffer[i] != 34);

						fprintf(fd,"<span style='color: green'>%c</span>", buffer[i]);
						//	printf("%c\n", buffer[i]);
					}
					if(buffer[i] == '/' && buffer[i + 1] == '/')
					{
						while(i < dist)
						{
							fprintf(fd,"<span style='color: blue'>%c</span>", buffer[i]);
							i++;
						}
						continue;
					}
					if(buffer[i] == 39)
					{
						printf("character constant: ");
						do
						{
							printf("%c", buffer[i]);
							fprintf(fd,"<span style='color: firebrick'>%c</span>", buffer[i]);
							i++;
						}while(buffer[i] != 39);
						fprintf(fd,"<span style='color: firebrick'>%c</span>", buffer[i]);
						//		printf("%c\n", buffer[i]);
					}
					if(buffer[i] == ' ')
					{
						fprintf(fd," ");
					}
					if(buffer[i] == '\t')
					{
						fprintf(fd,"\t");
					}
					while (buffer[i] != ' ' && buffer[i] != '\t' && !(ch = operator_checking(&buffer[i])))
					{
						word[k++] = buffer[i++];
						if(i == dist)
						{
							break;
						}
					}
					//					printf("%s\n", word);
					if (isdigit(word[0]))
					{

						fprintf(fd,"<span style='color: darkgreen'>%s</span>", word);
						printf("constant : %s \n", word);
					}
					else if (isalpha(word[0]))
					{
						flag = keyword_checking(word);
						if(ch == '\0')
						{
							if(flag)
							{
								fprintf(fd,"<span style='color: white'>%s </span>", word);
							}
							else
							{
								fprintf(fd,"<span style='color: GoldenRod'>%s </span>", word);
							}
						}
						else
						{
							if(flag)
							{
								fprintf(fd,"<span style='color: white'>%s</span>", word);
							}
							else
							{
								fprintf(fd,"<span style='color: GoldenRod'>%s</span>", word);
							}
						}
					}
					if (ch != '\0')
					{
						printf("operator : %c \n",ch);
						fprintf(fd,"<span style='color: Fuchsia'>%c</span>", ch);
						ch = '\0';
					}
					i++;
					for(k = 0; k <25; k++)
					{
						word[k] = '\0';
					}
					//					printf("Word after freeing : %s\n", word);
				}
				//				printf("Line ended\n");
			}
			fseek(fp1,1,SEEK_CUR);
			//		printf("%s\n", buffer);
			fseek(fp, dist + 1, SEEK_CUR);
		}
	}
	fprintf(fd, "</pre>\n");
	fprintf(fd, "</body>\n");
	fprintf(fd, "</html>\n");
}
//Searching for preprocessor
void preprocessor(char *buffer, int size, FILE *fd)
{
	int i = 0, j;
	//header file 
	if(buffer[i] == '#')
	{
		printf("Preprocessor directive : ");
		while(buffer[i] != ' ')
		{
			printf("%c", buffer[i]);
			//<span style='color: blue'>G</span>
			//fprintf(fd,"<span style='color: blue'>%c</span>", buffer[i]);
			i++;
		}
		printf("\n");
		i++;
		if(buffer[i] == '<' || buffer[i] == '"')
		{
			printf("Header file : %s\n", &buffer[i]);
			j = i;
			while(buffer[j] != '\0')
			{
				fprintf(fd,"<span style='color: red'>%c</span>", buffer[j]);
				j++;
			}
		}
	}
}
int keyword_checking(char *buffer)
{
	for (int i = 0; i < 32; i++)
	{
		char *key = (char *)malloc(strlen(keyword[i]));;
		strcpy(key, keyword[i]);
		//		printf("Biuffer is %s  \t key is %s\n", buffer, key);
		if (strcmp(buffer,key) == 0)
		{
			//			printf("keyword match\n");
			printf("Keyword : %s\n", buffer);
			return 0;
		}
	}
	printf("Identifier: %s\n", buffer);
	return -1;
}

char operator_checking(char*buffer)
{
	for (int i = 0; i < 16; i++)
	{
		if (*buffer == operator[i])
		{
			return *buffer;
		}
	}
	return 0;
}
