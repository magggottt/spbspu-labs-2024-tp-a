#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>

void doHelp(std::ostream & out)
{
  out << "Command system:\n";
  out << "1. create <dictionary> <file> - Creates a frequency dictionary for a text file.\n";
  out << "2. print <dictionary> <key> - Outputs the frequency of occurrence of the word.\n";
  out << "3. print <dictionary> - Outputs a frequency dictionary.\n";
  out << "4. sort <dictionary> - Sorts the dictionary by the frequency of occurrence of words (from more to less frequent).\n";
  out << "5. delete <dictionary> <key> -  Deletes a word from the frequency dictionary.\n";
  out << "6. delete <dictionary> - Deletes the frequency dictionary.\n";
  out << "7. compare <dictionary1> <dictionary2> - Compares two dictionaries, returns 1 if they are the same or 0 if they are not.\n";
  out << "8. combine <dictionary1> <dictionary2> <dictionary to combine> - Combines two frequency dictionaries into a created dictionary.\n";
  out << "9. intersect <dictionary1> <dictionary2> <dictionary to intersect> - Creates a frequency dictionary from the intersection of two dictionaries.\n";
  out << "10. subtract <dictionary1> <dictionary2> <dictionary to subtract> - Creates a dictionary from words in the first dictionary that are not in the second dictionary.\n";
  out << "11. mostfrequent <dictionary> <amount> - Outputs the given number of the most frequently occurring words from the dictionary.\n";
}

using map_of_dicts = std::map< std::string, std::map< std::string, size_t > >;

class Dictionary
{
public:
  Dictionary() = default;
  ~Dictionary() = default;

  void add_word(std::string & word)
  {
    auto iter = words_.find(word);
    if (iter != words_.end())
    {
      ++(*iter).second;
      return;
    }
    words_.insert(std::pair< std::string, size_t >(word, 1));
  }

  void print()
  {
    std::cout << "RESULT:\n";
    for (auto it = words_.begin(); it != words_.end(); ++it)
    {
      std::cout << (*it).first << ' ' << (*it).second << '\n';
    }
  }

private:
  std::map< std::string, size_t > words_;
};

void createCmd(std::map< std::string, Dictionary > & dictionaries, std::istream & in)
{
  std::string dictionary_name = "", file_name = "";
  in >> dictionary_name >> file_name;
  std::ifstream input(file_name);
  //проверка
  Dictionary create_dict;
  std::string word;
  while (input >> word)
  {
    create_dict.add_word(word);
  }
  dictionaries.insert(std::pair< std::string, Dictionary >(dictionary_name, create_dict));
}

/*
void printCmd(dicts & map_of_dict, std::istream & in)
{
}

void sortCmd(dicts & map_of_dict, std::istream & in)
{
}

void deleteCmd(dicts & map_of_dict, std::istream & in)
{
}

void compareCmd(dicts & map_of_dict, std::istream & in)
{
}

void combineCmd(dicts & map_of_dict, std::istream & in)
{
}

void intersectCmd(dicts & map_of_dict, std::istream & in)
{
}

void subtractCmd(dicts & map_of_dict, std::istream & in)
{
}

void mostfrequentCmd(dicts & map_of_dict, std::istream & in)
{
}
*/

int main(int argc, char ** argv)
{
/*
  Dictionary dict;
  std::string input = "";
  while (std::cin >> input)
  {
    dict.add_word(input);
  }
  std::cout << '\n';
  dict.print();
*/


  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    doHelp(std::cout);
  }
  else if (argc == 3 && std::string(argv[1]) == "--check")
  {
    std::cout << "CHECK\n";
    std::ifstream input(argv[2]);
    if (!input)
    {
      std::cerr << "No such file\n";
      return 1;
    }
  }

  std::map< std::string, Dictionary > dictionaries;
  createCmd(dictionaries, std::cin);
  for (auto iter = dictionaries.begin(); iter !=  dictionaries.end(); ++iter)
  {
    std::cout << (*iter).first << ":\n";
    (*iter).second.print();
  }

/*
  std::map< std::string, std::map< std::string, size_t > > map_of_dict = {};
  std::map< std::string, Dictionary > dictionaries;
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    //cmds["create"] = std::bind(createCmd, dictionaries, _1);
    //cmds["print"] = std::bind(printCmd, map_of_dict, _1, _2);
    //cmds["sort"] = std::bind(sortCmd, map_of_dict, _1);
    //cmds["delete"] = std::bind(deleteCmd, map_of_dict, _1);
    //cmds["compare"] = std::bind(compareCmd, map_of_dict, _1, _2);
    //cmds["combine"] = std::bind(combineCmd, map_of_dict, _1);
    //cmds["intersect"] = std::bind(intersectCmd, map_of_dict, _1);
    //cmds["subtract"] = std::bind(subtractCmd, map_of_dict, _1);
    //cmds["mostfrequent"] = std::bind(mostfrequentCmd, map_of_dict, _1, _2);
  }
  for (dictionaries.begin();)

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;

*/
}
