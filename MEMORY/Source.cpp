#include "Header.h"
#include <iostream>

Memory::Memory()
{
	int b; cout << "Введите размер ОП больше 1024 и явл. степенью двойки\n";
	cin >> b;
	while (!cin || cin.peek() != '\n' || b < 64 || !((b & (b - 1)) == 0))
	{
		clean();
		cout << "Введите размер памяти больше 1024 и явл. степенью двойки\n"; cin >> b;
	}
	int a; cout << "Введите размер ВЗУ больше 1024 и явл. степенью двойки\n";
	cin >> a;
	while (!cin || cin.peek() != '\n' || a < 64 || !((a & (a - 1)) == 0))
	{
		clean();
		cout << "Введите размер памяти больше 1024 и явл. степенью двойки\n"; cin >> a;
	}
	OP_syze = b / 32;
	EM_syze = a / 32;
	OP.resize(OP_syze); EM.resize(EM_syze);
	lists_quantity = (a+b) / 32;
	catalog.resize(lists_quantity);
}


void Memory::Generation_Pages() {
	for (int i = 0; i < OP_syze; i++) {
		OP[i].addr = i; OP[i].Number = i;
		if(i == 0)
		catalog[i].addr = OP[i].addr;
		else
		catalog[i].addr = OP[i].addr * 32;
		catalog[i].info = i;
		catalog[i].virt_addr = OP[i].addr;
	}

	for (int i = 0; i < EM_syze; i++) {
		EM[i].addr = i; EM[i].Number = OP_syze + i;
		catalog[OP_syze + i].addr = EMD;
		catalog[OP_syze + i].info = OP_syze + i;
		catalog[OP_syze + i].virt_addr = EM[i].addr;
	}
}


void Memory::Read_Page()
{
	int nomer, adr; cout << "Введите номер виртуального листа\n";
	cin >> nomer;
	while (!cin || cin.peek() != '\n' || nomer < 0 || nomer >= lists_quantity)
	{
		clean();
		cout << "Введите номер виртуального листа\n"; cin >> nomer;
	}
	if (catalog[nomer].addr == EMD) {

		Swapping(adr, nomer);
		Page *p = &OP[adr];
		cout << "\nВиртуальный лист N " << nomer << endl;
		cout << "Находилась в ВЗУ\n";
		cout << p->count << " - значение обращений\n";
		(p->M) ? cout << "Страница грязная - значение: " << p->info << endl : cout << "Страница чистая\n";
		(p->R) ? cout << "В последнее время обращение было\n" : cout << "В последнее время обращения не было\n\n";
		Request_alg(nomer);
	}
	else {
		Page *p = &OP[catalog[nomer].virt_addr];
		cout << "\nВиртуальный лист N " << nomer << endl;
		cout << "Находится в ОП\n";
		cout << "Адрес ячейки - " << catalog[nomer].addr << endl;
		cout << p->count << " - значение обращений\n";
		(p->M) ? cout << "Страница грязная - значение: " << p->info << endl : cout << "Страница чистая\n";
		(p->R) ? cout << "В последнее время обращение было\n" : cout << "В последнее время обращения не было\n\n";
		Request_alg(nomer);
	}
}

void Memory::Swapping(int& address, int nomer)
{
	int min = 255u;
	for (Page& p_old : OP) if (p_old.count.to_ullong() < min) min = p_old.count.to_ullong();
	for (Page p_old : OP)
		if (p_old.count.to_ullong() == min) {
			Page p = EM[catalog[nomer].virt_addr];
			address = p_old.addr;
			p_old.addr = catalog[nomer].virt_addr;
			catalog[p_old.Number].addr = EMD;
			catalog[p_old.Number].virt_addr = p_old.addr;
			catalog[nomer].addr = address * 32; 
			catalog[nomer].virt_addr = address;
			p.addr = address;
			p_old.count = 0; p.count = 0; p.R = 0; p_old.R = 0;
			OP[address] = p; EM[p_old.addr] = p_old;
			break;
		}
}

void Memory::Change_Page()
{
	 string a;
	int b; cout << "Введите номер виртуального листа\n";
	cin >> b;
	while (!cin || cin.peek() != '\n' || b < 0 || b > lists_quantity)
	{
		clean();
		cout << "Введите номер виртуального листа\n"; cin >> b;
	}
	int address = b;
	if (catalog[b].addr == EMD) Swapping(address, b);
	else address = catalog[b].virt_addr;
	cout << "Внесите модификацию\n";
	cin.get();
	getline(cin, a); 
	Modify(OP[address/32]);
	OP[address].info = a;
	OP[address].f = 1;
	OP[address].M = 1;
	Request_alg(b);
}

void Memory::Request_alg(int b) {

	if (catalog[b].addr == EMD)
	{
		int address;
		Swapping(address, b);
		OP[address].R = 1;
		OP[address].count >>= 1;
		OP[address].count.set(7);
		for (int i = 0; i < OP_syze; i++) {
			if (OP[i].addr != address) {
				OP[i].count >>= 1; OP[i].R = 0;
			}
		}
		
	}
	else {

			OP[catalog[b].virt_addr].R = 1;
			OP[catalog[b].virt_addr].count >>= 1;
			OP[catalog[b].virt_addr].count.set(7);
			for (int i = 0; i < OP_syze; i++) {
				if (OP[i].addr != OP[catalog[b].virt_addr].addr) {
					OP[i].count >>= 1; OP[i].R = 0;
				}
			
		}
	}
}

void Memory::Request()
{
	int b; cout << "Введите номер виртуального листа\n";
	cin >> b;
	while (!cin || cin.peek() != '\n' || b < 0 || b > lists_quantity)
	{
		clean();
		cout << "Введите номер виртуального листа\n"; cin >> b;
	}
	Request_alg(b);
}

void Memory::Modify(Page &p) {
	p.M = 1;
	p.f = 1;
}



void Memory::Generation_Request()
{
	srand(time(0));
	int a, b;
		
	for (int i = 0; i < OP_syze; i++) {
		a = rand() % (OP_syze);
		b = OP[a].Number;
		Request_alg(b);
	}
}

void Memory::Print_Pages() {
	cout << "Блоки в ОП\n";
	for (Page p : OP) {
		cout << p.Number << " - " << p.R << " - " << p.count << " - адрес: " << p.addr*32 << "\n";
	}
	cout << "_______________________________________________________________________________________________________________________\n";
	cout << "Блоки в ВЗУ\n";
	for (Page p : EM) {
		cout << p.Number << " - " << p.R << " - " << p.count << "\n";
	}
	cout << endl << endl;
}

void clean()
{
	cin.clear();
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}