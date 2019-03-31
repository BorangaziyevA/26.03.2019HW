#include<iostream>
#include<iomanip>
#include<iostream>
#include<fstream>


int buf_size = 0;

int current_size = 0;

using namespace std;

struct Date
{
	int day;

	int month;

	int year;

	void print()
	{
		cout << day << "." << month << "." << year << " ";
	}

};

struct Man
{
	char surname[20];

	char name[20];

	Date date;

	void print()
	{
		cout << name << " " << surname << " ";

		date.print();

		cout << endl;
	}

};

void MS(Man *&ms, const char* name)
{
	for (size_t i = 0; i < current_size; i++)
	{
		if (strcmp(ms[i].name, name))
		{
			for (size_t j = i; j < current_size - 1; j++)
			{
				ms[j] = ms[j + 1];
				i--;
			}
			current_size--;
		}
	}

}

void add(Man *&ms, Man el)
{
	if (buf_size == 0)
	{
		buf_size = 4;
		ms = new Man[buf_size];
	}
	else
	{
		if (buf_size == current_size)
		{
			buf_size *= 2;

			Man* tmp = new Man[buf_size];

			for (size_t i = 0; i < current_size; i++)
			{
				tmp[i] = ms[i];
			}
			delete[] ms;
			ms = tmp;
		}

	}
	ms[current_size++] = el;
}

void erase_last(Man *&ms)
{
	current_size--;
	if (current_size == 0)
	{
		delete[] ms;

		buf_size = 0;
	}
}

void sortbyname(Man *&fs)
{
	for (size_t i = 0; i < current_size; i++)
	{
		for (size_t j = 1; j < current_size; j++)
		{
			if (strcmp(fs[j].name, fs[j - 1].name) == 1)
			{
				swap(fs[j], fs[j - 1]);
			}
		}
	}

}

void sortbysurname(Man *&fs)
{

	for (size_t i = 0; i < current_size; i++)
	{
		for (size_t j = 1; j < current_size; j++)
		{
			if (strcmp(fs[j].surname, fs[j - 1].surname) == 1)
			{
				swap(fs[j], fs[j - 1]);
			}

		}

	}

}

void New(Man &fs)
{
	char c;

	cout << "Введите дату рождения" << endl;

	cin >> fs.date.day >> c >> fs.date.month >> c >> fs.date.year ;

	cout << "Введите имя" << endl;

	cin >> fs.name;

	cout << "Введите фамилию" << endl;

	cin >> fs.surname;


}

void Delete(Man *&el, char ch1[30])
{
	Man* tmp;

	tmp = new Man[current_size--];

	int flag = 0;

	for (size_t i = 0; i < current_size; i++)
	{
		if (!strcmp(ch1, el[i].name))
		{
			flag = 1;
		}

		if (flag == 0)
		{
			tmp[i] = el[i];
		}
		else
			tmp[i] = el[i + 1];

	}

	delete[] el;

	el = tmp;
}

void change(Man *&el, int n)
{

	int flag = 0;

	int tmp;

	char c;

	char text[30];

	el[n - 1].print();


	cout << "1. Редактировать дату рождения" << endl << "2. Редактировать имя" << endl << "3. Редактировать фамилию" << endl;

	cin >> flag;

	if (flag == 1)

	{

		cout << "Введите дату рождения" << endl;

		cin >> el[n - 1].date.day >> c >> el[n - 1].date.month >> c >> el[n - 1].date.year;

	}

	if (flag == 2)

	{

		cout << "Введите имя" << endl;

		cin >> text;

		strcpy_s(el[n - 1].name, text);

	}

	if (flag == 3)

	{

		cout << "Введите фамилию" << endl;

		cin >> text;

		strcpy_s(el[n - 1].surname, text);

	}

}

void poisk(Man *el, char ch[30])
{
	int flag = 0;

	for (size_t i = 0; i < current_size; i++)
	{
		if (!strcmp(ch, el[i].name) || !strcmp(ch, el[i].surname))
		{
			el[i].print();
		}

	}

}

int main()
{
	setlocale(LC_ALL, "");

	ifstream in_file("in.txt");

	Man* ms = 0;

	Man tmp_man;

	char c;

	while (!in_file.eof())
	{
		in_file >> tmp_man.name >> tmp_man.surname >> tmp_man.date.day >> c >> tmp_man.date.month >> c >> tmp_man.date.year;

		add(ms, tmp_man);
	}

	for (size_t i = 0; i < current_size; i++)
	{
		ms[i].print();
	}

	int task;

	int flag;

	char ch1[30];

	int fl;

	do
	{
		cout << "1.Редактирование" << endl << "2.Удаление" << endl << "3.Добавление" << endl << "4.Сортировка" << endl << "5.Поиск" << endl;

		cin >> task;

		switch (task)
		{
		case 1:
			int n;
			do
			{
				cout << "Введите номер человека которого хотите изменить" << endl;
				cin >> n;

				change(ms, n);

				for (size_t i = 0; i < current_size; i++)
				{
					ms[i].print();
				}

				cout << "Продолжить?" << endl;

				cin >> flag;



			} while (flag != 0); break;

		case 2:
			cout << "Введите имя записи которую хотите удалить" << endl;

			cin >> ch1;

			Delete(ms, ch1);

			break;

		case 3:

			New(tmp_man);

			add(ms, tmp_man);

			break;

		case 4:
			int flags;

			cout << "1.Сортировка по имени" << endl << "2.Сортировка по фамилии" << endl;

			cin >> flags;

			if (flags == 1)
			{
				sortbyname(ms);
			}
			else if (flags == 2)
			{
				sortbysurname(ms); break;
			}

		case 5:
			cout << "Введите имя или фамилию записи которую хотите найти" << endl;

			cin >> ch1;

			poisk(ms, ch1);
		}
		cout << endl << endl << endl;

		for (size_t i = 0; i < current_size; i++)
		{
			ms[i].print();
		}



		cout << "Продолжить?" << endl;

		cin >> fl;

	} while (fl != 0);

	system("pause");

	return 0;

}

