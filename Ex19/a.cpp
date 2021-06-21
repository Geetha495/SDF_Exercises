//######################################################

/**
 * works only when the expression has odd number of numbers :( 
 * 
 * Need to Change :(
 */

//############################



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

class exprt;
class visitort
{
public:
	virtual void visit(exprt *) = 0;
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
	virtual void visit(exprt *e)
	{
		if (dynamic_cast<plus_exprt *>(e))
		{
			visit(dynamic_cast<plus_exprt *>(e));
		}
		else if (dynamic_cast<minus_exprt *>(e))
		{
			visit(dynamic_cast<minus_exprt *>(e));
		}
		else if (dynamic_cast<const_exprt *>(e))
		{

			visit(dynamic_cast<const_exprt *>(e));
		}
		else
		{
			assert(false && "illegal expression type");
		}
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
		//#########################################################

		es.push(op1 - op2);

		//#########################################################

	}
	void visit(const_exprt *ce)
	{
		es.push(std::any_cast<int>(ce->getval()));
	}
	virtual void visit(exprt *e)
	{
		if (dynamic_cast<plus_exprt *>(e))
		{
			visit(dynamic_cast<plus_exprt *>(e));
		}
		else if (dynamic_cast<minus_exprt *>(e))
		{
			visit(dynamic_cast<minus_exprt *>(e));
		}
		else if (dynamic_cast<const_exprt *>(e))
		{

			visit(dynamic_cast<const_exprt *>(e));
		}
		else
		{
			assert(false && "illegal expression type");
		}
	}
};

exprt *parse_expression(std::istringstream &str, unsigned pos)
{

	//str.seekg(pos);
	int num;
	str >> num;
	std::any anum(num);
	exprt *op1 = new const_exprt(anum);

	char c;
	str.get(c);


	//####################################################
	
	int num2;
	str >> num2;
	std::any anum2(num2);
	exprt *op2 = new const_exprt(anum2);

	//#########################################################
	switch (c)
	{
	case ';':
		return op1;
		break;
	case '+':
	{
		//#########################################################
		
		auto a = dynamic_cast<exprt *>(new plus_exprt(std::move(std::vector<exprt *>({op1, op2}))));
		exprt *subexpr = parse_expression(str, str.tellg());
		//std::vector<exprt*> ops = {op1,subexpr};
		return new plus_exprt(std::move(std::vector<exprt *>({a, subexpr})));

		//#########################################################

	}
	break;
	case '-':
	{
		//########################################################
		
		auto s = dynamic_cast<exprt *>(new minus_exprt(std::move(std::vector<exprt *>({op1, op2}))));
		exprt *subexpr = parse_expression(str, str.tellg());
		return new minus_exprt(std::move(std::vector<exprt *>({s, subexpr})));

		//#########################################################

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
	std::istringstream istream(in_str.c_str());
	exprt *e = parse_expression(istream, 0);
	print_visitort pv;
	e->visit(pv);
	//pv.print();
	eval_visitort ev;
	e->visit(ev);
	fmt::print("Expr evaluation: {}\n", ev.get_result());

	return EXIT_SUCCESS;
}