#include "Header.h"
#include <iostream>
int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Memory m;
	m.Generation_Pages();
	m.Print_Pages();
	int choise;
	enum class CHOISE { Request = 1, Change, Info_Page, Info_pages, Generation, Break };
	while (true) {
		cout << "Выберите действие\n1 - Обращение к странице\n2 - Изменить страницу\n3 - Информация о странице\n4 - Информация о всех страницах\n5 - Генерация обращений\n6 - Выйти из программы\n";
		cin >> choise;
		while (!cin || cin.peek() != '\n')
		{
			clean();
			cout << "Введите одно из чисел\n"; cin >> choise;
		}
		switch (CHOISE(choise))
		{
		case CHOISE::Request:
			m.Request();
			break;
		case CHOISE::Change:
			m.Change_Page();
			break;
		case CHOISE::Info_Page:
			m.Read_Page();
			break;
		case CHOISE::Info_pages:
			m.Print_Pages();
			break;
		case CHOISE::Generation:
			m.Generation_Request();
			break;
		case CHOISE::Break:
			cout << "Хорошего Вам дня :)\n";
			return 0;
		default:
			cout << "Напишите одно из чисел, чтобы выбрать действие\n";
			break;
		}
	}
}
