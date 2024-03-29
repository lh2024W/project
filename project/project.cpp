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
void createOrder(Car* car, Car* cars, ServiceOrder* order, ServiceOrder* orders, int n, int m);
/// <summary>
/// вывод информации о заказе на экран
/// </summary>
/// <param name="car">информация об автомобиле</param>
/// <param name="dateTime">дата и время заказа</param>
/// <param name="description">описание работ</param>
void displayOrder(Car* car, Car* cars, ServiceOrder* order, ServiceOrder* orders, int n, int m);
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
void choiceMenuOrders(Car* car, Car* cars, ServiceOrder* order, ServiceOrder* orders, int n, int m);
/// <summary>
/// поиск по номеру авто в массиве Cars
/// </summary>
/// <param name="cars">массив Cars</param>
/// <param name="n">количество элементов массива Cars</param>
void findAutoInFile(Car* car, Car* cars, int n);
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
				cout << "1 - Создание автомобиля\n 2 - Вывод информации об автомобиле\n 0 - Выход\n\n";
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
			do
			{
				cout << "\nВыберите, пожалуйста нужный Вам пункт меню:\n";
				cout << "1 - Создание заказа\n 2 - Вывод информации о заказе\n 0 - Выход\n\n";
				cin >> choice;
				if (choice == 1) { createOrder(&car, cars, &order, orders, 100, 100); }
				if (choice == 2) { displayOrder(&car, cars, &order, orders, 100, 100); }
			} while (choice == 0);
		}

		else if (chapter == 3) {
			do
			{
				cout << "\nВыберите, пожалуйста нужный Вам пункт меню:\n";
				cout << "1 - Вывод всех заказов из файла\n2 - Поиск заказа по номеру автомобиля\n";
				cout << "3 - Удаление заказа из файла\n0 - Выход\n\n";
				cin >> choice;
				if (choice == 1) { showCarsInFile(); }
				if (choice == 2) { cout << "Поиск заказа по номеру автомобиля\n"; }
				if (choice == 3) { cout << "Удаление заказа из файла\n"; }
			} while (choice == 0);
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
	if (choice == 2) { createCar(cars, 100, cars_count); }
	if (choice == 0) { return; }
}

void choiceMenuOrders(Car* car, Car* cars, ServiceOrder* order, ServiceOrder* orders, int n, int m) {
	int choice;
	cout << "Выберите действие: \n";
	cout << "1 - Посмотреть информацию о добавленном заказе.\n";
	cout << "2 - Добавить еще заказ.\n";
	cout << "0 - Выход.\n\n";
	cin >> choice;
	if (choice == 1) { displayOrder(car, cars, order, orders, 100, 100); }
	if (choice == 2) { createOrder(car, cars, order, orders, 100, 100); }
	if (choice == 0) { return; }
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

void createOrder(Car* car, Car* cars, ServiceOrder* order, ServiceOrder* orders, int n, int m) {
	order->order_count;
	cin.ignore();
	car->car_count;
	cout << "Марка автомобиля?\n";
	gets_s(cars[car->car_count].brand);
	cout << "Модель автомобиля?\n";
	gets_s(cars[car->car_count].model);
	cout << "Год выпуска автомобиля?\n";
	gets_s(cars[car->car_count].year);
	cout << "Номерной знак автомобиля?\n";
	gets_s(cars[car->car_count++].licensePlate);
	cout << "Введите дату и время приема заказа.\n";
	gets_s(orders[order->order_count].dateTime);
	cout << "Введите описание работ\n";
	cout << "\n\n";
	gets_s(orders[order->order_count++].description);
	saveOrderInFile(order);
	choiceMenuOrders(car, cars, order, orders, 100, 100);
}

void displayOrder(Car* car, Car* cars, ServiceOrder* order, ServiceOrder* orders, int n, int m) {
	order->order_count;
	car->car_count;
	int index = 0;
	int index1 = 0;
	cout << "Вы добавили заказ:\n\n";
	cout << "Автомобиль: " << "\n";
	for (index = 0; index < car->car_count; index++) {
		cout << "Марка: " << cars[index].brand << "\n\n";
		cout << "Модель: " << cars[index].model << "\n\n";
		cout << "Год выпуска: " << cars[index].year << "\n\n";
		cout << "Номерной знак: " << cars[index].licensePlate << "\n\n";
	}
	for (index1 = 0; index1 < order->order_count; index1++) {
		cout << "Дата и время: " << orders[index1].dateTime << "\n\n";
		cout << "Описание работ: " << orders[index1].description << "\n\n";
	}
	choiceMenuOrders(car, cars, order, orders, 100, 100);
}

void findAutoInFile(Car* car, Car* cars, int n) {

	char number[10];
	cout << "Введите номер авто для поиска: \n";
	cin >> number;
	for (int i = 0; i < n; i++) {
		if (number == cars[i].licensePlate) {
			cout << cars[i].brand, cars[i].model, cars[i].year, cars[i].licensePlate;
		}
		else
			cout << "Авто с таким номером не найдено.\n\n";
	}
}

void saveCarInFile(const Car& car) {
	FILE* save = nullptr;
	fopen_s(&save, "1.txt", "a"); // открываем файл на дозапись в конец

	fwrite(&car, sizeof(Car), 1, save);
	if (save != nullptr) fclose(save);
}

void saveOrderInFile(ServiceOrder* order) {
	FILE* save;
	fopen_s(&save, "2.txt", "a");

	fwrite(&order, sizeof(ServiceOrder), 1, save);
	fclose(save);
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