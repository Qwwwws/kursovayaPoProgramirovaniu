// конструктор вызывается при создании объекта класса. диструктор вызывается при уничтожении объекта класса 

#include <vector>
#include <conio.h>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int stek = 10; // max размер стека
class Node {
private:
	int key;
	Node* p;
public:
	int poluchitKey() {
		return this->key;
	}
	Node* poluchitNode() {
		return this->p;
	}
	// setter - устанавливает значение, getter - получает
	void setNode(Node* p) {
		this->p = p;

	}
	/*Node(): key{}, p{}{}*/
	Node() {
		this->key = 0;
		this->p = nullptr; // nullptr - ничего. 
	} // - это дефолтный конструктор. 
	Node(int chislo) {
		this->key = chislo;
		this->p = nullptr;
	} // - это дополнительный контруктор или же перегрузка дефолтного конструктора. перегрузка - 
	/*
	void f(){
	void f(...)
	простым языком добавление новых параметров из-за которых меняется логика.
	}
	*/
	Node(int znachenie, Node* pointer) {
		this->key = znachenie;
		this->p = pointer;
	}
	~Node() { delete p; }
};

class Stack {
private:
	Node* golova; // последний элемент стэка
public:
	Stack() {
		this->golova = nullptr;
	}
	~Stack() { delete golova; }

	bool nichego() {
		if (this->golova == nullptr) {
			return true;
		} // проверка на пустоту стека, если пустой, то true
		return false; // если в nichego что-то есть, то это уже не ничего, а что-то, поэтому false
	}

	bool shtoto() { // проверка на полноту
		if (dlinnaSteka() == stek) {
			return true;
		}
		return false;
	}

	int dlinnaSteka() {
		int i = 1;
		Node* tekushieZnachenie; // указатель на рассматриваемый Node 
		if (nichego()) {
			return 0;
		} // проверка пустой ли массив
		tekushieZnachenie = this->golova;

		while (tekushieZnachenie != nullptr) {
			++i;
			tekushieZnachenie = tekushieZnachenie->poluchitNode();
		} // ищем длинну стека
		return i;
	}
	void push(int dobovlyaemiElement) { // добавление эллемента в стек
		if (shtoto()) {
			cout << "Stack is full lmao :D" << endl; // если стек полный, то как бы добавить ничего нельзя
			return;
		}

		Node* buffer = new Node(dobovlyaemiElement, this->golova);

		/* если бы не было указателя,
		то переменная бы исчезла сразу после того, как стек не полный, а так она будет напрямую в памяти */

		this->golova = buffer;
	}

	void udalenie() {
		if (nichego()) {
			cout << "Stack is empty lmao :D" << endl;
			return;
		} // проверка на пустоту
		Node* buffer = this->golova;
		this->golova = buffer->poluchitNode();

		cout << buffer->poluchitKey() << endl;

		buffer->setNode(nullptr);
		delete buffer;
	}
	void udalenieStack() { // удаление всего стека
		if (nichego()) {
			cout << "Stack is empty lmao :D" << endl;
			return;
		} // проверка на пустоту
		delete this->golova;
		this->golova = nullptr;
	}
	void vivodVsegoStack() {
		if (nichego()) {
			cout << "Stack is empty lmao :D" << endl;
			return;
		} // проверка на пустоту

		Node* buffer = this->golova;
		while (buffer->poluchitNode() != nullptr) {
			cout << buffer->poluchitKey() << endl;
			buffer = buffer->poluchitNode();
		}
		cout << buffer->poluchitKey() << endl;
	}

