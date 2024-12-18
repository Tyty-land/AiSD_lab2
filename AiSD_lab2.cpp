#include <iostream>
#include <string>

using namespace std;

template <typename TYPE>
class LinkedList
{
	struct Node
	{
		TYPE _сontent;
		Node* _next;
		Node* _early;
		Node(const TYPE& value)
		{
			_сontent = value;
			_next = nullptr;
			_early = nullptr;
		};
	};
	class ConStr
	{
		int _val;
	public:
		ConStr(int val) 
		{
			_val = val;
		}
		operator string() const
		{
			string l_str = "";
			int val = _val, cnt = 0;
			while (val != 0)
			{
				l_str += char(48 + (val % 10));
				val = int(val / 10);
				cnt++;
			}
			string r_str = l_str;
			int I = 0;
			while (l_str[I] != '\0')
			{
				r_str[cnt - I - 1] = l_str[I];
				I++;
			}
			return r_str;
		}
		operator int() const
		{
			return _val;
		}
	};
	Node* _head;
	size_t _size;
	TYPE getElem(size_t index) const
	{
		Node* next = this->_head;
		if (index >= 0 && index < this->_size)
		{
			for (size_t i = 0; i < index; i++)
			{
				next = next->_next;
			}
			return next->_сontent;
		}
		else
			throw "(operator[]) - Индекс вышел за пределы списка";
	}
public:
	LinkedList() : _head(new Node(TYPE())), _size(1) {};
	LinkedList(const TYPE& value)
	{
		this->_head = new Node(value);
		this->_size = 1;
	}
	LinkedList(int seed, size_t size)
	{
		srand(seed);
		this->_size = size;
		this->_head = new Node(TYPE(ConStr(rand())));
		Node* next = this->_head;
		for (size_t i = 1; i < this->_size; i++)
		{
			Node* early = next;
			next->_next = new Node(TYPE(ConStr(rand())));
			next = next->_next;
			next->_early = early;
		}
	}
	LinkedList(size_t size, string op_mode)
	{
		this->_size = size;
		this->_head = new Node(TYPE());
		Node* next = this->_head;
		for (size_t i = 1; i < this->_size; i++)
		{
			Node* early = next;
			next->_next = new Node(TYPE());
			next = next->_next;
			next->_early = early;
		}
	}
	//Конструктор компирования
	LinkedList(const LinkedList& other)
	{
		this->_size = other.getSize();
		this->_head = new Node(other.getContentHead());
		Node* next_this = this->_head;
		Node* next_other = other.getHead();
		for (size_t i = 1; i < this->_size; i++)
		{
			Node* early_this = next_this;
			next_other = next_other->_next;
			next_this->_next = new Node(next_other->_сontent);
			next_this = next_this->_next;
			next_this->_early = early_this;
		}
	}
	//Методы
	Node* getNext() const
	{
		return this->_head->_next;
	}
	Node* getHead() const
	{
		return this->_head;
	}
	Node* getEarly() const
	{
		return this->_head->_early;
	}
	TYPE getContentHead() const
	{
		return this->_head->_сontent;
	}
	size_t getSize() const
	{
		return this->_size;
	}
	size_t getMaxSize(const LinkedList& other)
	{
		if (this->_size <= other.getSize())
			return other.getSize();
		return this->_size;
	}
	void setContentHead(const Node& value)
	{
		this->_head->_сontent = value._сontent;
	}
	void push_head(const TYPE& value)
	{
		Node* next = this->_head;
		TYPE new_content = value;
		TYPE old_content = TYPE();
		for (size_t i = 0; i < this->_size; i++)
		{
			old_content = next->_сontent;
			next->_сontent = new_content;
			new_content = old_content;
			if (i + 1 != this->_size)
				next = next->_next;
		}
		next->_next = new Node(new_content);
		next->_next->_early = next;
		this->_size += 1;
	}
	void push_head(const LinkedList& other)
	{
		Node* next = other.getHead();
		for (size_t i = 1; i < other.getSize(); i++)
		{
			next = next->_next;
		}
		while (next->_early != nullptr)
		{
			this->push_head(next->_сontent);
			next = next->_early;
		}
		this->push_head(other.getContentHead());
	}
	void push_tail(const TYPE& value)
	{
		Node* next = this->_head;
		for (size_t i = 1; i < this->_size; i++)
		{
			next = next->_next;
		}
		next->_next = new Node(value);
		next->_next->_early = next;
		this->_size += 1;
	}
	void push_tail(const LinkedList& other)
	{
		Node* next_this = this->_head;
		for (size_t i = 1; i < this->_size; i++)
		{
			next_this = next_this->_next;
		}
		Node* next_other = other.getHead();
		for (size_t i = 1; i < other.getSize(); i++)
		{
			Node* early_this = next_this;
			next_other = next_other->_next;
			next_this->_next = new Node(next_other->_сontent);
			next_this = next_this->_next;
			next_this->_early = early_this;
		}
		this->_size += other.getSize();
	}
	void pop_head()
	{
		Node* next = this->_head;
		Node* early = nullptr;
		for (size_t i = 0; i < this->_size - 1; i++)
		{
			early = next;
			next = next->_next;
			early->_сontent = next->_сontent;
		}
		if (this->_size != 1)
		{
			if (early->_next != nullptr)
				delete early->_next;
			early->_next = nullptr;
			this->_size -= 1;
		}
	}
	void pop_tail()
	{
		Node* next = this->_head;
		for (size_t i = 1; i < this->_size - 1; i++)
		{
			next = next->_next;
		}
		delete next->_next;
		next->_next = nullptr;
		this->_size -= 1;
	}
	LinkedList delete_node(const TYPE& value)
	{
		LinkedList temp(this->_head->_сontent);
		Node* next = this->_head->_next;
		for (size_t i = 1; i < this->_size; i++)
		{
			if (value != next->_сontent)
				temp.push_tail(next->_сontent);
			next = next->_next;
		}
		if (value == temp.getContentHead())
			temp.pop_head();
		return temp;
	}
	//Диструктор
	~LinkedList()
	{
		Node* next = this->_head;
		for (size_t i = 1; i < this->_size - 1; i++)
		{
			next = next->_next;
		}
		while (next->_early != nullptr)
		{
			delete next->_next;
			next->_next = nullptr;
			next = next->_early;
		}
		delete this->_head->_next;
		this->_head->_next = nullptr;
		delete this->_head;
		this->_head = nullptr;
	}
	//операторы
	void operator=(const LinkedList& other)
	{
		Node* next_this = this->_head;
		Node* next_other = other.getHead();
		size_t max_size = this->getMaxSize(other);
		for (size_t i = 0; i < max_size; i++)
		{
			if (next_this != nullptr && next_other == nullptr)
			{
				this->pop_tail();
			}
			else
			{
				if (next_this->_next == nullptr && next_other->_next != nullptr)
				{
					next_other = next_other->_next;
					this->push_tail(next_other->_сontent);
					next_other = next_other->_early;
				}
				next_this->_сontent = next_other->_сontent;
				next_this = next_this->_next;
				next_other = next_other->_next;
			}
		}
		this->_size = other.getSize();
	}
	TYPE& operator[](size_t index) const
	{
		Node* next = this->_head;
		if (index >= 0 && index < this->_size)
		{
			for (size_t i = 0; i < index; i++)
			{
				next = next->_next;
			}
			return next->_сontent;
		}
		else
			throw "(operator[]) - Индекс вышел за пределы списка";
	}
	LinkedList<TYPE> operator+(const LinkedList<TYPE>& other)
	{
		size_t max_size = this->getMaxSize(other);
		LinkedList<TYPE> temp(max_size, "");
		for (size_t i = 0, j = 0; i < this->_size && j < other.getSize(); i++, j++)
		{
			if (this->_size - i > other.getSize())
			{
				temp[i] = this->getElem(i);
				j--;
			}
			else if (other.getSize() - j > this->_size)
			{
				temp[j] = other[j];
				i--;
			}
			else
			{
				if (i >= j)
					temp[i] = this->getElem(i) + other[j];
				else
					temp[j] = this->getElem(i) + other[j];
			}
		}
		return temp;
	}
};

