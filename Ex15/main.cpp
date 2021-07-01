#include<iostream>
#include<string>
#include<vector>
#include<mutex>
#include<fstream>

class observer
{
public:
	virtual void update(std::string) = 0;
	virtual ~observer(){};
};

class reader_t
{
	std::vector<std::pair<observer*,bool>> observers;
	std::mutex m;
  public:
  void take_string(std::string str)
  {
	const std::lock_guard<std::mutex> l(m); 
	for(auto& o: observers)
        {
            if(o.second)
            {
                o.first->update(str);
            }
        }
  }
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
};



class string_observer : public observer
{
	void update(std::string str)
	{
		std::cout<<"string_observer : "<<str<<std::endl;
	}
};


class frequency_observer : public observer
{
	void update(std::string str)
	{

		std::cout<<"frequency_observer : "<<std::endl;
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
};


class writer_observer : public observer
{
	static std::ofstream MyFile;
	void update(std::string str)
	{
		std::cout<<"writer_observer : ";
		MyFile.open("myfile.txt",std::ios_base::app);
		MyFile << str;
		MyFile << " ";
		MyFile.close();
		std::cout<<"done"<<std::endl;
	}
};
std::ofstream writer_observer::MyFile;


int main()
{
	reader_t rdr;
	std::string str;
	unsigned id1 = rdr.subscribe(new string_observer());
	unsigned id2 = rdr.subscribe(new frequency_observer());
	unsigned id3 = rdr.subscribe(new writer_observer());
	while(1)
	{
		std::cin>>str;
		if(str=="STOP")
			break;
		rdr.take_string(str);
	}
}
	