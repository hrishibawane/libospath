/////////////////////////PREPROCESSOR DIRECTIVES//////////////////////////

#pragma once

#ifndef OS_PATH_HPP
#define OS_PATH_HPP

#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS 1
#else
#define OS_LINUX 1
#endif
#define MAXBUFFER 4096

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <array>
#include <stack>
#include <sstream>
#include <climits>
#include <sys/stat.h>

/////////////////////////////NAMESPACES/////////////////////////////

using namespace std;

////////////////////////////CLASS DECLARATION/////////////////////////

class os_path
{
	private:
		/* buffer for data transfers */
		array<char, MAXBUFFER> m_buffer;

		/* stat struct to store and retrieve file info */
		struct stat m_info;

		/**
		 * Generic function to invoke stat() system call
		 * @param path - pathname
		 * @returns stat() call's return code
		 */
		int getstatinfo(const string& path);

	public:
		/**
		 * Constructor
		 */
		os_path();

		/**
		 * Destructor
		 */
		~os_path();

		/**
		 * Return a normalized absolutized version of
		 * pathname path for a valid path
		 * @param path - pathname
		 * @returns absolute path from root to path
		 */
		string abspath(const string& path);

		/**
		 * Return the base name of pathname path
		 * @param path - pathname
		 * @returns basename
		 */
		string basename(const string& path);

		/**
		 * Return the longest path prefix(char-by-char)
		 * that is a prefix of all paths in vector paths
		 * @param paths - list of paths
		 * @returns longest path prefix
		 */
		string commonprefix(const vector<string>& paths);

		/**
		 * Check if path refers to an existing(valid) path
		 * @param path - pathname
		 * @returns true if valid, false otherwise
		 */
		bool exists(const string& path);

		/**
		 * Return the time of last access of path
		 * @param path - pathname
		 * @returns floating point number giving the
		 * number of seconds since epoch
		 */
		double getatime(const string& path);

		/**
		 * Return the time of last modification of path
		 * @param path - pathname
		 * @returns floating point number giving the
		 * number of second since epoch
		 */
		double getmtime(const string& path);
		
		/**
		 * Return the system's ctime which, on UNIX is
		 * time of the last metadata change, and on Windows,
		 * is creation time for path
		 * @param path - pathname
		 * @returns floating point number giving the
		 * number of seconds since epoch
		 */
		double getctime(const string& path);

		/**
		 * Return the size, in bytes, of path
		 * @param path - pathname
		 * @returns size in bytes
		 */
		long int getfilesize(const string& path);

		/**
		 * Checks if path is an existing regular file
		 * @param path - pathname
		 * @returns true if regular file, false otherwise
		 */
		bool isfile(const string& path);

		/**
		 * Checks if path is an existing directory
		 * @param path - pathname
		 * @returns true if directory, false otherwise
		 */
		bool isdir(const string& path);

		/**
		 * Return a relative filepath to path either from current
		 * directory or from optional start directory
		 * @param path - pathname
		 * @param start - optional start directory
		 * @returns relative path
		 */
		string relpath(const string& path, string start = ".");

		/**
		 * Split the pathname path into a pair, (head, tail)
		 * where tail is the last pathname component and head
		 * is everything leading up to that
		 * @param path - pathname
		 * @returns pair with head as first and tail as second
		 */
		pair<string, string> split(const string& path);

		/**
		 * Split the pathname path into a pair (root, ext)
		 * such that root + ext == path
		 * @param path - pathname
		 * @returns pair with root as first and ext as second
		 */
		pair<string, string> splitext(const string& path);
};

#endif