	Stack* kopirovanie() {
		Stack* buffer = new Stack();
		if (this->nichego()) {
			return buffer;
		}
		vector<Node*> stackNodes;
		Node* current = this->golova;
		while (current->poluchitNode() != nullptr) {
			stackNodes.push_back(current);
			current = current->poluchitNode();
		}
		stackNodes.push_back(current);
		for (int i = stackNodes.size() - 1; i >= 0; --i) {
			buffer->push(stackNodes.at(i)->poluchitKey());
		}
	}
	void inventirovanieStack() {
		if (nichego()) {
			cout << "Stack is empty lmao :D" << endl;
			return;
		} // проверка на пустоту
		vector<Node*> stackNodes; // вектор, который хранит все node
		Node* buffer = this->golova; // копия ссылки на последний элемент стека
		while (buffer->poluchitNode() != nullptr) {
			stackNodes.push_back(buffer); // в этом цикле мы пушим буффер, чтобы его инвентировать
			buffer = buffer->poluchitNode(); // сдвиг на след элемент в стеке
		}
		stackNodes.push_back(buffer); // добавляем в вектор последний элемент
		reverse(stackNodes.begin(), stackNodes.end()); // разворот вектора задом наперёд
		for (int i = 0; i < stackNodes.size() - 1; i++) { // проходим по всем элементам вектора
			stackNodes[i]->setNode(stackNodes[i + 1]); // меняем в цикле связи, чтобы стек стал обратным
		}
		stackNodes[stackNodes.size() - 1]->setNode(nullptr);
		this->golova = stackNodes.at(0); // изменяет ссылку на голову массива
	}
	void setGolova(Node* golova) {
		this->golova = golova;

	}
	Node* poluchitGolova() {
		return this->golova;
	}
	void dobalevnieStackKStak(Stack* stack) {
		//скопировать стек-аргумент
		Stack* appendCopy = stack->kopirovanie(); // appendCopy - dobalevnieStackKStak Copy
		//найти первый элемент добавляемого
		Node* buffer = this->golova;
		while (buffer->poluchitNode() != nullptr) {
			buffer = buffer->poluchitNode();
		}
		//поменять в нём указатель
		buffer->setNode(this->golova);
		//поменять голову добавляемого стека на nullptr
		appendCopy->setGolova(nullptr);
		//удалить копию добавляемого стека
		delete appendCopy;
	}
	void deleteDuplicates() {
		if (this->nichego()) {
			printf("Stack is empty lmao");
			return;
		}
		//копируем ссылки на элементы в вектор
		vector<Node*> nodes;
		Node* buffer = this->golova;
		while (buffer->poluchitNode() != nullptr) {
			nodes.push_back(buffer);
			buffer = buffer->poluchitNode();
		}
		nodes.push_back(buffer);
		//удаляем неуникальные элементы
		bool popped = false;
		while (true)
		{
			set<int> nums;
			popped = false;
			for (int i = 0; i < nodes.size(); i++) {
				if (nums.contains(nodes[i]->poluchitKey())) { //нашли неуникальный
					popped = true;
					nodes.erase(nodes.begin() + i);
					break;
				}
				nums.insert(nodes[i]->poluchitKey());
			}
			if (!popped) break;
		}
		//чиним связи элементов
		for (int i = 0; i < nodes.size() - 1; i++) {
			nodes[i]->setNode(nodes[i + 1]);
		}
		nodes[nodes.size() - 1]->setNode(nullptr);
		//устанавливаем новую голову стэка
		this->golova = nodes[0];
	}
};




int main()
{
	setlocale(LC_ALL, "rus");
	Stack* stack = new Stack();
	while (true) {
		system("cls");
		printf(
			"Размер стека: %i\n"
			"Выберите операцию:\n\n"
			"1 - удалить верхний элемент стека\n"
			"2 - вывести стек на экран\n"
			"3 - Добавить элемент в стек\n"
			"4 - инвертировать стек\n"
			"5 - очистить стек\n"
			"6 - добавить стек\n"
			"7 - удалить дубликаты\n"
			"0 - выход\n"
			"Введите ваш выбор: "
			, stack->dlinnaSteka());
		char choice;
		cin >> choice;
		if (!('0' <= choice <= '7')) continue;
		printf("\n");
		int i = choice - '0';
		switch (i) {
		case 0:
			delete stack;
			return 0;
		case 1:
			stack->udalenie();
			break;
		case 2:
			stack->vivodVsegoStack();
			break;
		case 3:
			printf("Введите новый элемент стека: ");
			int buffer;
			cin >> buffer;
			stack->push(buffer);
			break;
		case 4:
			stack->inventirovanieStack();
			break;
		case 5:
			stack->udalenieStack();
			break;
		case 6:
			stack->dobalevnieStackKStak(new Stack());
			break;
		case 7:
			stack->deleteDuplicates();
			break;
		}
		printf("\nНажмите Enter, чтобы продолжить...");
		_getch();
	}
}