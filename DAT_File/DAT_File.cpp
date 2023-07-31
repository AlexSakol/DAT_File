#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

struct worker {
	char surname[20];
	char department_name[100];
	int salary[3];
	int month_num[3];
	float average;
};

void create_dat_file()
{
	FILE* file = NULL;
	if ((file = fopen("D:\\folder\\temp.dat", "wb")) == NULL)
	{
		system("cls");
		puts("Cannot open file");
		exit(0);
	}
	printf("File is created");
	_getch();
	fclose(file);
}

void write_in_dat_file(int& z)
{
	fflush(stdin);
	z++;
	FILE* file = NULL;
	worker w;
	if ((file = fopen("D:\\folder\\temp.dat", "ab")) == NULL)
	{
		system("cls");
		puts("Cannot open file");
		exit(0);
	}
	system("cls");
	printf("Enter worker's data (use whitespace):\nLast name, Department, month_1, salary_1, month_2, salary_2, month_3, salary_3\n");
	scanf("%s %s %d %d %d %d %d %d", &w.surname, &w.department_name, &w.month_num[0], &w.salary[0], &w.month_num[1], &w.salary[1], &w.month_num[2], &w.salary[2]);
	fwrite(&w, sizeof(worker), 1, file);
	fclose(file);
}

int read_from_dat_file()
{
	system("cls");
	FILE* file = NULL;
	worker w = {};
	if ((file = fopen("D:\\folder\\temp.dat", "rb")) == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}
	fread(&w, sizeof(worker), 1, file);
	if (!strcmp(w.surname, ""))
	{
		printf("File is empty\n");
		_getch();
		return (0);
	}
	fseek(file, 0, SEEK_SET);
	int i = 1;
	while (fread(&w, sizeof(worker), 1, file)) printf("Note %d:\t %-15s %-20s %d %d\t%d %d\t%d %d\n\n", i++, w.surname, w.department_name, w.month_num[0], w.salary[0], w.month_num[1], w.salary[1], w.month_num[2], w.salary[2]);
	_getch();
	fclose(file);
	return (1);
}

void edit_note(int& z)
{
	system("cls");
	FILE* file = NULL;
	worker massiv[20] = {};
	if ((file = fopen("D:\\folder\\temp.dat", "rb")) == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}
	int i = 0;
	while (fread((massiv + i), sizeof(worker), 1, file))
	{
		printf("Note %d:\t %-15s %-20s %d %d\t%d %d\t%d %d\n", i + 1, (massiv + i)->surname, (massiv + i)->department_name, (massiv + i)->month_num[0], (massiv + i)->salary[0], (massiv + i)->month_num[1], (massiv + i)->salary[1], (massiv + i)->month_num[2], (massiv + i)->salary[2]);
		i++;
	}
	fclose(file);
	int n;
	i = 0;
	worker w = {};
	printf("Enter number of note ");
	scanf("%d", &n);
	printf("Enter an option:\n1 - Last name\n2 - Department\n3 - Month number 1\n4 - Salary per month 1\n5 - Month number 2\n6 - Salary per month 2\n7 - Month number 3\n8 - Salary per month 3\n9 - Go back\n");
	scanf("%d", &i);
	switch (i)
	{
	case 1: printf("Enter new last name "); scanf("%s", &w.surname); memcpy(massiv[n - 1].surname, &w.surname, sizeof(w.surname)); break;
	case 2: printf("Enter new department name "); scanf("%s", &w.department_name); memcpy(massiv[n - 1].department_name, &w.department_name, sizeof(w.department_name)); break;
	case 3: printf("Enter new month 1 "); scanf("%d", &w.month_num[0]); massiv[n - 1].month_num[0] = w.month_num[0]; break;
	case 4: printf("Enter new salary per month 1 "); scanf("%d", &w.salary[0]); massiv[n - 1].salary[0] = w.salary[0]; break;
	case 5: printf("Enter new month 2 "); scanf("%d", &w.month_num[1]); massiv[n - 1].month_num[1] = w.month_num[1]; break;
	case 6: printf("Enter new salary per month 2 "); scanf("%d", &w.salary[2]); massiv[n - 1].salary[1] = w.salary[1]; break;
	case 7: printf("Enter new month 3 "); scanf("%d", &w.month_num[2]); massiv[n - 1].month_num[2] = w.month_num[2]; break;
	case 8: printf("Enter new salary per month 3 "); scanf("%d", &w.salary[2]); massiv[n - 1].salary[2] = w.salary[2]; break;
	case 9: printf("Exit\n");
		_getch();
		break;
	}
	if (i != 9)
	{
		if ((file = fopen("D:\\folder\\temp.dat", "wb")) == NULL)
		{
			puts("Cannot open file");
			exit(0);
		}
		for (i = 0; i < z; i++) fwrite(massiv + i, sizeof(worker), 1, file);
		fclose(file);
		printf("Note was edited");
		_getch();
	}
}

