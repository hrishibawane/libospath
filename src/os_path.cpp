//////////////////////////PREPROCESSOR DIRECTIVES/////////////////////////////

#include "os_path.hpp"

///////////////////////////NAMESPACES//////////////////////////

using namespace std;

//////////////////////////CONSTRUCTOR//////////////////////////

os_path::os_path()
{
	m_sep = '/';
}

//////////////////////////DESTRUCTOR///////////////////////////

os_path::~os_path() 
{}

//////////////////////////ABSPATH//////////////////////////////

string os_path::abspath(const string& path)
{
	if (os_path::isabs(path))
	{
		return path;
	}
	string s_res = "";
	string s_buf = "";
	stack<string> stk_curr_dir;

#ifdef OS_LINUX
	FILE* f_pipe = popen("pwd", "r");
#elif OS_WINDOWS
	FILE* f_pipe = _popen("cd", "r");
#endif
	if (f_pipe == NULL)
	{
		printf("Error in execution of command\n");
		return s_res;
	}

	while (fgets(m_buffer.data(), MAXBUFFER, f_pipe) != NULL)
	{
		s_buf += m_buffer.data();
	}
#ifdef OS_LINUX
	pclose(f_pipe);
#elif
	_pclose(f_pipe);
#endif
	if (s_buf[s_buf.length() - 1] == '\n')
		s_buf.pop_back();
	
	s_buf = os_path::cleanpathstr(s_buf);
	string s_tmp;
	stringstream ss_tokenizer1(s_buf);
	while (getline(ss_tokenizer1, s_tmp, m_sep))
	{
		stk_curr_dir.push(s_tmp);
	}

	s_tmp.clear();
	stringstream ss_tokenizer2(path);
	while (getline(ss_tokenizer2, s_tmp, m_sep))
	{
		if (s_tmp == ".." && !stk_curr_dir.empty())
		{
			stk_curr_dir.pop();
		}
		else if (s_tmp != "." && s_tmp != "..")
		{
			stk_curr_dir.push(s_tmp);
		}
	}

	while (!stk_curr_dir.empty())
	{
		s_res = stk_curr_dir.top() + m_sep + s_res;
		stk_curr_dir.pop();
	}
	// Remove extra m_sep
	s_res.pop_back();
#ifdef OS_LINUX
	if (s_res[0] != m_sep)
		s_res = m_sep + s_res;
#endif
	return s_res;
}

///////////////////////////////BASENAME///////////////////////////////////

string os_path::basename(const string& path)
{
	return os_path::split(path).second;
}

///////////////////////////////CLEANPATHSTR/////////////////////////////////

string os_path::cleanpathstr(const string& path)
{
	string s_path = path;
#ifdef OS_WINDOWS
	replace(s_path.begin(), s_path.end(), '/', '\\');
#endif
	return s_path;
}

///////////////////////////////COMMONPREFIX/////////////////////////////////

string os_path::commonprefix(const vector<string>& paths)
{
	string s_res = "";
	if (paths.size() == 0)
	{
		return s_res;
	}
	int min_length = INT_MAX;
	for (string s_curr : paths)
	{
		min_length = min(min_length, static_cast<int>(s_curr.length()));
	}
	
	for (int n_pos = 0; n_pos < min_length; n_pos++)
	{
		bool b_check = true;
		char c_curr = paths[0][n_pos];
		for (int n_str = 1; n_str < paths.size(); n_str++)
		{
			if (paths[n_str][n_pos] != c_curr)
			{
				b_check = false;
				break;
			}
		}
		if (b_check)
		{
			s_res += c_curr;
		}
		else
		{
			break;
		}
	}
	return s_res;
}

///////////////////////////////DIRNAME///////////////////////////////////

string os_path::dirname(const string& path)
{
	return os_path::split(path).first;
}

/////////////////////////////////GETSTATINFO/////////////////////////////////

int os_path::getstatinfo(const string& path)
{
	m_info = {};
#ifdef OS_LINUX
	return stat(path.c_str(), &m_info);
#elif OS_WINDOWS
	return _stat(path.c_str(), &m_info);
#endif
}

