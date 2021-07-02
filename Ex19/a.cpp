
/*    Copyright (C) 2021  Saurabh Joshi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stack>
#include <any>
#include <utility>
//#include <typeinfo>
#include <iostream>
#include <sstream>
//#include <memory>
#include <cstdlib>
#include <cassert>
#include <fmt/format.h>
#include <vector>
#include <chrono>

class exprt;
class plus_exprt;
class minus_exprt;
class const_exprt;
class visitort
{
public:
	virtual void visit(plus_exprt *) = 0;
	virtual void visit(minus_exprt *) = 0;
	virtual void visit(const_exprt *) = 0;
};
class exprt
{
public:
	virtual ~exprt() {}
	virtual void visit(visitort &v) = 0;
};

using operandst = std::vector<exprt *>;

class plus_exprt : public exprt
{

	operandst operands;

public:
	operandst &get_operands() { return operands; }
	plus_exprt(operandst &&op) : operands(op) {}
	virtual void visit(visitort &v)
	{
		v.visit(this);
	}
};
class minus_exprt : public exprt
{

	operandst operands;

public:
	operandst &get_operands() { return operands; }
	minus_exprt(operandst &&op) : operands(op) {}
	virtual void visit(visitort &v)
	{
		v.visit(this);
	}
};

class const_exprt : public exprt
{
	std::any val;

public:
	const std::any &getval() { return val; };
	const_exprt(std::any e) : val(e) {}
	void visit(visitort &v)
	{
		v.visit(this);
	}
};

class print_visitort : public visitort
{
	fmt::memory_buffer print_str;

public:
	void print()
	{
		fmt::print("{}\n", print_str.data());
	}
	virtual void visit(plus_exprt *pe)
	{
		fmt::format_to(print_str, "( plus_exprt : ");
		auto op = pe->get_operands();
		for (auto operand : op)
		{
			operand->visit(*this);
		}
		fmt::format_to(print_str, ")");
	}
	virtual void visit(minus_exprt *me)
	{
		fmt::format_to(print_str, "( minus_exprt : ");
		auto op = me->get_operands();
		for (auto operand : op)
		{
			operand->visit(*this);
		}
		fmt::format_to(print_str, ")");
	}
	void visit(const_exprt *ce)
	{
		fmt::format_to(print_str, "const : {} ", std::any_cast<int>(ce->getval()));
	}
};

class eval_visitort : public visitort
{
	std::stack<int> es;
	//int result;
public:
	eval_visitort() {}
	int get_result()
	{
		return es.top();
	}
	void visit(plus_exprt *pe)
	{
		for (auto &o : pe->get_operands())
		{
			(o->visit(*this));
		}
		auto op1 = es.top();
		es.pop();
		auto op2 = es.top();
		es.pop();
		es.push(op1 + op2);
	}
	void visit(minus_exprt *me)
	{
		for (auto &o : me->get_operands())
		{
			(o->visit(*this));
		}
		auto op1 = es.top();
		es.pop();
		auto op2 = es.top();
		es.pop();
		es.push(op2 - op1);
	}
	void visit(const_exprt *ce)
	{
		es.push(std::any_cast<int>(ce->getval()));
	}
};

exprt *parse_expression(std::stringstream &str, unsigned pos)
{

	str.seekg(pos);
	int num;
	str >> num;
	std::any anum(num);
	exprt *op1 = new const_exprt(anum);
	char c;
	str.get(c);
	switch (c)
	{
	case ';':
		return op1;
		break;
	case '+':
	{
		int num2;
		str >> num2;
		int num3 =num+num2;	
		std::string temp1,temp2;
		if(num>=0)
		{
			temp1 = str.str().substr(3,str.str().size()-1);
		}
		else{
			temp1 =  str.str().substr(4,str.str().size()-1);
		}
		str.str(std::string());
		str << num3;
		str << temp1;
		return parse_expression(str,0);	
	}
	break;
	case '-':
	{
		int num2;
		str >> num2;
		int num3;
		num3 =num-num2;	
		std::string temp1,temp2;
		if(num>=0)
		{
			temp1 = str.str().substr(3,str.str().size()-1);
		}
		else if(num<0){
			temp1 =  str.str().substr(4,str.str().size()-1);
		}
		str.str(std::string());
		str << num3;
		str << temp1;
		return parse_expression(str,0);	
	}
	break;
	};

	assert(false && "illegal string");
	return nullptr;
}

int main()
{
	std::string in_str;
	std::cin >> in_str;
	std::stringstream stream(in_str.c_str());
	exprt *e = parse_expression(stream, 0);
	//print_visitort pv;
	//e->visit(pv);
	//pv.print();
	eval_visitort ev;
	e->visit(ev);
	fmt::print("Expr evaluation: {}\n", ev.get_result());
	return EXIT_SUCCESS;
}