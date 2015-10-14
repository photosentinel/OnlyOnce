/*
 * OnlyOnce.cpp
 *
 * Copyright (c) 2015 Cornerstone Solutions Pty Ltd
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   * Neither the name of the project's author nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdexcept>
#include <unistd.h>
#include "OnlyOnce.h"

namespace helpers
{

int GetPidFromLock(std::string filename);
bool FileExists(std::string filename);
bool FolderExists(std::string foldername);
void RemoveLockFile(std::string filename);

bool LockMeUp(std::string ProcessName)
{
    if (!AmIRunning(ProcessName))
    {
        MakeLock(ProcessName);
        return true;
    }
    else
    {
        return false;
    }
}


void AndImDone(std::string ProcessName)
{
    RemoveLockFile(ProcessName);
}

bool CheckPidRunning(unsigned int pid)
{
    // Checks whether folder /proc/pid exists
    return FolderExists ("/proc/" + std::to_string(pid));
}

bool AmIRunning(std::string ProcessName)
{
    if (FileExists(PID_FOLDER + ProcessName + ".pid"))
    {
        unsigned int pid = GetPidFromLock(ProcessName);
        return CheckPidRunning(pid);
    }
    else
    {
        return false;
    }
}

/**
 * Makes a lock file with current pid in PID_FOLDER/filename.pid
 * @param filename File to write pid to
 */
void MakeLock(std::string filename)
{
    std::string path = PID_FOLDER + filename + ".pid";
    std::ofstream file(path.c_str());
    int pid = getpid(); //getpid() is POSIX from unistd.h
    file << pid << "\n";
    file.close();
}

/**
 * Returns pid from /var/run/filename.pid
 * @param filename File to get pid from
 * @return pid from file
 */
int GetPidFromLock(std::string filename)
{
    std::string path = PID_FOLDER + filename + ".pid";
    std::ifstream ifile(path.c_str());
    int pid;
    ifile >> pid;
    ifile.close();
    return pid;
}

/**
 * Check if a file exists
 * @param filename File to check
 * @return True, if file exists
 */
bool FileExists(std::string filename)
{
    std::ifstream file(filename.c_str());
    return file;
}

/**
 * Check if folder exists
 * @param foldername Folder to check
 * @return True, if folder exists
 */
bool FolderExists(std::string foldername)
{
    // If >C++17 - should be using the filesystem
    // Boost is also a good cross platform solution
    // This is POSIX specific, messy, C style, and a little smelly
    // See http://stackoverflow.com/questions/3828192/checking-if-a-directory-exists-in-unix-system-call
    struct stat sb;
    if (stat(foldername.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) // URGH!
    {
        return true;
    }
    return false;
}

/**
 * Removes pid lock file /var/tmp/filename.pid
 */
void RemoveLockFile(std::string filename)
{
    std::string path = PID_FOLDER + filename + ".pid";
    std::remove(path.c_str());
}

}
