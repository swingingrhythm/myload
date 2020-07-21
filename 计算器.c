#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char judge_char(char ch);
int get_num(int start, int stop);
int put_num(double num);
double pop_num(void);
int put_op(char op);
char pop_op(void);
int calculation(char op);

char str[MAX];
double num_val[MAX];
char operator[MAX];
char str_temp[MAX];
char legal_char[] = { '(', ')', '.', '+', '-', '*', '/', '=', '0','1', '2', '3', '4', '5', '6', '7', '8', '9','\0'};

int main(void)
{
	int j, start, stop;
	int i;

	for (i = 0; i < MAX; i++)
	{
		str[i] = operator[i] = str_temp[i] = '\0';
		num_val[i] = 0.000;
	}

	printf("go：\n");
	scanf_s("%s", str, MAX);

	int len = (int)strlen(str);
	char tag;

	i = 0;
	while (i < len)
	{
		tag = judge_char(str[i]);
		
		switch (tag)
		{
		case '(':
			if (str[i + 1] == '-')
			{
				start = i + 1;
				for (j = i + 2; j < len; j++)
				{
					if (str[j] == ')')
					{
						stop = j;
						i = j;
						get_num(start, stop);
						break;
					}
				}
			}
			else if (str[i + 1] != '-')
			{
				put_op(tag);
			}
			break;
		case 'n':
			start = i;
			for (j = i + 1; j <= len; j++)
			{
				if (judge_char(str[j]) != 'n')
				{
					i = j - 1;
					stop = j - 1;
					get_num(start, stop);
					break;
				}
			}
			break;
		default:
			put_op(tag);
			break;
		}

		i++;
	}

	return 0;
}


char judge_char(char ch)
{
	switch (ch)
	{
	case '(': return '(';
		break;
	case '+': return '+';
		break;
	case '-': return '-';
		break;
	case '*': return '*';
		break;
	case '/': return '/';
		break;
	case ')': return ')';
		break;
	case '=': return '=';
		break;
	case '\0': return '\0';
		break;
	default: return 'n';
		break;
	}
}

int get_num(int start, int stop)
{
	int k, t;
	for (k = 0, t = start; t <= stop; k++, t++)
	{
		str_temp[k] = str[t];
	}
		
	put_num(atof(str_temp));

	for (k = 0; k < MAX; k++)
	{
		str_temp[k] = '\0';
	}

	return 0;
}

int top_num = -1;

int put_num(double val)
{
	if (top_num == MAX - 1)
	{
		printf("erro: stack full, can't push\n");
	}
	else
	{
		top_num++;
		num_val[top_num] = val;								
	}

	return 0;
}

double pop_num(void)
{
	double top_now;
	if (top_num == -1)
	{
		printf("erro: stack empty\n");
		return 1111;
	}
	else
	{
		top_now = num_val[top_num];
		top_num--;
		return top_now;
	}
}

int top_op = -1;

int put_op(char op)
{
	if (top_op == MAX - 1)
	{
		printf("erro: stack full, can't push\n");
	}
	else
	{
		if (top_op == -1)
		{
			top_op++;
			operator[top_op] = op;
		}
		else
		{
			switch (op)
			{
			case '+':					
				if (operator[top_op] == '(')
				{
					top_op++;
					operator[top_op] = op;
				}
				else
				{
					pop_op();
					top_op++;
					operator[top_op] = op;
				}			
				break;
			case '-':
				if (operator[top_op] == '(')
				{
					top_op++;
					operator[top_op] = op;
				}
				else
				{
					pop_op();
					top_op++;
					operator[top_op] = op;
				}
				break;
			case '*':						
				if (operator[top_op] == '(')
				{
					top_op++;
					operator[top_op] = op;
				}
				else if (operator[top_op] == '*' || operator[top_op] == '/')
				{
					pop_op();
					top_op++;
					operator[top_op] = op;
				}
				else
				{
					top_op++;
					operator[top_op] = op;
				}
				break;
			case '/':			
				if (operator[top_op] == '(')
				{
					top_op++;
					operator[top_op] = op;
				}
				else if (operator[top_op] == '*' || operator[top_op] == '/')
				{
					pop_op();
					top_op++;
					operator[top_op] = op;
				}
				else
				{
					top_op++;
					operator[top_op] = op;
				}
				break;
			case '(':
				top_op++;
				operator[top_op] = op;
				break;
			case ')':
				while (operator[top_op] != '(')
				{
					pop_op();
				}
				pop_op();
				break;
			case '=':
				while (top_op != -1)
				{
					pop_op();
				}
				calculation('=');
				break;
			default:
				break;
			}
		}
	}

	return 0;
}

char pop_op(void)
{
	if (top_op == -1)
	{
		printf("erro: stack empty\n");
	}
	else
	{
		calculation(operator[top_op]);
		top_op--;
	}

	return 0;
}

double temp1, temp2;

int calculation(char op)
{
	switch (op)
	{
	case '+':
		temp1 = pop_num();
		temp2 = pop_num();
		put_num(temp1 + temp2);
		break;
	case '-':
		temp1 = pop_num();
		temp2 = pop_num();
		put_num(temp2 - temp1);
		break;
	case '*':
		temp1 = pop_num();
		temp2 = pop_num();
		put_num(temp2 * temp1);
		break;
	case '/':
		temp1 = pop_num();
		temp2 = pop_num();
		if (temp1 == 0.0)
		{
			printf("error: zero divisor\n");
		}
		else
		{
			put_num(temp2 / temp1);
		}
		break;
	case '=':
		printf("result = %f\n\n", num_val[top_num]);
		top_num = top_op = -1;
		return main();
	default:
		break;
	}

	return 0;
}