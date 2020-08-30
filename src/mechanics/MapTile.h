/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "core/Logger.h"

#include <genie/resource/Slope.h>
#include <genie/resource/MaskPattern.h>

class TerrainSprite;
typedef std::shared_ptr<TerrainSprite> TerrainPtr;
struct Entity;

struct Slope {
    enum Direction : uint8_t {
        Flat = 0,
        SouthUp     = 1 << 0,
        NorthUp     = 1 << 1,
        WestUp      = 1 << 2,
        EastUp      = 1 << 3,
        SouthWestUp = SouthUp | WestUp,
        NorthWestUp = NorthUp | WestUp,
        SouthEastUp = SouthUp | EastUp,
        NorthEastUp = NorthUp | EastUp,

        SouthWestEastUp = SouthUp | WestUp | EastUp,
        NorthWestEastUp = NorthUp | WestUp | EastUp,

        NorthSouthEastUp = NorthUp | SouthUp | EastUp,
        NorthSouthWestUp = NorthUp | SouthUp | WestUp,
    };

    Slope (const Direction s) : direction(s) {}
    Slope &operator =(const Direction s) noexcept { direction = s; return *this; }
    Slope &operator =(const uint8_t s) noexcept { direction = Direction(s); return *this; }

    inline bool operator <(const Direction other) const noexcept { return direction < other; }
    inline bool operator==(const Direction other) const noexcept { return other == direction; }
    inline bool operator!=(const Direction other) const noexcept { return other != direction; }
    inline bool operator <(const Slope other) const noexcept { return direction < other.direction; }
    inline bool operator==(const Slope other) const noexcept { return other.direction == direction; }

    inline operator Direction() const noexcept { return direction; }

    inline std::string toAbbreviation() const noexcept {
        switch (direction) {
        case Flat:
            return "Flat";
        case SouthUp:
            return "S";
        case NorthUp:
            return "N";
        case WestUp:
            return "W";
        case EastUp:
            return "E";
        case SouthWestUp:
            return "SW";
        case NorthWestUp:
            return "NW";
        case SouthEastUp:
            return "SE";
        case NorthEastUp:
            return "NE";
        case SouthWestEastUp:
            return "SWE";
        case NorthWestEastUp:
            return "NWE";
        case NorthSouthWestUp:
            return "NSW";
        case NorthSouthEastUp:
            return "NSE";
        default:
            return "Unknown (" + std::to_string(int(direction)) + ")";
        }
    }

    inline std::string toString() const noexcept {
        switch (direction) {
        case Flat:
            return "Flat";
        case SouthUp:
            return "SouthUp";
        case NorthUp:
            return "NorthUp";
        case WestUp:
            return "WestUp";
        case EastUp:
            return "EastUp";
        case SouthWestUp:
            return "SouthWestUp";
        case NorthWestUp:
            return "NorthWestUp";
        case SouthEastUp:
            return "SouthEastUp";
        case NorthEastUp:
            return "NorthEastUp";
        case SouthWestEastUp:
            return "SouthWestEastUp";
        case NorthWestEastUp:
            return "NorthWestEastUp";
        case NorthSouthWestUp:
            return "NorthWestEastUp";
        case NorthSouthEastUp:
            return "NorthWestEastUp";
        default:
            return "Unknown (" + std::to_string(int(direction)) + ")";
        }
    }

    inline genie::Slope toGenie() const noexcept {
        switch (direction){
        case Flat: return genie::SlopeFlat;
        case SouthUp: return genie::SlopeSouthUp;
        case NorthUp: return genie::SlopeNorthUp;
        case WestUp: return genie::SlopeWestUp;
        case EastUp: return genie::SlopeEastUp;

        case SouthWestUp: return genie::SlopeSouthWestUp;
        case NorthWestUp: return genie::SlopeNorthWestUp;
        case SouthEastUp: return genie::SlopeSouthEastUp;
        case NorthEastUp: return genie::SlopeNorthEastUp;

        case SouthWestEastUp: return genie::SlopeSouthWestEastUp;
        case NorthWestEastUp: return genie::SlopeNorthWestEastUp;
        case NorthSouthEastUp: return genie::SlopeNorthSouthEastUp;
        case NorthSouthWestUp: return genie::SlopeNorthSouthWestUp;

        default:
            WARN << "unhandled direction" << direction;
            return genie::SlopeFlat;
        }
    }

    Direction direction = Flat;
};


struct TileSlopes
{
    Slope self = Slope::Flat;

    Slope north = Slope::Flat;
    Slope south = Slope::Flat;

    Slope west = Slope::Flat;
    Slope east = Slope::Flat;

