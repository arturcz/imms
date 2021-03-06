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
#ifndef __FLAGS_H
#define __FLAGS_H

namespace Flags
{
    enum FlagVals {
        first       = (1 << 0),     // 1
        jumped_to   = (1 << 1),     // 2
        jumped_from = (1 << 2),     // 4
        bad         = (1 << 3),     // 8
        idleness    = (1 << 4),     // 16
        active      = (1 << 5)      // 32
    };

    inline int deltify(time_t skipped_at, int flags)
    {
        if (flags & bad)
            return 0;

        bool skipped = (skipped_at != 10);

        int bonus = ((flags & idleness) ? ((flags & active) ? 2 : 0) : 1);

        if (skipped && (flags & jumped_from))
            return -1;

        if (flags & jumped_to)
            return skipped ? 1 : (7 + bonus);

        if (skipped)
            return ((flags & first) ? -6 : -4) - bonus;

        return ((flags & first) ? 5 : 1) + bonus;
    }

    inline int undeltify(int delta)
    {
        switch (delta)
        {
            case -8:
                return first | idleness | active;
            case -7:
                return first;
            case -6:
                return first | idleness;
            case -5:
                return 0;
            case -4:
                return idleness;
            case -1:
                return jumped_from | idleness;
            case 1:
                return idleness;
            case 2:
                return 0;
            case 3:
                return idleness | active;
            case 5:
                return first | idleness;
            case 6:
                return first;
            case 7:
                return jumped_to | idleness;
            case 8:
                return jumped_to;
            case 9:
                return jumped_to | idleness | active;
            default:
                return 0;
        }
    }
}

#endif