/////////////////////////////////EXISTS//////////////////////////////////

bool os_path::exists(const string& path)
{
	if (getstatinfo(path) != 0 && errno == ENOENT)
	{
		return false;
	}
	return true;
}

//////////////////////////////////GETATIME////////////////////////////////

double os_path::getatime(const string& path)
{
	double d_res = 0;
	if (getstatinfo(path) == 0)
	{
#ifdef OS_LINUX
		d_res = static_cast<double>(m_info.st_atim.tv_sec);
#elif OS_WINDOWS
		d_res = static_cast<double>(m_info.st_atime);
#endif
	}
	else
	{
		printf("Invalid path\n");
	}
	return d_res;
}

//////////////////////////////////GETMTIME////////////////////////////////

double os_path::getmtime(const string& path)
{
	double d_res = 0;
	if (getstatinfo(path) == 0)
	{
#ifdef OS_LINUX
		d_res = static_cast<double>(m_info.st_mtim.tv_sec);
#elif OS_WINDOWS
		d_res = static_cast<double>(m_info.st_mtime);
#endif
	}
	else
	{
		printf("Invalid path\n");
	}
	return d_res;
}

//////////////////////////////////GETCTIME////////////////////////////////

double os_path::getctime(const string& path)
{
	double d_res = 0;
	if (getstatinfo(path) == 0)
	{
#ifdef OS_LINUX
		d_res = static_cast<double>(m_info.st_ctim.tv_sec);
#elif OS_WINDOWS
		d_res = static_cast<double>(m_info.st_ctime);
#endif
	}
	else
	{
		printf("Invalid path\n");
	}
	return d_res;
}

////////////////////////////////GETFILESIZE/////////////////////////////////

long int os_path::getfilesize(const string& path)
{
	long int l_res = -1;
	if (getstatinfo(path) == 0 && S_ISREG(m_info.st_mode))
	{
		l_res = m_info.st_size;
	}
	else
	{
		printf("Invalid path\n");
	}
	return l_res;
}

///////////////////////////////////ISABS///////////////////////////////////

bool os_path::isabs(const string& path)
{
	bool b_res = true;
	if (path.length() == 0 || path[0] != m_sep)
	{
		b_res = false;
	}
	return b_res;
}

///////////////////////////////////ISFILE//////////////////////////////////

bool os_path::isfile(const string& path)
{
	bool b_res = false;
	if (getstatinfo(path) == 0 && S_ISREG(m_info.st_mode))
	{
		b_res = true;
	}
	return b_res;
}

///////////////////////////////////ISDIR//////////////////////////////////

bool os_path::isdir(const string& path)
{
	bool b_res = false;
	if (getstatinfo(path) == 0 && S_ISDIR(m_info.st_mode))
	{
		b_res = true;
	}
	return b_res;
}

///////////////////////////////////RELPATH////////////////////////////////

string os_path::relpath(const string& path)
{
#ifdef OS_LINUX
	if (!os_path::isabs(path))
	{
		return path;
	}
#endif
	string s_res = "";
	string s_curr_path = os_path::abspath(".");
	string s_target_path = path;
	vector<string> v_curr;
	vector<string> v_target;
	string s_tmp;
	stringstream ss_tokenizer1(s_curr_path);
	while (getline(ss_tokenizer1, s_tmp, m_sep))
	{
		v_curr.push_back(s_tmp);
	}

	s_tmp.clear();
	stringstream ss_tokenizer2(s_target_path);
	while (getline(ss_tokenizer2, s_tmp, m_sep))
	{
		v_target.push_back(s_tmp);
	}

	int n_limit = min(v_curr.size(), v_target.size());
	int n_cnt = v_curr.size();
	int i = 0;
	while (i < n_limit)
	{
		if (v_curr[i] != v_target[i])
		{
			break;
		}
		i++;
	}
	n_cnt = i;
	int n_up = v_curr.size() - n_cnt;
	while (n_up--)
	{
		s_res += "../";
	}
	while (i < v_target.size())
	{
		s_res += v_target[i++] + "/";
	}
	if (s_res.length() > 0)
		s_res.pop_back();
	return s_res;
}

