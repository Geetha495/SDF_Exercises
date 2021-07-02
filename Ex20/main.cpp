/*****************************************************************************
 *
 *     LICENCE : GNU GPL v3. Full text at :
 *     http://www.gnu.org/licenses/gpl-3.0.en.html
 *
 *     Copyright (C) 2016 	Saurabh Joshi     sbjoshi@iitg.ernet.in
 *
 *     For compiling, use
 *
 *     g++ --std=c++14 -Wall -O0 -g assign.cpp
 *     (for preorder traversal)
 *     or
 *
 *     g++ --std=c++11 -Wall -O0 -g -DINORDER assign.cpp
 *     (for inorder traversal)
 *
 *
 *
 *
 *
 * ****************************************************************************/


/**
 * if using count_if() , then 
 * 
 *  For compiling, use
 *
 *     g++ --std=c++2a -Wall -O0 -g main.cpp -o main
 *     (for preorder traversal)
 * 
 *     or
 *
 *     g++ --std=c++2a -Wall -O0 -g -DINORDER main.cpp
 *     (for inorder traversal)
 * 
 */


#include <iostream>
#include <cassert>
#include <random>
#include <functional>
#include <list>
#include <algorithm>
#include <iterator>
#include <memory>
enum class node_typet
{
	ROOT,
	LEFT,
	RIGHT
};

template <typename T>
class visitort;

template <typename T>
class bintree_nodet : public std::enable_shared_from_this<bintree_nodet<T>>
{

protected:
	
	std::shared_ptr<bintree_nodet<T>> left;
	std::shared_ptr<bintree_nodet<T>> right;
	std::weak_ptr<bintree_nodet<T>> parent;

public:
T value;
	using nptrt = std::shared_ptr<bintree_nodet<T>>;
	T &get_value()
	{
		return value;
	}
	void preorder_visit(visitort<T> &v)
	{
		v.visit(*this);
		if (has_left())
			left->preorder_visit(v);
		if (has_right())
			right->preorder_visit(v);
	}
	void print_visit()
	{
		std::cout << "(";
		std::cout << value << " ";
		if (has_left())
			left->print_visit();
		if (has_right())
			right->print_visit();
		std::cout << ")";
	}
	void inorder_visit(visitort<T> &v)
	{
		if (has_left())
			left->inorder_visit(v);
		v.visit(*this);
		if (has_right())
			right->inorder_visit(v);
	}

	bintree_nodet(T &_value, const node_typet _ntype, std::shared_ptr<bintree_nodet<T>> _left,
		      std::shared_ptr<bintree_nodet<T>> _right, std::shared_ptr<bintree_nodet<T>> _parent)
	{
		value = _value;
		left = _left;
		right = _right;
		parent = _parent;
		ntype = _ntype;
	}

	void init()
	{

		if (parent.lock().get() == nullptr && ntype != node_typet::ROOT)
		{
			assert(false && "inconsistent parent pointer and node type");
		}

		if (left.get() != nullptr)
		{
			left->parent = std::enable_shared_from_this<bintree_nodet<T>>::shared_from_this();
		}
		if (right.get() != nullptr)
		{
			right->parent = std::enable_shared_from_this<bintree_nodet<T>>::shared_from_this();
		}

		if (ntype == node_typet::LEFT)
		{
			parent.lock()->left = std::enable_shared_from_this<bintree_nodet<T>>::shared_from_this();
		}
		else if (ntype == node_typet::RIGHT)
		{
			parent.lock()->right = std::enable_shared_from_this<bintree_nodet<T>>::shared_from_this();
		}
	}

	bool has_parent()
	{
		return parent.lock().get() != nullptr;
	}
	bool has_left()
	{
		return (left.get() != nullptr);
	}
	bool has_right()
	{
		return (right.get() != nullptr);
	}
	std::shared_ptr<bintree_nodet<T>> get_parent()
	{
		return parent.lock();
	}
	std::shared_ptr<bintree_nodet<T>> get_left()
	{
		return left;
	}
	std::shared_ptr<bintree_nodet<T>> get_right()
	{
		return right;
	}
	node_typet ntype;
};

template <typename T>
class biteratort;

template <typename T, typename U>
class iteratort;

template <typename T>
class bintreet
{
	std::shared_ptr<bintree_nodet<T>> root;

public:
	void print()
	{
		root->print_visit();
	}
	bintreet() : root(nullptr) {}
	bintreet(T &value)
	{
		root = std::make_shared<bintree_nodet<T>>(value, node_typet::ROOT, std::shared_ptr<bintree_nodet<T>>(nullptr), std::shared_ptr<bintree_nodet<T>>(nullptr), std::shared_ptr<bintree_nodet<T>>(nullptr));
		root->init();
	}
	bool is_empty() { return root.get() == nullptr; }

