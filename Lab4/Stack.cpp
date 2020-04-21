//---------------------------------------------------------------------------

#pragma hdrstop

#include "Stack.h"

Stack::Stack()		//конструктор стека
{
	size=0;
	head=nullptr;
}
Stack::~Stack()		//деструктор стека
{
	while(size)
	{
		char temp=pop_front();
    	}
}
int Stack::getsize()		//получение размера стека
{
    return size;
}
void Stack::push_front(char data)   //вставить в стек
{
	head = new Node(data, head);
	size++;
}
char Stack::pop_front()     //извлечь из стека
{
	Node* temp=head;
	char ch=temp->data;
	head=head->pNext;
	delete temp;
	size--;
	return ch;
}
char Stack::look()       //получить первый элемент стека
{
	if (!head)
	{
		return ' ';
	}
	return head->data;
}
int priority(char data)      //определить приоритет знака
{
	switch(data)
	{
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':
			return 2;
		case '(':
			return 1;
		default :
			return 0;
	}
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
