#ifndef __IDENTIFY_H
#define __IDENTIFY_H

#include <utility>
#include <string>

using std::pair;
using std::string;

typedef pair<string, string> StringPair;

class Song
{
public:
    Song(const string &path = "", int _uid = -1, int _sid = -1);

    void set_last(time_t last);
    void set_info(const StringPair &info);
    void set_rating(int rating);
    void set_trend(int trend);
    void set_acoustic(const string &spectrum, const string &bpmgraph);
    void increment_playcounter();

    int get_rating();
    int get_trend();
    time_t get_last();
    int get_playcounter();

    StringPair get_info();
    StringPair get_acoustic();

    int get_sid() { return sid; }
    int get_uid() { return uid; }
    const string &get_path() { return path; }

    bool isok() { return uid != -1 && path != ""; }

    void reset() { playcounter = uid = sid = -1; artist = title = ""; }
protected:
    void register_new_sid();
    void identify(time_t modtime);

    int uid, sid, playcounter;
    string title, artist, path;
};

#endif