	biteratort<T> add_left(biteratort<T> &it, T &value)
	{
		std::shared_ptr<bintree_nodet<T>> node = std::make_shared<bintree_nodet<T>>(value, node_typet::LEFT, std::shared_ptr<bintree_nodet<T>>(nullptr), std::shared_ptr<bintree_nodet<T>>(nullptr), it.get_node());
		node->init();
		return biteratort<T>(node);
	}
	biteratort<T> add_left(biteratort<T> &it, T value)
	{
		T v = value;
		std::shared_ptr<bintree_nodet<T>> node = std::make_shared<bintree_nodet<T>>(v, node_typet::LEFT, std::shared_ptr<bintree_nodet<T>>(nullptr), std::shared_ptr<bintree_nodet<T>>(nullptr), it.get_node());
		node->init();
		return biteratort<T>(node);
	}
	biteratort<T> add_right(biteratort<T> &it, T value)
	{
		T v = value;
		std::shared_ptr<bintree_nodet<T>> node = std::make_shared<bintree_nodet<T>>(v, node_typet::RIGHT, std::shared_ptr<bintree_nodet<T>>(nullptr), std::shared_ptr<bintree_nodet<T>>(nullptr), it.get_node());
		node->init();
		return biteratort<T>(node);
	}
	biteratort<T> add_right(biteratort<T> &it, T &value)
	{
		bintree_nodet<T> *node = std::make_shared<bintree_nodet<T>>(value, node_typet::RIGHT, std::shared_ptr<bintree_nodet<T>>(nullptr), std::shared_ptr<bintree_nodet<T>>(nullptr), it.get_node());
		node->init();
		return biteratort<T>(node);
	}

	biteratort<T> get_root()
	{
		return biteratort<T>(root);
	}

	template <typename U>
	iteratort<T, U> begin(U &u)
	{
		iteratort<T, U> it(root);
		it.begin();
		return it;
	}
	template <typename U>
	iteratort<T, U> end(U &u)
	{
		iteratort<T, U> it(nullptr);
		return it;
	}
};

template <typename T>
class visitort
{
public:
	virtual void visit(bintree_nodet<T> &_node) = 0;
};

template <typename T>
class list_visitort : public visitort<T>
{
	std::list<T> values;

public:
	const std::list<T> &get_list() const
	{
		return values;
	}

	void visit(bintree_nodet<T> &_node)
	{
		values.push_back(_node.get_value());
	}
};

template <typename T>
class biteratort
{
protected:
	std::shared_ptr<bintree_nodet<T>> current;

public:
	biteratort<T>() : current(nullptr) {}
	biteratort<T>(std::shared_ptr<bintree_nodet<T>> nptr)
	{
		current = nptr;
	}
	biteratort<T>(const biteratort<T> &bit)
	{
		current = bit.current;
	}
	biteratort<T> &operator=(biteratort<T> &bit)
	{
		current = bit.current;
		return *this;
	}


	bool operator==(const biteratort &bit)
	{
		return current == bit.current;
	}

	bool operator!=(const biteratort &bit)
	{
		return current != bit.current;
	}
	std::shared_ptr<bintree_nodet<T>> operator->() const
	{
		return current;
	}
	std::shared_ptr<bintree_nodet<T>> get_node()
	{
		return current;
	}
	bintree_nodet<T> &operator*()
	{
		return current;
	}
	
};

template <typename T, typename U>
class iteratort : public biteratort<T> , public  std::iterator<std::forward_iterator_tag,T>  // <===========
{
protected:
	using biteratort<T>::current;
	U traversal_strategy;

public:
	iteratort<T, U>(std::shared_ptr<bintree_nodet<T>> nptr) : biteratort<T>(nptr)
	{
	}
	void next()
	{
		std::shared_ptr<bintree_nodet<T>> next_node = traversal_strategy.next(current);
		current = next_node;
	}
	void begin()
	{
		current = traversal_strategy.begin(current);
	}

	//##################################
	iteratort<T,U>& operator++()
	{ 
		if(current!=nullptr)
		{
			std::shared_ptr<bintree_nodet<T>> next_node = traversal_strategy.next(current);
			current = next_node;
		}
		return *this;
	}
	iteratort<T,U> operator++(int i)
	{
		iteratort tmpcopy(current);
		++(*this);
		return tmpcopy;
	}
	T operator*()
	{
		return current->value;
	}
	//######################################
};

template <typename T>
class preordert
{
public:
	std::shared_ptr<bintree_nodet<T>> begin(std::shared_ptr<bintree_nodet<T>> n)
	{
		return n;
	}
	std::shared_ptr<bintree_nodet<T>> next(const std::shared_ptr<bintree_nodet<T>> n)
	{
		auto tmp = n;
		if (tmp == nullptr)
			return tmp;

		if (tmp->has_left())
			return tmp->get_left();
		if (tmp->has_right())
			return tmp->get_right();

		//we are at a leaf, keep going up if the node is
		//RIGHT node or it is LEFT node without a
		//sibling

		while (((tmp->ntype == node_typet::LEFT) && tmp->has_parent() &&
			!tmp->get_parent()->has_right()) ||
		       (tmp->ntype == node_typet::RIGHT && tmp->has_parent()))
		{
			tmp = tmp->get_parent();
		}

		//we have reached root so we are done
		if (!tmp->has_parent())
			return nullptr;
		return tmp->get_parent()->get_right();
	}
};

