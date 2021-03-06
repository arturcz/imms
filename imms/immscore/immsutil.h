/*
 IMMS: Intelligent Multimedia Management System
 Copyright (C) 2001-2009 Michael Grigoriev

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/
#ifndef __UTILS_H
#define __UTILS_H

#include <sys/time.h>
#include <stdint.h>

#include <climits>
#include <string>
#include <vector>
#include <iostream>

#include "appname.h"

enum LogTypes {
    INFO,
    ERROR
};

#define     HOUR                    (60*60)
#define     DAY                     (24*HOUR)
#define     ROUND(x)                (int)((x) + 0.5)
#define     DIVROUNDUP(x,y)         ((int)(x + y - 1) / (int)y)

#define     LOG(x)                  \
            (x == INFO ? std::cout : std::cerr) << AppName << ": "
#define     DEBUGVAL(x)             LOG(ERROR) << #x << " = " << x << endl;

using std::string;
using std::vector;
using std::endl;

int imms_random(int max);
uint64_t usec_diff(struct timeval &tv1, struct timeval &tv2);

static inline float cap(float val, float max = 1) {
    return std::max(std::min(val, max), -max);
}

int socket_connect(const string &sockname);

class StackTimer
{
public:
    StackTimer();
    ~StackTimer();
private:
    struct timeval start;
};

class StackLockFile
{
public:
    StackLockFile(const string &_name);
    ~StackLockFile();
    bool isok() { return name != ""; }
private:
    string name;
};

template <typename NUM>
class StatCollector
{
public:
    StatCollector() : maxv(0), minv(0), sum(0), num(0) {}
    void process(NUM n) {
        if (!num)
            maxv = minv = n;
        ++num;
        sum += n;
        maxv = std::max(maxv, n);
        minv = std::min(minv, n);
    }
    void finish() {
        DEBUGVAL(maxv);
        DEBUGVAL(minv);
        double avg = sum;
        if (num)
            avg /= num;
        DEBUGVAL(avg);
    }
private:
    NUM maxv, minv, sum;
    int num;
};

string get_imms_root(const string &file = "");

string path_normalize(const string &path);

float rms_string_distance(const string &s1, const string &s2,
        int max = INT_MAX);
int listdir(const string &dirname, vector<string> &files);
bool file_exists(const string &filename);

#endif
