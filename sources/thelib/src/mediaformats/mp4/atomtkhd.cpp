/* 
*  Copyright (c) 2010,
*  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
*  
*  This file is part of crtmpserver.
*  crtmpserver is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  crtmpserver is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "mediaformats/mp4/atomtkhd.h"

AtomTKHD::AtomTKHD(MP4Document *pDocument, uint32_t type, uint64_t size, uint64_t start)
: VersionedAtom(pDocument, type, size, start) {
    _creationTime = 0;
    _modificationTime = 0;
    _trackId = 0;
    memset(_reserved1, 0, 4);
    _duration = 0;
    memset(_reserved2, 0, 8);
    _layer = 0;
    _alternateGroup = 0;
    _volume = 0;
    memset(_reserved3, 0, 2);
    memset(_matrixStructure, 0, 36);
    _trackWidth = 0;
    _trackHeight = 0;
}

AtomTKHD::~AtomTKHD() {
}

uint32_t AtomTKHD::GetWidth() {
    return _trackWidth >> 16;
}

uint32_t AtomTKHD::GetHeight() {
    return _trackHeight >> 16;
}

bool AtomTKHD::ReadData() {
    if (!ReadUInt32(_creationTime)) {
        FATAL("Unable to read creation time");
        return false;
    }
    //FINEST("_creationTime: %u", _creationTime);

    if (!ReadUInt32(_modificationTime)) {
        FATAL("Unable to read modification time");
        return false;
    }
    //FINEST("_modificationTime: %u", _modificationTime);

    if (!ReadUInt32(_trackId)) {
        FATAL("Unable to read track id");
        return false;
    }
    //FINEST("_trackId: %u", _trackId);

    if (!ReadArray(_reserved1, 4)) {
        FATAL("Unable to read reserved 1");
        return false;
    }

    if (!ReadUInt32(_duration)) {
        FATAL("Unable to read duration");
        return false;
    }
    //FINEST("_duration: %u", _duration);

    if (!ReadArray(_reserved2, 8)) {
        FATAL("Unable to read reserved 2");
        return false;
    }

    if (!ReadUInt16(_layer)) {
        FATAL("Unable to read layer");
        return false;
    }
    //FINEST("_layer: %u", _layer);

    if (!ReadUInt16(_alternateGroup)) {
        FATAL("Unable to read alternate group");
        return false;
    }
    //FINEST("_alternateGroup: %u", _alternateGroup);

    if (!ReadUInt16(_volume)) {
        FATAL("Unable to read volume");
        return false;
    }
    //FINEST("_volume: %u", _volume);

    if (!ReadArray(_reserved3, 2)) {
        FATAL("Unable to read reserved 3");
        return false;
    }

    if (!ReadArray(_matrixStructure, 36)) {
        FATAL("Unable to read matrix structure");
        return false;
    }

    if (!ReadUInt32(_trackWidth)) {
        FATAL("Unable to read track width");
        return false;
    }
    //FINEST("_trackWidth: %u", _trackWidth);

    if (!ReadUInt32(_trackHeight)) {
        FATAL("Unable to read track height");
        return false;
    }
    //FINEST("_trackHeight: %u", _trackHeight);

    return true;
}

