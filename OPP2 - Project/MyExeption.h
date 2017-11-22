#pragma once
#include<string>

class MyExeption
{
public:
	MyExeption(const std::string &msg);
	~MyExeption();
	std::string getMessge() { return m_msg; } ;
private:
	std::string m_msg;
};