LinkedList<string>* create_home_list(const int& adress_cnt, const int& residents_cnt)
{
	string array_random_name[16]{"Саня", "Тимур", "Катя", "Эльдар", "Иван", "Илья", "Миша", "Андрей", "Дима", "Тимофей", "Никита", "Полина", "Денис", "Аким", "Ярик", "Мики"};
	LinkedList<string>* home_list = new LinkedList<string>[adress_cnt];
	for (size_t i = 0; i < adress_cnt; i++)
	{
		home_list[i][0] = array_random_name[(0 + rand() % (16 - 0))];
		for (size_t j = 1; j < residents_cnt; j++)
		{
			size_t index_random_name = (0 + rand() % (16 - 0));
			home_list[i].push_tail(array_random_name[index_random_name]);
		}
	}
	return home_list;
}
template <typename TYPE>
void drawn_home_list(const LinkedList<TYPE>* home_list, const int& adress_cnt, const int& residents_cnt)
{
	cout << "/Home_List:" << endl;
	for (size_t i = 0; i < adress_cnt; i++)
	{
		cout << "[Adress number " << i + 1 << "]<=>(";
		for (size_t j = 0; j < residents_cnt; j++)
		{
			if (j + 1 != residents_cnt)
				cout << home_list[i][j] << ", ";
			else
				cout << home_list[i][j] << ")";
		}
		cout << endl;
	}
}
template <typename TYPE>
void add_two_numbers(LinkedList<TYPE>& num_first, LinkedList<TYPE>& num_second)
{
	LinkedList<TYPE> temp = num_first + num_second;
	for (size_t i = temp.getSize() - 1; i >= 1; i--)
	{
		if (temp[i] > 9)
		{
			TYPE val_temp = temp[i];
			temp[i] = TYPE(int(temp[i]) % 10);
			temp[i - 1] += TYPE(int(val_temp / 10));
		}
	}
	while (temp[0] > 9)
	{
		TYPE val_temp = temp[0];
		temp[0] = TYPE(int(temp[0]) % 10);
		temp.push_head(TYPE(int(val_temp / 10)));
	}
	for (size_t i = 0; i < temp.getSize(); i++)
		cout << temp[i];
	cout << endl;
	cout << "Результат сложения = " << temp;
}
template <typename TYPE>
LinkedList<TYPE> add_two_numbers(LinkedList<TYPE>& num_first, LinkedList<TYPE>& num_second, string op_mode)
{
	LinkedList<TYPE> temp = num_first + num_second;
	for (size_t i = temp.getSize() - 1; i >= 1; i--)
	{
		if (temp[i] > 9)
		{
			TYPE val_temp = temp[i];
			temp[i] = TYPE(int(temp[i]) % 10);
			temp[i - 1] += TYPE(int(val_temp / 10));
		}
	}
	while (temp[0] > 9)
	{
		TYPE val_temp = temp[0];
		temp[0] = TYPE(int(temp[0]) % 10);
		temp.push_head(TYPE(int(val_temp / 10)));
	}
	return temp;
}
template <typename TYPE>
LinkedList<TYPE> transformator(LinkedList<TYPE> source)
{
	LinkedList<TYPE> temp;
	for (size_t i = 0; i < source.getSize(); i++)
	{
		if (source[i] > 9)
		{
			int num = source[i];
			LinkedList<int> num_list;
			while (num != 0)
			{
				num_list.push_head(num % 10);
				num = int(num / 10);
			}
			num_list.pop_tail();
			for (size_t j = 0; j < num_list.getSize(); j++)
				temp.push_tail(num_list[j]);
		}
		else
			temp.push_tail(TYPE(int(source[i])));
	}
	temp.pop_head();
	return temp;
}
template <typename TYPE>
void mult_two_numbers(LinkedList<TYPE>& num_first, LinkedList<TYPE>& num_second)
{
	LinkedList<TYPE> num_first_cp = transformator(num_first);
	LinkedList<TYPE> num_second_cp = transformator(num_second);
	LinkedList<TYPE> temp = add_two_numbers(num_first_cp, num_first_cp, "");
	int cnt = 0;
	for (size_t i = 0; i < num_second_cp.getSize(); i++)
		cnt += num_second_cp[i] * pow(10, num_second_cp.getSize() - 1 - i);
	for (int i = 1; i < cnt - 1; i++)
		temp = add_two_numbers(temp, num_first_cp, "");
	for (size_t i = 0; i < temp.getSize(); i++)
		cout << temp[i];
	cout << endl;
	cout << "Результат умножения = " << temp;
}
//доп. опер.
template <typename TYPE>
ostream& operator<<(ostream& out, const LinkedList<TYPE> linked_list)
{
	out << "[ ";
	for (size_t i = 0; i < linked_list.getSize(); i++)
	{
		out << linked_list[i];
		if (i + 1 < linked_list.getSize())
			out << ", ";
	}
	out << "]" << endl;
	return out;
}

