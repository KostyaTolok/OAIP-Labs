//---------------------------------------------------------------------------

#include <vcl.h>
#include <ctype.h>
#pragma hdrstop

#include "Task.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Stack.h"
TForm1 *Form1;
Stack stack;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	StringGrid1->Cells[0][0]="Переменная";
	StringGrid1->Cells[1][0]="Значение";
	char temp='a';
	for (int i = 1; i < 6; i++)
	{
		StringGrid1->Cells[0][i]=temp++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	try
	{
		if (Edit1->Text=="")
		{
			throw Exception("Введите выражение!");
		}
		Set<char,'(','/'> signs;
		String OutputStr="";
		AnsiString InputStr=Edit1->Text;
		signs<<'+'<<'-'<<'*'<<'/';
		bool bracket=false;
		int count1=0,count2=0;                          //проверка на правильность
		for (int i = 1; i <= InputStr.Length(); i++)    //введенного выражения
		{
			if (!signs.Contains(InputStr[i])&&InputStr[i]!='('
			&&InputStr[i]!=')'&&!(InputStr[i]>='a'&&InputStr[i]<='e'))
			{
				throw Exception("Неверное выражение!");
			}
			if (signs.Contains(InputStr[i])&&i!=InputStr.Length())
			{
				if (signs.Contains(InputStr[i+1]))
				{
					throw Exception("Нельзя повторять знаки!");
				}
			}
			else if ((InputStr[i]>='a'&&InputStr[i]<='e')&&i!=InputStr.Length())
			{
				if ((InputStr[i+1]>='a'&&InputStr[i+1]<='e'))
				{
					throw Exception("Нельзя повторять переменные!");
				}
			}
			if (i==1&&(signs.Contains(InputStr[i])||InputStr[i]==')'))
			{
				throw Exception("Нельзя начинать с знака или закрывающей скобки!");
			}
			else if (i==InputStr.Length()&&(signs.Contains(InputStr[i])||InputStr[i]=='('))
			{
				throw Exception("Нельзя заканчивать знаком или открывающей скобкой!");
			}
			if (InputStr[i]=='(')
			{
				bracket=true;
				count1++;
				if (i!=InputStr.Length())
				{
					if (!((InputStr[i+1]>='a'&&InputStr[i+1]<='e')||InputStr[i+1]=='('))
					{
						throw Exception("После открывающей скобки не может быть знаков и закрывающей скобки!");
					}
				}
			}
			if (InputStr[i]==')')
			{
				bracket=false;
				count2++;
				if (i!=InputStr.Length())
				{
					if (!(signs.Contains(InputStr[i+1])))
					{
						throw Exception("После закрывающей скобки не может быть переменных!");;
					}
				}
			}
			if (i==InputStr.Length())
			{
				if (bracket)
				{
					throw Exception("Открывающая скобка не закрыта!");
				}
				else if(count1!=count2)
				{
					throw Exception("Нет открывающей скобки!");
				}
			}
			while(stack.getsize())
			{
				char temp=stack.pop_front();
			}
		}
		for (int i = 1; i <= InputStr.Length(); i++)   //заполнение стека и выходной строки
		{
			char ch=InputStr[i];
			if (ch>='a'&&ch<='e')         //если переменная - помещаем в выходную строку
			{
				OutputStr+=InputStr[i];
			}                               //если знак - помещаем из стека в выходную строку
			else if(signs.Contains(ch))    	//пока его приоритет меньше приоритета
			{                               //знаков из стека

				while(priority(stack.look())>=priority(ch))
				{
					OutputStr+=stack.pop_front();
				}
				stack.push_front(ch);

			}
			else if(ch=='(')      //если открывающая скобка - помещаем в стек
			{
				stack.push_front(InputStr[i]);
			}
			else if(ch==')')      //если закрывающая скобка - извлекаем пока не открывающая скобка
			{
				while(stack.look()!='(')
				{
					OutputStr+=stack.pop_front();
				}
				char del=stack.pop_front();
			}
		}
		while(stack.look()!=' ')     //извлечь оставшиеся символы
		{
			OutputStr+=stack.pop_front();
		}
		Edit2->Text=OutputStr;
		Button2->Enabled=True;
	}
	catch(Exception &ex)
	{
		ShowMessage(ex.Message);
   	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	try
	{
		for (int i = 1; i < 6; i++)    //проверка значений таблицы
		{
			for (int j=1; i < StringGrid1->Cells[1][i].Length(); i++)
			{
				if (!isdigit(StringGrid1->Cells[1][i][j]))
				{
					throw Exception("Неверное значение");
				}
			}
		}
		AnsiString Str=Edit2->Text;
		double values[100];
		double result, temp1, temp2;
		char ch, ch1, ch2;
		int result_index=5;
		for (int i = 1; i < 6; i++)         //заполнение массива массива значений
		{
			ch=StringGrid1->Cells[0][i][1];
			values[int(ch)-'a']=StrToFloat(StringGrid1->Cells[1][i]);
		}
		for (int i = 1; i <= Str.Length(); i++)
		{
			ch=Str[i];
			if (ch>='a'&&ch<='e')          //если переменная помещаем в стек
			{
				stack.push_front(ch);
			}
			else  //если знак извлекаем два верхних числа из стека и проводим операцию
			{
				ch1=stack.pop_front();
				ch2=stack.pop_front();
				temp1=values[int(ch1)-'a'];
				temp2=values[int(ch2)-'a'];
				switch(ch)
				{
					case '+':
						result=temp2+temp1;
						break;
					case '-':
						result=temp2-temp1;
						break;
					case '*':
						result=temp2*temp1;
						break;
					case '/':
						if (temp1==0)
						{
							throw Exception("Деление на ноль!");
						}
						result=temp2/temp1;
						break;
				}
				values[result_index]=result;
				stack.push_front(char(result_index + 'a'));
				result_index++;
			}

		}
		Edit3->Text=result;
	}
	catch(Exception &ex)
	{
		ShowMessage(ex.Message);
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	StringGrid1->Cells[1][1]="0,4";		//заполнение таблицы стандартными значениями
	StringGrid1->Cells[1][2]="2,3";
	StringGrid1->Cells[1][3]="6,7";
	StringGrid1->Cells[1][4]="5,8";
	StringGrid1->Cells[1][5]="9,1";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Edit1->Text="a*(b+c)/(d-e)";		//стандартное выражение
}
//---------------------------------------------------------------------------

