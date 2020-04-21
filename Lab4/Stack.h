//---------------------------------------------------------------------------

#ifndef StackH
#define StackH
class Stack
{
	public:
	Stack();
	~Stack();
	void push_front(char data);
	char pop_front();
	char look();
    	int getsize();
	private:
	class Node		//элемент стека
	{
        public:
		Node *pNext;	//указатель на следующий элемент стека
		char data;
		Node(char data, Node *pNext = nullptr)		//конструктор элемента стека
	   	{
			this->data=data;
			this->pNext=pNext;
	   	}
	};
	int size;
	Node *head;		//указатель на первый элемент стека
};
int priority(char data);
//---------------------------------------------------------------------------
#endif