int main() 
{
	setlocale(LC_ALL, "ru");
	try
	{
		//Проверка функционала
		/*LinkedList<string> Zero;
		LinkedList<string> g(1, 10);
		LinkedList<string> G(2, 5);
		Zero = G;
		for (size_t i = 0; i < g.getSize(); i++)
			cout << g[i] << endl;
		cout << endl;
		g.push_head("12.4");
		for (size_t i = 0; i < g.getSize(); i++)
			cout << g[i] << endl;
		cout << endl;
		for (size_t i = 0; i < G.getSize(); i++)
			cout << Zero[i] << endl;
		cout << endl;
		g.pop_head();
		for (size_t i = 0; i < g.getSize(); i++)
			cout << g[i] << endl;
		cout << endl;
		g.push_head(Zero);
		for (size_t i = 0; i < g.getSize(); i++)
			cout << g[i] << endl;
		for (size_t i = 4; i < 7; i++)
			g[i] = g[0];
		cout << endl;
		for (size_t i = 0; i < g.getSize(); i++)
			cout << g[i] << endl;
		cout << endl;
		g = g.delete_node(g[0]);
		for (size_t i = 0; i < g.getSize(); i++)
			cout << g[i] << endl;*/
		//Задание №9 первая часть лабы
		int n = 2;
		int flat = 100;
		drawn_home_list(create_home_list(flat, n), flat, n);
		//Задание №2 вторая часть лабы
		cout << "Номер 2:" << endl;
		LinkedList<double> list_1(5, "1");
		LinkedList<double> list_2(3, "");
		for (size_t i = 0; i < list_2.getSize(); i++)
		{
			list_1[i] = (i + 1)*2;
			list_2[i] = (i + 1)*2;
		}
		list_1[3] = 4.125135;
		list_1[4] = 120.6;
		list_1[0] = 100.5;
		list_2[2] = 60.6;
		cout << "Ввиде числа = ";
		add_two_numbers(list_2, list_1);
		cout << "Ввиде числа = ";
		mult_two_numbers(list_1, list_2);
		cout << "Первый список = " << list_1 << "Второй список = " << list_2;
	}
	catch (const char* ex)
	{
		cout << "[!] - Исключение: " << ex << endl;
	}
}