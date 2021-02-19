#include "../src/os_path.hpp"

int main()
{
	os_path os;
	cout << os.abspath("../src/os_path.hpp") << endl;
	cout << os.commonprefix({"/usr/lib/hrishi", "/usr/local/siddhu/ok", "/usr/lol"}) << endl;
	cout << os.exists("") << endl;
	printf("%lf\n", os.getatime("../../websock/"));
	printf("%lf\n", os.getmtime("../../websock/"));
	printf("%lf\n", os.getctime("../../websock/"));
	cout << os.getfilesize("../src") << endl;
	cout << os.getfilesize("../src/os_path.cpp") << endl;
	cout << os.isfile("test.cpp") << endl;
	cout << os.isfile("../") << endl;
	cout << os.isdir("test.cpp") << endl;
	cout << os.isdir("../") << endl;
	pair<string, string> p = os.split("/home/hrishib/Hrishi//////////lol////////////");
	cout << p.first << ", " << p.second << endl;

	p = os.splitext(".vimrc");
	cout << p.first << ", " << p.second << endl;
}