template <typename T>
class inordert
{
public:
	std::shared_ptr<bintree_nodet<T>> begin(std::shared_ptr<bintree_nodet<T>> n)
	{
		auto tmp = n;
		if (tmp == nullptr)
			return n;
		while (tmp->has_left())
		{
			tmp = tmp->get_left();
		}
		return tmp;
	}
	std::shared_ptr<bintree_nodet<T>> next(std::shared_ptr<bintree_nodet<T>> n)
	{
		auto tmp = n;
		if (tmp == nullptr)
			return nullptr;

		//if the node has a right child, then the
		//next node in inorder traversal will be
		//the left most descendent of its right child
		if (tmp->has_right())
		{
			tmp = tmp->get_right();
			tmp = begin(tmp);
			return tmp;
		}

		//the node is ROOT and does not have a right
		//child -> tree is completely traversed
		if (!tmp->has_parent())
		{
			return nullptr;
		}

		//The node does not have a right child so we
		//have to go up
		//If the node itself is a left child we know
		//that the next node in inorder traversal will
		//be its parent
		if (tmp->ntype == node_typet::LEFT)
		{
			tmp = tmp->get_parent();
			return tmp;
		}

		while (tmp->has_parent() && !(tmp->get_parent()->ntype == node_typet::LEFT))
		{
			tmp = tmp->get_parent();
		}
		//We reached ROOT on upward traversal from right
		//-> tree is completely traversed
		if (!tmp->has_parent())
			return nullptr;
		else
		{
			//now the tmp must be a right child of a
			//left child
			tmp = tmp->get_parent()->get_parent();
			return tmp;
		}

		return nullptr;
	}
};

class tree_generatort
{
	float leftprob;
	float rightprob;
	unsigned node_limit;

	std::function<float()> probrandom;
	std::function<int()> valuerandom;

public:
	tree_generatort(int lbound, int rbound, float _probleft = 0.5, float _probright = 0.5, unsigned _node_limit = 50)

	{
		assert(lbound <= rbound);
		leftprob = _probleft;
		node_limit = _node_limit;
		rightprob = _probright;
		assert(0 <= leftprob && leftprob <= 1.0 &&
		       0 <= rightprob && rightprob <= 1.0 &&
		       "probability NOT between 0 and 1");

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(0, 1);
		probrandom = std::bind(dist, gen);

		std::uniform_int_distribution<> intdist(lbound, rbound);
		valuerandom = std::bind(intdist, gen);
	}

	bintreet<int> generate()
	{
		int tmp = valuerandom();
		unsigned node_generated = 0;
		bintreet<int> t(tmp);
		node_generated++;
		biteratort<int> it(t.get_root());
		std::list<biteratort<int>> worklist;
		worklist.push_back(it);
		while (!worklist.empty() && node_generated < node_limit)
		{
			auto wit = worklist.back();
			worklist.pop_back();
			if (probrandom() < leftprob)
			{
				auto lit = t.add_left(wit, valuerandom());
				worklist.push_back(lit);
				node_generated++;
			}
			if (probrandom() < rightprob)
			{
				auto rit = t.add_right(wit, valuerandom());
				worklist.push_back(rit);
				node_generated++;
			}
		}
		return t;
	}
};

int main()
{

	tree_generatort tg(1, 100, 0.5, 0.5, 100);
	for (unsigned i = 0; i < 3; i++)
	{
		std::cout << "Case " << i << ":" << std::endl;

		auto t = tg.generate();
		list_visitort<int> lv;

		t.print();
		std::cout << std::endl;
#ifdef INRODER
		t.get_root()->inorder_visit(lv);

		inordert<int> s;
		iteratort<int, inordert<int>> it = t.begin(s);
		auto it_end = t.end(s);
#else
		t.get_root()->preorder_visit(lv);

		preordert<int> s;
		iteratort<int, preordert<int>> it = t.begin(s);
		auto it_end = t.end(s);

#endif
		//--->
		std::cout<<"\ncount >30 is "<<std::count_if(t.begin(s),t.end(s),[](const auto& x){return x>30;})<<std::endl;
		
		auto lv_begin = lv.get_list().begin();
		auto lv_end = lv.get_list().end();
		std::cout << "Visitor list :";
		std::copy(lv_begin, lv_end, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;

		std::list<int> li;
		while (it != it_end)
		{
			li.push_back(it->get_value());
			it.next();
		}

		std::cout << "Iterator list :";
		std::copy(li.begin(), li.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
		if (!std::equal(li.begin(), li.end(), lv_begin, lv_end))
		{
			assert(false);
		}
	}
	return 0;
}
