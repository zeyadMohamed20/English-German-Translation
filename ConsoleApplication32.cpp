#include<algorithm>
#include<fstream>
#include <iostream>
#include <string>
#include<vector>
#include <io.h>
#include <fcntl.h>
using namespace std;

int binary_search(vector<string>& Dictionary, int Low, int High, string Key)
{
	if (Low > High)
		return Low - 1;
	int Mid = Low + (High - Low) / 2;
	if (Key == Dictionary[Mid])
		return Mid;
	else if (Key > Dictionary[Mid])
		return binary_search(Dictionary, Mid + 1, High, Key);
	else if (Key < Dictionary[Mid])
		return binary_search(Dictionary, Low, Mid - 1, Key);
}

int main()
{
	vector<string>English;
	string EWord;
	ifstream ERead("English.txt");
	vector<wstring>German;
	wstring GWord;
	wifstream GRead("German.txt");
	GRead.imbue(std::locale("zh_CN.UTF-8"));
	string Sentence;
	string Key;
	int Index;
	int PreviousMode = _O_U16TEXT;
	while (getline(ERead, EWord))
	{
		transform(EWord.begin(), EWord.end(), EWord.begin(), tolower);
		English.push_back(EWord);
	}
	while (getline(GRead, GWord))
	{
		transform(GWord.begin(), GWord.end(), GWord.begin(), tolower);
		German.push_back(GWord);
	}
	while (true)
	{
		cout << "Enter English Sentence: ";
		getline(cin, Sentence);
		cout << "Translation: ";
		int Count = 0;
		while (Count < Sentence.size())
		{
			if (Sentence[Count] != ' ')
				Key.push_back(Sentence[Count]);
			else
			{
				Sentence.erase(Sentence.begin(), Sentence.begin() + Sentence.find(' ') + 1);
				Count = -1;
				Index = binary_search(English, 0, English.size() - 1, Key);
				PreviousMode = _setmode(_fileno(stdout), PreviousMode);
				wcout <<  German[Index] << " ";
				PreviousMode = _setmode(_fileno(stdout), PreviousMode);
				Key.clear();
			}
			Count++;
		}
		transform(Key.begin(), Key.end(), Key.begin(), tolower);
		Index = binary_search(English, 0, English.size() - 1, Key);
		PreviousMode = _setmode(_fileno(stdout), PreviousMode);
		wcout << German[Index] << endl;
		PreviousMode = _setmode(_fileno(stdout), PreviousMode);
		Key.clear();
		Sentence.clear();
	}
}