void delete_note(int& z)
{
	system("cls");
	FILE* file = NULL;
	worker massiv[20] = {};
	if ((file = fopen("D:\\folder\\temp.dat", "rb")) == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}
	int i = 0;
	worker w = {};
	while (fread((massiv + i), sizeof(worker), 1, file))
	{
		printf("Note %d:\t %-15s %-20s %d %d\t%d %d\t%d %d\n", i + 1, (massiv + i)->surname, (massiv + i)->department_name, (massiv + i)->month_num[0], (massiv + i)->salary[0], (massiv + i)->month_num[1], (massiv + i)->salary[1], (massiv + i)->month_num[2], (massiv + i)->salary[2]);
		i++;
	}
	fclose(file);
	int n;
	printf("Enter deleted note number ");
	scanf("%d", &n);
	for (i = n - 1; i < 19; i++) memcpy(massiv + i, massiv + i + 1, sizeof(worker));
	if ((file = fopen("d:\\folder\\temp.dat", "wb")) == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}
	for (i = 0; i < z; i++) fwrite(massiv + i, sizeof(worker), 1, file);
	fclose(file);
	printf("Note was deleted");
	z--;
	_getch();
}

void zadacha(int& z)
{
	system("cls");
	int i = 0, j;
	FILE* file = NULL;
	if ((file = fopen("d:\\folder\\temp.dat", "rb")) == NULL)
	{
		puts("Cannot open file");
		exit(0);
	}
	worker massiv[20] = {};
	while (fread((massiv + i), sizeof(worker), 1, file))
	{
		printf("Note %d:\t %-15s %-20s %d %d\t%d %d\t%d %d\n", i + 1, (massiv + i)->surname, (massiv + i)->department_name, (massiv + i)->month_num[0], (massiv + i)->salary[0], (massiv + i)->month_num[1], (massiv + i)->salary[1], (massiv + i)->month_num[2], (massiv + i)->salary[2]);
		(massiv + i)->average = ((massiv + i)->salary[0] + (massiv + i)->salary[1] + (massiv + i)->salary[2]) / 3.;
		i++;
	}
	fclose(file);
	char dep[100];
	int month;
	printf("Enter department name ");
	scanf("%s", &dep);
	printf("Enter month number ");
	scanf("%d", &month);
	int sum = 0;
	for (i = 0; i < 20; i++) if (strcmp(dep, (massiv + i)->department_name) == 0) for (j = 0; j < 3; j++) if (month == ((massiv + i)->month_num[j])) sum += ((massiv + i)->salary[j]);
	printf("Amount per month %d  for -%s- is %d\n", month, dep, sum);
	_getch();
	system("cls");
	float b[20];
	char** fam = new char* [20];
	for (i = 0; i < 20; i++) fam[i] = new char[50];
	for (i = 0; i < 20; i++) for (j = 0; j < 20; j++) fam[i][j] = '\0';
	j = 0;
	int s = 0;
	for (i = 0; i < 20; i++)
		if (strcmp((massiv + i)->department_name, dep) == 0)
		{
			b[j] = (massiv + i)->average;
			strcpy(fam[j++], (massiv + i)->surname);
			s++;
		}
	int buf;
	char buf_t[100];
	for (i = 0; i < s - 1; i++) for (j = 0; j < s - i - 1; j++)
	{
		if (b[j] < b[j + 1])
		{
			buf = b[j + 1];
			b[j + 1] = b[j];
			b[j] = buf;
			strcpy(buf_t, fam[j + 1]);
			strcpy(fam[j + 1], fam[j]);
			strcpy(fam[j], buf_t);
		}
	}
	printf("List of employees in descending order of salary \n");
	printf("Last name\tSalary\n");
	for (i = 0; i < s; i++) printf("%s\t%-10.2f\n", fam[i], b[i]);
	_getch();
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i = 1, k, z = 0;
	char* locale = new char[100];
	while (i)
	{
		system("cls");
		printf("Notes in base %d\n", z);
		printf("Choose an option:\n1 - Create new file\n2 - Read from file\n3 - Edit\n4 - Amount and sorting\n5 - Exit\n");
		scanf("%d", &k);
		fflush(stdin);
		switch (k)
		{
		case 1: system("cls"); create_dat_file(); break;
		case 2: system("cls"); read_from_dat_file(); break;
		case 3: system("cls");  printf("1 - Add a worker\n2 - Edit worker\n3 - Delete worker\n4 - Go back\n");
			int q;
			scanf("%d", &q);
			fflush(stdin);
			switch (q)
			{
			case 1: write_in_dat_file(z); break;
			case 2:	edit_note(z); break;
			case 3:	delete_note(z); break;
			case 4: break;
			}
			break;
		case 4: zadacha(z); break;
		case 5:	i = 0; printf("Exit\n"); break;
		}
	}
}
