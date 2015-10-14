/*
 * OnlyOnce.h
 *
 * A small library to allow checking if a process is already running, such
 * that the programmer may prevent it running twice.
 *
 * This only tells you and creates the locks - actually stopping the program
 * is up to you!
 *
 * It's probably Linux specific but other POSIX may work
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

#ifndef ONLYONCE_H
#define ONLYONCE_H

#include <string>

namespace helpers
{


void MakeLock(std::string filename);

/**
 * Folder to store PID files in. Suggestions are:
 * - /var/tmp or ~/. for user level applications
 * - /var/run for root things
 */
const std::string PID_FOLDER = "/var/tmp/";

/**
 * Creates a lock with ProcessName if there is no lock on ProcessName.
 * There is a lock on ProcessName if:
 *  - /var/tmp/X.pid exists, where X is the process name; and
 *  - the process identified by that file is running
 * @param ProcessName Name of lock (filename in /var/run/filename.pid)
 * @return True if a new lock was established. False if already locked.
 */
bool LockMeUp(std::string ProcessName);

/**
 * Removes the process lock with ProcessName
 * @param ProcessName Name of lock (filename in /var/run/filename.pid)
 */
void AndImDone(std::string ProcessName);

/**
 * Checks whether process with pid is running
 * @param pid Pid to check
 * @return True if pid is running
 */
bool CheckPidRunning(unsigned int pid);

/**
 * Checks whether there is a lock on ProcessName
 * There is a lock on ProcessName if:
 *  - /var/tmp/X.pid exists, where X is the process name; and
 *  - the process identified by that file is running
 * @param ProcessName Name of lock (filename in /var/run/filename.pid)
 * @return True if there is a lock on ProcessName
 */
bool AmIRunning(std::string ProcessName);

}

#endif
