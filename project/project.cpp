#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "ColorCursor.h"
using namespace std;

struct Car {
	char brand[20];
	char model[20];
	char year[10];
	char licensePlate[10];
	int car_count = 0;
};

struct ServiceOrder {
	Car car;
	char dateTime[20];
	char description[100];
	int order_count = 0;
};

// списки параметров почти для всех функций были упрощены

/// <summary>
/// функция для окрашивания консоли и постановки курсора
/// </summary>
/// <param name="x">координаты по х</param>
/// <param name="y">координаты по у</param>
/// <param name="color">цвет текста</param>
/// <param name="message">текст</param>
void ColorCursor(int x, int y, int color, string message);
/// <summary>
/// Создание нового автомобиля
/// </summary>
/// <param name="brand">марка автомобиля</param>
/// <param name="model">модель автомобиля</param>
/// <param name="year">год выпуска</param>
/// <param name="licensePlate">номер знака</param>
void createCar(Car* cars, int n, int& car_count);
/// <summary>
/// вывод информации об автомобиле
/// </summary>
/// <param name="brand">марка автомобиля</param>
/// <param name="model">модель автомобиля</param>
/// <param name="year">год выпуска</param>
/// <param name="licensePlate">номер знака</param>
void displayCar(const Car& car);
void displayCars(Car* cars, const int cars_count);
/// <summary>
/// создание нового заказа на обслуживание
/// </summary>
/// <param name="car">информация об автомобиле</param>
/// <param name="dateTime">дата и время заказа</param>
/// <param name="description">описание работ</param>
void createOrder(ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int& order_count);
/// <summary>
/// вывод информации о заказе на экран
/// </summary>
/// <param name="car">информация об автомобиле</param>
/// <param name="dateTime">дата и время заказа</param>
/// <param name="description">описание работ</param>
void displayOrder(const ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int m, int& orders_count);
/// <summary>
/// выбор меню в разделе машины
/// </summary>
/// <param name="cars">массив Cars</param>
/// <param name="n">количество элементов массива Cars</param>
void choiceMenuCars(Car* car, Car* cars, int n, int& cars_count);
/// <summary>
/// выбор меню в разделе заказы
/// </summary>
/// <param name="cars">массив Cars</param>
/// <param name="orders">массив Orders</param>
/// <param name="n">количество элементов массива Cars</param>
/// <param name="m">количество элементов массива Orders</param>
void choiceMenuOrders(ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int m, int& orders_count);
/// <summary>
/// поиск по номеру авто в массиве Cars
/// </summary>
/// <param name="cars">массив Cars</param>
/// <param name="n">количество элементов массива Cars</param>
void findOrderInFile(const ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int m, int& orders_count);
/// <summary>
/// сохранить автомобиль в файл
/// </summary>
/// <param name="cars">структура Сar</param>
void saveCarInFile(const Car& car);
/// <summary>
/// показ автомобилей из файла
/// </summary>
/// <param name="car">структура Сar</param>
/// <param name="cars">массив Cars</param>
/// <param name="n">количество элементов массива Cars</param>
void showCarsInFile();
/// <summary>
/// сохранение заказа в файл
/// </summary>
/// <param name="order">структура Order</param>
void saveOrderInFile(ServiceOrder* order);
void showOrdersInFile();