//////////////////////////////////SPLIT/////////////////////////////////

pair<string, string> os_path::split(const string& path)
{
	string tail = "";
	int n_char = path.length() - 1;
	while (n_char >= 0 && path[n_char] != m_sep)
	{
		tail = path[n_char--] + tail;
	}
	while (n_char >= 0 && path[n_char] == m_sep)
	{
		n_char--;
	}
	string head(path, 0, n_char + 1);
	return make_pair(head, tail);
}

///////////////////////////////////SPLITEXT///////////////////////////////////

pair<string, string> os_path::splitext(const string& path)
{
	string ext = "";
	int n_char = path.length() - 1;
	while (n_char >= 0 && path[n_char] != '.')
	{
		ext = path[n_char--] + ext;
	}
	ext = path[n_char--] + ext;
	string root(path, 0, n_char + 1);
	return root.length() == 0 ? make_pair(ext, root) : make_pair(root, ext);
}

//////////////////////////////////LISTDIR/////////////////////////////////////

vector<string> os_path::listdir(const string& path)
{
	vector<string> res;
	string s_buf = "";
	string s_cmd;
#ifdef OS_LINUX
	s_cmd = "ls " + path;
	FILE* f_pipe = popen(s_cmd.c_str(), "r");
#elif OS_WINDOWS
	s_cmd = "dir /b " + path;
	FILE* f_pipe = _popen(s_cmd.c_str(), "r");
#endif
	if (f_pipe == NULL)
	{
		printf("Error in command execution\n");
		return res;
	}
	while (fgets(m_buffer.data(), MAXBUFFER, f_pipe) != NULL)
	{
		string s_buf = m_buffer.data();
		s_buf.pop_back();
		s_buf = os_path::cleanpathstr(s_buf);
		res.push_back(s_buf);
	}
#ifdef OS_LINUX
	pclose(f_pipe);
#elif OS_WINDOWS
	_pclose(f_pipe);
#endif
	return res;
}

////////////////////////////////WALK///////////////////////////////////

void os_path::walk(string path, st_data& data)
{
	unordered_map<string, vector<string>> mp_dirnames;
	unordered_map<string, vector<string>> mp_filenames;
	vector<string> v_seq;
	if (path[path.length() - 1] == m_sep)
	{
		path.pop_back();
	}
	string s_cmd;
#ifdef OS_LINUX
	s_cmd = "find " + path + " -print";
	FILE* f_pipe = popen(s_cmd.c_str(), "r");
#elif OS_WINDOWS
	s_cmd = "dir /s /b " + path;
	FILE* f_pipe = _popen(s_cmd.c_str(), "r");
#endif
	if (f_pipe == NULL)
	{
		printf("Error in command execution\n");
		return;
	}
	while (fgets(m_buffer.data(), MAXBUFFER, f_pipe) != NULL)
	{
		string s_buf = m_buffer.data();
		s_buf.pop_back();
		s_buf = os_path::cleanpathstr(s_buf);
		pair<string, string> p;
		if (os_path::isdir(s_buf))
		{
			p = os_path::split(s_buf);
			mp_dirnames[p.first].push_back(p.second);
			v_seq.push_back(s_buf);
		}
		else if (os_path::isfile(s_buf))
		{
			p = os_path::split(s_buf);
			mp_filenames[p.first].push_back(p.second);
		}
	}
#ifdef OS_LINUX
	pclose(f_pipe);
#elif OS_WINDOWS
	_pclose(f_pipe);
#endif
	for (string s_dir : v_seq)
	{
		data.dirpath.push_back(s_dir);
		data.dirnames.push_back(mp_dirnames[s_dir]);
		data.filenames.push_back(mp_filenames[s_dir]);
	}
}



