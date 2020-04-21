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
	class Node
	{
        public:
		Node *pNext;
		char data;
		Node(char data, Node *pNext = nullptr)
	   {
			this->data=data;
			this->pNext=pNext;
	   }
	};
	int size;
	Node *head;
};
int priority(char data);
//---------------------------------------------------------------------------
#endif