int main() {

	setlocale(0, "");
	system("title База СТО"); // СДЕЛАЛ ЗАГОЛОВОК ДЛЯ ОКНА

	int chapter;
	int choice;
	Car car = {};
	ServiceOrder order = {};
	Car cars[100];
	int cars_count = 0; // ОБЩЕЕ КОЛИЧЕСТВО АВТО
	ServiceOrder orders[100];
	int orders_count = 0;

	while (true) { // ЦИКЛ БЕСКОНЕЧНЫЙ (пока не введём ноль)
		system("cls");
		ColorCursor(25, 5, 13, "Добрый день! Вас приветствует База данных СТО!\n\n");
		ColorCursor(10, 10, 11, // ТУТ ДОБАВИЛ РАЗБИВКУ ТЕКСТА
			"Выберите, пожалуйста нужный Вам раздел:\n\n\
1 - Автомобили\n\
2 - Заказы на обслуживание\n\
3 - База данных\n\
0 - Выход\n\n");
		cin >> chapter;

		if (chapter == 1) {
			while (true) // ТУТ ТОЖЕ БЕСКОНЕЧНЫЙ ЦИКЛ ДО 0
			{
				system("cls"); // чистим экран
				cout << "\nВыберите, пожалуйста, нужный Вам пункт меню:\n";
				cout << "1 - Создание автомобиля\n 2 - Вывод информации об автомобилях\n 0 - Выход\n\n";
				cin >> choice;
				if (choice == 1) {
					createCar(cars, 100, cars_count);
				}
				else if (choice == 2) {
					displayCars(cars, cars_count);
				}
				else if (choice == 0)
					break; // выходим на внешний цикл
			}
		}

		else if (chapter == 2) {
			while (true)
			{
				cout << "\nВыберите, пожалуйста нужный Вам пункт меню:\n";
				cout << "1 - Создание заказа\n 2 - Вывод информации о заказах\n 0 - Выход\n\n";
				cin >> choice;
				if (choice == 1) { createOrder(order, cars, orders, 100, orders_count); }
				else if (choice == 2) { showOrdersInFile(); }
				else if (choice == 0)
					break;
			} 
		}

		else if (chapter == 3) {
			while (true)
			{
				cout << "\nВыберите, пожалуйста нужный Вам пункт меню:\n";
				cout << "1 - Вывод всех заказов из файла\n2 - Поиск заказа по номеру автомобиля\n";
				cout << "3 - Удаление заказа из файла\n0 - Выход\n\n";
				cin >> choice;
				if (choice == 1) { showOrdersInFile(); }
				else if (choice == 2) { cout << "Поиск заказа по номеру автомобиля\n"; }
				else if (choice == 3) { cout << "Удаление заказа из файла\n"; }
				else if (choice == 0)
					break;
			}
		}

		else if (chapter == 0) {
			system("cls");
			cout << "До свидания!\n";
			Sleep(INFINITE);
		}
	}
}

void choiceMenuCars(Car* car, Car* cars, int n, int& cars_count) {
	int choice;
	cout << "\nВыберите действие\n";
	cout << "1 - Посмотреть информацию о добавленном автомобиле.\n";
	cout << "2 - Добавить еще автомобиль.\n";
	cout << "0 - Выход.\n\n";
	cin >> choice;
	if (choice == 1) { displayCar(*car); }
	else if (choice == 2) { createCar(cars, 100, cars_count); }
	else if (choice == 0) { return; }
}

void choiceMenuOrders(ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int m, int& orders_count) {
	int choice;
	cout << "Выберите действие: \n";
	cout << "1 - Посмотреть информацию о добавленном заказе.\n";
	cout << "2 - Добавить еще заказ.\n";
	cout << "0 - Выход.\n\n";
	cin >> choice;
	if (choice == 1) { showOrdersInFile(); }
	else if (choice == 2) { createOrder(order, cars, orders, 100, orders_count); }
	else if (choice == 0) { return; }
}


void createCar(Car* cars, int n, int& car_count) {
	cin.ignore();
	Car temp;
	cout << "Марка автомобиля?\n";
	gets_s(temp.brand);
	cout << "Модель автомобиля?\n";
	gets_s(temp.model);
	cout << "Год выпуска автомобиля?\n";
	gets_s(temp.year);
	cout << "Номерной знак автомобиля?\n";
	gets_s(temp.licensePlate);
	saveCarInFile(temp);
	cars[car_count++] = temp; // добавляем авто в массив
	choiceMenuCars(&temp, cars, 100, car_count);
}

void displayCar(const Car& car) {

	cout << "Марка: " << car.brand << "\n\n";
	cout << "Модель: " << car.model << "\n\n";
	cout << "Год выпуска: " << car.year << "\n\n";
	cout << "Номерной знак: " << car.licensePlate << "\n\n";
	_getch();
}

void displayCars(Car* cars, const int cars_count) {
	for (int i = 0; i < cars_count; i++)
	{
		displayCar(cars[i]);
	}

	_getch();
}

