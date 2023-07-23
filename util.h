#pragma once
#include<iostream>
using namespace std;
//Syed Qasim Hussain 21i-0379 Section E&V combined

class indices
{
public:
	int row, col;
	indices(int r = 0, int c = 0)
	{
		row = r;
		col = c;
	}
};
template <class B>
class node {
public:
	B value;
	node<B>* next;
	node(B val) {
		value = val;
		next = NULL;
	}

};
template <class B>
class stack {
public:
	node<B>* top;

	stack() {
		top = NULL;
	}

	bool isempty() {
		return top == NULL;
	}

	void push(B val) {
		node<B>* temp = new node<B>(val);
		temp->next = top;
		top = temp;
	}

	void pop() {
		node<B>* temp = top;
		top = top->next;
		delete temp;

	}

	B Peek() {
		return top->value;

	}

	int sizeofstack() {
		int counter = 0;
		node<B>* temp = top;
		while (temp != NULL) {
			counter++;
			temp = temp->next;
		}
		return counter;
	}

};
template <class B>
class queues {
public:
	node<B>* front;
	node<B>* rear;
	queues() {
		front = NULL;
		rear = NULL;
	}
	bool isempty() {
		return rear == NULL;
	}
	void enqueu(B a) {
		node<B>* temp = new node<B>(a);
		temp->value = a;
		temp->next = NULL;
		if (isempty()) {
			front = temp;
			rear = temp;
		}
		else {
			rear->next = temp;
			rear = temp;

		}

	}
	void dequeue() {
		if (isempty()) {
			return;
		}
		else {
			node<B>* temp = front;
			front = front->next;
			delete temp;
			if (front == NULL)
				rear = NULL;
		}
	}
	B Front() {
		return front->value;
	}
	void print() {
		node<B>* temp = front;
		while (temp != NULL) {
			cout << temp->value << " ";
			temp = temp->next;
		}
	}
	int sizeofqueue() {
		int counter = 0;
		node<B>* temp = front;
		while (temp != NULL) {
			counter++;
			temp = temp->next;
		}
		return counter;
	}
};









bool IsOperand(char C)
{

	if ((C >= '0' && C <= '9') || (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'))
	{

		return true;

	}
	return false;
}


bool IsOperator(char C)
{

	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '^')
		return true;

	return false;
}
int getValue(char op)
{
	int weight = -1;

	switch (op)
	{
	case '+': case '-':
		weight = 1;

		break;
	case '*': case '/':
		weight = 2;

		break;
	case '$': case '^':
		weight = 3;

		break;
	}
	return weight;
}
bool comparePrecedence(char op1, char op2)
{



	int w1 = getValue(op1);
	int w2 = getValue(op2);

	if (w1 == w2)
	{
		if (op1 == '$' || op1 == '^')
		{
			return false;
		}
		else
		{
			return true;
		}


	}
	return w1 > w2;
}

string InfixToPostfix(string mystr)
{
	stack<char> S;

	string postfix = "";
	if(IsOperator(mystr[0]) || IsOperator(mystr[mystr.length()-1]))
		return "[INVALID EXPRESSION]";
	for (int i = 0; i < mystr.length(); i++) {
		if (mystr[i] == ' ')
			continue;

		else if (IsOperator(mystr[i]))
		{
			while (!S.isempty() && S.Peek() != '(' && comparePrecedence(S.Peek(), mystr[i]))
			{
				postfix += S.Peek();
				S.pop();
			}
			S.push(mystr[i]);
		}
		else if (IsOperand(mystr[i]))
		{
			postfix += mystr[i];
		}
		else if (mystr[i] == '(')
		{
			S.push(mystr[i]);
		}
		else if (mystr[i] == ')')
		{
			while (!S.isempty() && S.Peek() != '(') {
				postfix += S.Peek();
				S.pop();
			}
			if (S.isempty())

			{
				return "[INVALID EXPRESSION]";
			}
			S.pop();

		}
		else
		{

			return "[INVALID EXPRESSION]";
		}
	}

	while (!S.isempty()) {
		if (S.Peek() == '(')
		{
			return "[INVALID EXPRESSION]";

		}
		postfix += S.Peek();
		S.pop();
	}

	return postfix;
}

string revString(string mystr)
{
	string result = "";
	stack<char> st;
	for (auto s : mystr)
		st.push(s);
	while (!st.isempty())
	{
		result += st.Peek();
		st.pop();
	}
	return result;
}


string InfixToPrefix(string mystr)
{
	mystr = revString(mystr);

	for (int i = 0; i < mystr.length(); i++)
	{
		if (mystr[i] == ')')
		{
			mystr[i] = '(';

		}
		else if (mystr[i] == '(')
		{
			mystr[i] = ')';

		}
	}
	mystr = InfixToPostfix(mystr);
	if (mystr == "[INVALID EXPRESSION]")
	{

		return mystr;
	}
	else
	{

		return revString(mystr);
	}
}





string evaluatePrefix(string prefixExp) {

	stack<int> OP_ST;
	int size = prefixExp.size() - 1;

	for (int i = size; i >= 0; i--) {

		if (prefixExp[i] <= '9' && prefixExp[i] >= '0')
		{
			OP_ST.push(prefixExp[i] - 48);
		}

		else 
		{
			if (OP_ST.isempty())
			{
				return "[INVALID EXPRESSION]";

			}
			int o1 = OP_ST.Peek();

			OP_ST.pop();

			if (OP_ST.isempty())
			{
				return "[INVALID EXPRESSION]";

			}
			int o2 = OP_ST.Peek();
			OP_ST.pop();

			if (prefixExp[i] == '+')
			{
				OP_ST.push(o1 + o2);

			}
			else if (prefixExp[i] == '-')
			{
				OP_ST.push(o1 - o2);

			}
			else if (prefixExp[i] == '*')
			{
				OP_ST.push(o1 * o2);

			}
			else if (prefixExp[i] == '/')
			{
				OP_ST.push(o1 / o2);

			}
			else
				return "[INVALID EXPRESSION]";

		}
	}
	if (OP_ST.sizeofstack() != 1)
	{
		return "[INVALID EXPRESSION]";
	}
	return to_string(OP_ST.Peek());
}
