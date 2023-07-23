#include"image_reading.h"

void Priority(string mystr, int& hit, int& miss, queues<int>& pri)
{
	bool hitflag = false;
	bool missflag = false;
	queues<int> tempQ;
	while (pri.isempty() == false)
	{
		int t = pri.Front();
		pri.dequeue();
		if (t == stoi(mystr))
		{
			hitflag = 1;
			continue;
		}
		tempQ.enqueu(t);
	}
	if (hitflag == false)
		missflag = 1;
	hit += hitflag;
	miss += missflag;
	while (tempQ.isempty() == false)
	{
		int t = tempQ.Front();
		tempQ.dequeue();
		pri.enqueu(t);
	}
	pri.enqueu(stoi(mystr));
	if (pri.sizeofqueue() > 4)
		pri.dequeue();
}
string RemoveSpecial(string str)
{
	string out = "";
	bool flag = true;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '+' || str[i] == ' ' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^' || str[i] == '\\'|| (str[i] == '_' && !flag))
		{
			out.push_back(str[i]);
			continue;
		}
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			out.push_back(str[i]);
			continue;
		}
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			out.push_back(str[i]);
			continue;
		}
		if (str[i] >= '0' && str[i] <= '9')
		{
			out.push_back(str[i]);
			continue;
		}
		if (flag && str[i] == '|')
		{
			out = out + " |";
			flag = false;
			continue;
		}
		if (!flag && str[i] == '|')
		{
			out = out + "| ";
			flag = true;
			continue;
		}
		out = out + " " + str[i] + " ";
	}
	return out;
}
stringstream seperateTag(stringstream & ss)
{
	stringstream out;
	while (!ss.eof())
	{
		string str = "";
		getline(ss, str, '\n');
		out << RemoveSpecial(str) << "\n";
	}
	return out;
}
stringstream updatefile(string name)
{
	fstream red;
	red.open(name, ios::in);
	stringstream ss;
	ss << red.rdbuf();
	red.close();
	return seperateTag(ss);
}
bool isOpeningTag(string str)
{
	if (str.length() < 3)
		return false;
	if (str[0] == '|' && str[str.length() - 1] == '|' && str[1] != '\\')
		return true;
	return false;
}
bool isClosingTag(string str)
{
	if (str.length() < 4)
		return false;
	if (str[0] == '|' && str[str.length() - 1] == '|' && str[1] == '\\')
		return true;
	return false;
}
string UpdatedTag(string str)
{
	string out;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			out.push_back(str[i]);
		if (str[i] >= 'A' && str[i] <= 'Z')
			out.push_back(str[i]);
		if (str[i] >= '0' && str[i] <= '9')
			out.push_back(str[i]);
	}
	return out;
}
string StackToString(stack <string> st)
{
	string out = "";
	stack <string> tempStack;
	while (!st.isempty())
	{
		tempStack.push(st.Peek());
		st.pop();
	}
	while (!tempStack.isempty())
	{
		out = out + tempStack.Peek();
		tempStack.pop();
	}
	return out;
}
string ReadFile(string name,string srcFilename,int & hit,int & miss, queues<int>& pri)
{
	stringstream ss = updatefile(name);
	string  substr = "", exprString = "";
	bool flag = false;
	stack <string> output;
	stack<string> Tags;
	while (!ss.eof())
	{
		getline(ss, substr, '\n');
		stringstream tempstream;
		tempstream << substr;
		while (tempstream >> substr)
		{
			//cout << substr << " ";
			if (isOpeningTag(substr))
			{
				Tags.push(UpdatedTag(substr));
				string tempStr = UpdatedTag(substr);
				if (tempStr == "postexp" || tempStr == "preexp" || tempStr == "solexp" || tempStr == "src" || tempStr == "priorty")
					flag = true;
			}
			else if (isClosingTag(substr))
			{
				string tempStr = UpdatedTag(substr);
				if (Tags.isempty())
					return StackToString(output) + "\n\t\t\t[SYNTAX ERROR]\n";
				if (tempStr != Tags.Peek())
					return StackToString(output) + "\n\t\t\t[SYNTAX ERROR]\n";
				Tags.pop();
				if (tempStr == "postexp")
				{
					output.push(InfixToPostfix(exprString) + " ");
					flag = false;
				}
				else if (tempStr == "preexp")
				{
					output.push(InfixToPrefix(exprString) + " ");
					flag = false;
				}
				else if (tempStr == "solexp")
				{
					string temp = InfixToPrefix(exprString);
					if (temp == "[INVALID EXPRESSION]")
						output.push(temp + " ");
					else
					{
						output.push(evaluatePrefix(temp) + " ");
					}
					flag = false;
				}
				else if (tempStr == "src")
				{
					output.push(to_string(CountObject(exprString, srcFilename)));
					flag = false;
				}
				else if (tempStr == "priorty")
				{
					Priority(exprString, hit, miss, pri);
					flag = false;
				}
				else if (tempStr == "tab")
				{

					output.push("\t");
				}
			}
			else if (flag == false)
			{
				exprString = "";
				output.push(substr + " ");
			}
			else if (flag == true)
			{
				exprString = exprString + substr;
			}
		}
		output.push("\n");
	}
	return StackToString(output);

}