void createOrder(ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int& order_count) {
	cin.ignore();
	ServiceOrder temp;
	cout << "Марка автомобиля?\n";
	gets_s(temp.car.brand);
	cout << "Модель автомобиля?\n";
	gets_s(temp.car.model);
	cout << "Год выпуска автомобиля?\n";
	gets_s(temp.car.year);
	cout << "Номерной знак автомобиля?\n";
	gets_s(temp.car.licensePlate);
	cout << "Введите дату и время приема заказа.\n";
	gets_s(temp.dateTime);
	cout << "Введите описание работ\n";
	gets_s(temp.description);
	saveOrderInFile(&temp);
	orders[order_count++] = temp;
	choiceMenuOrders(order, cars, &temp, 100, 100, order_count); 
}

void displayOrder(const ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int m, int& orders_count) {
	cout << "Вы добавили заказ:\n\n";
	cout << "Марка автомобиля: " << order.car.brand << "\n\n";
	cout << "Модель автомобиля: " << order.car.model << "\n\n";
	cout << "Год выпуска автомобиля: " << order.car.year << "\n\n";
	cout << "Номерной знак автомобиля: " << order.car.licensePlate << "\n\n";

	cout << "Дата и время: " << order.dateTime << "\n\n";
	cout << "Описание работ: " << order.description << "\n\n";

	//choiceMenuOrders(order, cars, orders, 100, 100, orders_count);
	_getch();
}

void findOrderInFile(ServiceOrder& order, Car* cars, ServiceOrder* orders, int n, int m, int& orders_count) {
	FILE* f = nullptr;
	int key;
	char query[100];
	cout << "Введите номерной знак автомобиля для поиска: ";
	cin.ignore();
	cin.getline(query, 100 - 1);

	fopen_s(&f, "2.txt", "ab+");

	ServiceOrder new_order;
	while (fread(&new_order, sizeof(ServiceOrder), 1, f))
		if (strcmp(query, new_order.car.licensePlate) == 0)
			key = new_order.car.licensePlate;
	fclose(f);
	
	fopen_s(&f, "2.txt", "ab+");
	ServiceOrder order;
	int k = 0;
	while (fread(&order, sizeof(ServiceOrder), 1, f))
	{
		if (key == order.car.licensePlate)
		{
			cout << "Марка автомобиля: " << order.car.brand << "\n\n";
			cout << "Модель автомобиля: " << order.car.model << "\n\n";
			cout << "Год выпуска автомобиля: " << order.car.year << "\n\n";
			cout << "Номерной знак автомобиля: " << order.car.licensePlate << "\n\n";

			cout << "Дата и время: " << order.dateTime << "\n\n";
			cout << "Описание работ: " << order.description << "\n\n";;
			k++;
			_getch();
		}
	}

	if (k == 0)
		cout << "Нет авто с таким номером.";

	fclose(f);
}

void saveCarInFile(const Car& car) {
	FILE* save = nullptr;
	fopen_s(&save, "1.txt", "a"); // открываем файл на дозапись в конец

	fwrite(&car, sizeof(Car), 1, save);
	if (save != nullptr) fclose(save);
}

void saveOrderInFile(ServiceOrder* order) {
	FILE* save = nullptr;
	fopen_s(&save, "2.txt", "a");

	fwrite(&order, sizeof(ServiceOrder), 1, save);
	if (save != nullptr) fclose(save);
}

void showCarsInFile() {
	int i = 0;
	FILE* in = nullptr;
	fopen_s(&in, "1.txt", "r");
	if (in != nullptr) {
		while (!feof(in)) {
			Car temp;
			fread(&temp, sizeof(Car), 1, in);

			cout << "Модель: " << temp.brand << "\n";
			cout << "Марка: " << temp.model << "\n";
			cout << "Год выпуска: " << temp.year << "\n";
			cout << "Номерной знак: " << temp.licensePlate << "\n";
			cout << "\n";
			i++;
		}
		_getch();
	}
}

void showOrdersInFile() {
	int i = 0;
	FILE* in = nullptr;
	fopen_s(&in, "2.txt", "r");
	if (in != nullptr) {
		while (!feof(in)) {
			ServiceOrder temp;
			fread(&temp, sizeof(ServiceOrder), 1, in);

			cout << "Модель: " << temp.car.brand << "\n";
			cout << "Марка: " << temp.car.model << "\n";
			cout << "Год выпуска: " << temp.car.year << "\n";
			cout << "Номерной знак: " << temp.car.licensePlate << "\n";
			cout << "Дата и время: " << temp.dateTime << "\n";
			cout << "Описание работ: " << temp.description << "\n";
			cout << "\n";
			i++;
		}
		_getch();
	}
}
