#include<iostream>
#include<string>
#include<vector>
#include<mutex>
#include<fstream>

class observer
{
public:
	virtual void update(std::string,std::string) = 0;
	virtual ~observer(){};
};


class event_manager 
{
	std::mutex m;
	std::vector<std::pair<observer*,bool>> observers;
	public:
	unsigned subscribe(observer* obs)
	{
		const std::lock_guard<std::mutex> l(m);
		observers.push_back(std::make_pair(obs,true));
		return observers.size()-1;
	}

	void unsubscribe(unsigned id)
	{
		const std::lock_guard<std::mutex> l(m);
		observers[id].second=false;
	}
	void notify_all(std::string name,std::string str)
	{
		const std::lock_guard<std::mutex> l(m); 
		for(auto& o: observers)
		{
		    if(o.second)
		    {
		        o.first->update(name,str);
		    }
		}
	}
	~event_manager()
	{	
		for(auto& l: observers)
		{
			if(l.first!=nullptr)
			{
				delete l.first;
			}
		}
    
	}
};


class reader_t
{
	std::string name;
	public:
	reader_t(std::string _name):name(_name){};
	event_manager ev;
	
 
  	void take_string(std::string str)
	{

		ev.notify_all(name,str);
	}


};


class string_observer : public observer
{
	void update(std::string name,std::string str)
	{
		std::cout<<"For "<<name<<" string_observer : "<<str<<std::endl;
	}
	~string_observer(){};
};


class frequency_observer : public observer
{
	void update(std::string name ,std::string str)
	{

		std::cout<<"For "<<name<<" frequency_observer : "<<std::endl;
		int i=0;
		int alphabet[26]={0};
		while (str[i] != '\0') 
		{
			if (str[i] >= 'a' && str[i] <= 'z') 
			{
				++alphabet[str[i] - 'a'];
			}
			++i;
		}
   	
   
		for(i = 0; i < 26; i++)
		{
			if(alphabet[i]!=0)
			{
				std::cout<< char(i + 'a')<<" : "<< alphabet[i]<< std::endl;
			}
		}
	}
	~frequency_observer(){};
};


class writer_observer : public observer
{
	static std::ofstream MyFile;
	void update(std::string name,std::string str)
	{
		std::cout<<"For "<<name<<" writer_observer : ";
		MyFile.open("myfile.txt",std::ios_base::app);
		MyFile << str;
		MyFile << " ";
		MyFile.close();
		std::cout<<"done"<<std::endl;
	}
	~writer_observer(){};
};
std::ofstream writer_observer::MyFile;


int main()
{
	reader_t rdr1("reader1"),rdr2("reader2");
	std::string str;
	unsigned id1 = (rdr1.ev).subscribe(new string_observer());
	unsigned id2 = (rdr2.ev).subscribe(new frequency_observer());
	unsigned id3 = (rdr2.ev).subscribe(new writer_observer());
	std::cout<<"enter only 2 strings\n";
	std::string s1,s2;
	std::cin>>s1;
	rdr1.take_string(s1);
	std::cin>>s2;
	rdr2.take_string(s2);
}