    Slope southWest = Slope::Flat;
    Slope southEast = Slope::Flat;

    Slope northWest = Slope::Flat;
    Slope northEast = Slope::Flat;

    bool operator==(const TileSlopes &other) const noexcept {
        return self == other.self &&
               north == other.north &&
               south == other.south &&
               west == other.west &&
               east == other.east &&
               southWest == other.southWest &&
               southEast == other.southEast &&
               northWest == other.northWest &&
               northEast == other.northEast;
    }
};

struct Blend  {
    enum BlendTile {
        LowerLeft1 = 0,
        UpperLeft1 = 4,
        LowerRight1 = 8,
        UpperRight1 = 12,

        Right = 16,
        Down = 17,
        Up = 18,
        Left = 19,

        UpperRightAndLowerLeft = 20,
        UpperLeftAndLowerRight = 21,

        OnlyRight = 22,
        OnlyDown = 23,
        OnlyUp = 24,
        OnlyLeft = 25,

        KeepUpperLeft = 26,
        KeepUpperRight = 27,
        KeepLowerRight = 28,
        KeepLowerLeft = 29,

        All = 30,

        BlendTileCount
    };

    inline void addBlend(const BlendTile blend) noexcept
    {
        bits |= 1 << blend;
    }

    inline bool operator ==(const Blend &other) const noexcept
    {
        return bits      == other.bits &&
               frame     == other.frame &&
               blendMode == other.blendMode &&
               terrainId == other.terrainId;
    }

    uint32_t bits = 0;

    uint16_t terrainId;
    int8_t frame = 0;
    uint8_t blendMode = 0;
};

struct MapTile
{
    static MapTile null;

    void reset() {
        yOffset = 0;
        slopes = TileSlopes();
        blends.clear();
    }

    std::vector<genie::Pattern> slopePatterns() const noexcept;

    int elevation = -1;
    int frame = 0;

    int yOffset = 0;

    uint32_t terrainId;
    std::vector<Blend> blends;
    TileSlopes slopes;

    bool operator==(const MapTile &other) const noexcept {
        return frame == other.frame && blends == other.blends && slopes == other.slopes && terrainId == other.terrainId;
    }

};

namespace std {

template<> struct hash<TileSlopes>
{
    inline size_t operator()(const TileSlopes &s) const noexcept {
        return hash<int8_t>()(s.self.direction) ^
               hash<int8_t>()(s.north.direction) ^
               hash<int8_t>()(s.south.direction) ^
               hash<int8_t>()(s.west.direction) ^
               hash<int8_t>()(s.east.direction) ^
               hash<int8_t>()(s.southWest.direction) ^
               hash<int8_t>()(s.southEast.direction) ^
               hash<int8_t>()(s.northWest.direction) ^
               hash<int8_t>()(s.northEast.direction);
    }
};

template<> struct hash<Blend>
{
    inline size_t operator()(const Blend &b) const noexcept {
        return hash<uint32_t>()(b.bits) ^ hash<uint8_t>()(b.blendMode) ^ hash<uint8_t>()(b.frame);
    }
};

template<> struct hash<MapTile>
{
    inline size_t operator()(const MapTile &t) const noexcept {
        size_t ret = hash<uint32_t>()(t.frame) ^ hash<TileSlopes>()(t.slopes);
        for (const Blend &b : t.blends) {
            ret ^= hash<Blend>()(b);
        }
        return ret;
    }
};

}

inline LogPrinter operator <<(LogPrinter os, const Slope &slope)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "Slope::";
    switch (slope.direction) {
    case Slope::Flat:
        os << "Flat";
        break;
    case Slope::SouthUp:
        os << "SouthUp";
        break;
    case Slope::NorthUp:
        os << "NorthUp";
        break;
    case Slope::WestUp:
        os << "WestUp";
        break;
    case Slope::EastUp:
        os << "EastUp";
        break;
    case Slope::SouthWestUp:
        os << "SouthWestUp";
        break;
    case Slope::NorthWestUp:
        os << "NorthWestUp";
        break;
    case Slope::SouthEastUp:
        os << "SouthEastUp";
        break;
    case Slope::NorthEastUp:
        os << "NorthEastUp";
        break;
    case Slope::SouthWestEastUp:
        os << "SouthWestEastUp";
        break;
    case Slope::NorthWestEastUp:
        os << "NorthWestEastUp";
        break;
    case Slope::NorthSouthWestUp:
        os << "NorthWestEastUp";
        break;
    case Slope::NorthSouthEastUp:
        os << "NorthWestEastUp";
        break;
    default:
        os << "Unknown (" << int(slope.direction);
        break;
    }

    os << separator;
    os.separator = separator;

    return os;
}
