#include "misc.hpp"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <vector>
#include <sstream>
#include <iostream>
#include <cassert>

#ifdef WIN32
#include <dirent.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#endif

namespace mars
{
    namespace utils
    {

        using namespace std;

        bool matchPattern(const std::string &pattern, const std::string &str)
        {
            size_t pos1 = 0, pos2 = 0;

            // chop up pattern
            std::vector<std::string> patternList;
            while (1)
            {
                pos2 = pattern.find("*", pos1);
                if (pos2 == pattern.npos)
                {
                    if (pos1 != 0)
                        patternList.push_back(pattern.substr(pos1));
                    break;
                }
                patternList.push_back(pattern.substr(pos1, pos2 - pos1));
                pos1 = pos2 + 1;
            }

            // no wildcards. do direct test
            if (patternList.empty())
            {
                return pattern == str;
            }

            // special case the first pattern because it must match at pos == 0
            std::vector<std::string>::iterator patternListIt = patternList.begin();
            int result = str.compare(0, patternListIt->length(), *patternListIt);
            if (result != 0)
                return false;
            pos1 = patternListIt->length();
            ++patternListIt;
            // do the matching
            for (/*nothing*/; patternListIt != patternList.end(); ++patternListIt)
            {
                pos1 = str.find(*patternListIt, pos1);
                if (pos1 == str.npos)
                    return false;
                pos1 += patternListIt->length();
            }
            return true;
        }

        std::string trim(const std::string &str)
        {

            int front_idx, back_idx, len;

            front_idx = 0;
            back_idx = (len = str.size()) - 1;

            while (isspace(str[front_idx]) && front_idx < len)
                front_idx++;
            while (isspace(str[back_idx]) && back_idx > 0)
                back_idx--;

            if (front_idx > back_idx)
                return "";
            else
                return str.substr(front_idx, back_idx - front_idx + 1);
        }

        void handleFilenamePrefix(std::string *file, const std::string &prefix)
        {
            *file = pathJoin(prefix, *file);
        }

        std::string pathJoin(const std::string &path1, const std::string &path2)
        {
            if (path1.empty())
                return path2;
            if (path2.front() == '/')
            {
                // we have an absolute path
                return path2;
            }
#ifdef WIN32
            if (path2[1] == ':')
            {
                // we have an absolute path
                return path2;
            }
#endif
            std::string tmp = path1;
            if (tmp.back() != '/')
            {
                tmp += "/";
            }

            tmp += path2;
            return tmp;
        }

        void removeFilenamePrefix(std::string *file)
        {
            size_t pos;

            if ((pos = file->rfind('/')) != std::string::npos)
            {
                *file = file->substr(pos + 1);
            }
        }

        void removeFilenameSuffix(std::string *file)
        {
            size_t pos;

            if ((pos = file->rfind('.')) != std::string::npos)
            {
                *file = file->substr(0, pos);
            }
        }

        std::string getFilenameSuffix(const std::string &file)
        {
            size_t pos;

            if ((pos = file.rfind('.')) != std::string::npos)
            {
                return file.substr(pos);
            }
            return "";
        }

        std::string getCurrentWorkingDir()
        {
            const int BUFFER_SIZE = 512;
            char buffer[BUFFER_SIZE];
            if (!getcwd(buffer, BUFFER_SIZE))
            {
                std::cerr << "misc:: error while getting current working dir"
                          << std::endl;
                return "";
            }
            return std::string(buffer);
        }

        std::string getPathOfFile(const std::string &filename)
        {
            std::string path = "./";
            size_t pos;

            if ((pos = filename.rfind('/')) != std::string::npos)
            {
                path = filename.substr(0, pos + 1);
            }
            return path;
        }

        unsigned int createDirectory(const std::string &dir, int mode)
        {
            std::string s_tmpString = dir;
            DIR *p_Directory;

            p_Directory = opendir(dir.c_str());
            if (p_Directory != NULL)
            {
                closedir(p_Directory);
                return 2;
            }

            char tmp[FILENAME_MAX];
            char *p = 0;
            snprintf(tmp, sizeof(tmp), "%s", dir.c_str());
            size_t len = strlen(tmp);
            if (tmp[len - 1] == '/')
            {
                tmp[len - 1] = 0;
            }
            int result = 0;
            for (p = tmp + 1; *p; p++)
            {
                if (*p == '/')
                {
                    *p = 0;
                    if (pathExists(tmp))
                    {
                        // Directory already exists, assuming this is a first already existing part of the path
                    }
                    else
                    {
#ifdef WIN32
                        result = mkdir(tmp);
#else
                        result = mkdir(tmp, mode);
#endif
                    }
                    if (result == -1)
                    {
                        break;
                    }
                    *p = '/';
                }
            }

            if (result != -1)
            {
#ifdef WIN32
                result = mkdir(tmp);
#else
                result = mkdir(tmp, mode);
#endif
            }
            if (result == -1)
            {
                fprintf(stderr, "misc:: could not create dir: %s\n", dir.c_str());
                return 0;
            }
            return 1;
        }

        std::vector<std::string> explodeString(const char c, const std::string &s)
        {
            std::vector<std::string> result;
            std::stringstream stream(s);
            std::string entry;

            while (std::getline(stream, entry, c))
            {
                result.push_back(entry);
            }
            return result;
        }

        std::string replaceString(const std::string &source, const std::string &s1,
                                  const std::string &s2)
        {
            std::string back = source;
            size_t found = back.find(s1);
            while (found != std::string::npos)
            {
                back.replace(found, s1.size(), s2);
                found = back.find(s1, found + s2.size());
            }
            return back;
        }

        std::string toupper(const std::string &s)
        {
            std::string result;
            for (size_t i = 0; i < s.size(); ++i)
            {
                result += std::toupper(s[i]);
            }
            return result;
        }

        std::string tolower(const std::string &s)
        {
            std::string result;
            for (size_t i = 0; i < s.size(); ++i)
            {
                result += std::tolower(s[i]);
            }
            return result;
        }

    } // end of namespace utils

} // end of namespace mars
