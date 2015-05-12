#define _CRT_SECURE_NO_WARNINGS
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "md5.h"
using namespace std;
using namespace boost::filesystem;
void search(path dir_path)
{
	ofstream f("AbFiles.tsv");
	if (is_directory(dir_path) && exists(dir_path))
	{

		recursive_directory_iterator end;
		for (recursive_directory_iterator it(dir_path); it != end; ++it)
			if (is_regular_file(it->path()))
			{

				stringstream result;
				string a;
				ifstream myfile;
				myfile.open(it->path().string(), ios::binary);
				result << myfile.rdbuf();
				a = result.str();
				f << it->path().filename().string() << "\n" << it->path() << "\n" <<  file_size(it->path()) << "\n" <<  md5(a) << endl;
				f << endl;
			}
	}
	else
	{
		cout << dir_path << " does not exist\n";
	}


	f.close();
	return;
};
void checkIn(path dir_path)
{
	ifstream f;
	f.open("AbFiles.tsv", ios::in);
	string str, a;
	vector <string> filename;
	vector <string> hash;
	vector <string> savfilename;
	vector <string> savhash;
	vector <int> flagok;
	while (!f.eof()){
		getline(f, str);
		a = str;
		savfilename.push_back(a);
		getline(f, str);
		getline(f, str);
		getline(f, str);
		a = str;
		savhash.push_back(a);
		getline(f, str);

	}
	f.close();
	if (is_directory(dir_path) && exists(dir_path))
	{

		recursive_directory_iterator end;
		for (recursive_directory_iterator it(dir_path); it != end; ++it)
			if (is_regular_file(it->path()))
			{

				stringstream result;
				string a;
				ifstream myfile;
				myfile.open(it->path().string(), ios::binary);
				result << myfile.rdbuf();
				a = result.str();
				hash.push_back(md5(a));
				filename.push_back(it->path().filename().string());
				flagok.push_back(0);
			}
	}
	else
	{
		cout << dir_path << " does not exist\n";
	}
	int flag = 0;
	for (int i = 0; i < savfilename.size() - 1; ++i)
	{
		for (int j = 0; j < filename.size(); ++j)
		{
			if ((savfilename[i] == filename[j]) & (savhash[i] == hash[j])& (flagok[j]==0))
			{
				flag = 1; flagok[j] = 1; break;
			}
			if ((savfilename[i] == filename[j]) & (savhash[i] != hash[j])& (flagok[j] == 0))
			{
				flagok[j] = 1;
				cout << "file " << savfilename[i] << " " << "was changed" << endl;
				flag = 1; break;
			}
			flag = 0;
		}
		if (flag == 0)
		{
			cout << "file " << savfilename[i] << " " << "was deleted" << endl;
		}
	}
	for (int i = 0; i < flagok.size(); ++i)
	{
		if (flagok[i] == 0){
			cout << filename[i] << " " << "was added" << endl;
		}
	}
	return;
};

int main(int argc, char* argv[1])
{

	
	cout << "If you want to search your files enter 1" << "\n" << "If you want to check your files enter 2" << endl;
	int y;
	cin >> y;
	cout << "Enter the directory path:\n" << std::endl;
	path dir_path;
	cin >> dir_path;
	if (exists(dir_path)){
		if (y == 1)
		{
			search(dir_path);
			cout<<"files searched"<<endl;
		}
		if (y == 2)
		{
			checkIn(dir_path);
			cout << "Other files did not change" << endl;
		}
	}
	else {
		cout << dir_path << " does not exist\n";
	}

	int i;
	cin >> i;
	return 0;
}
