#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include "Tournament.h"
#include "Tile.h"

class Serializer {
public:
    /* --- Constructor --- */

    Serializer() = delete;

    /* --- Destructor --- */

    ~Serializer() = delete;

    /* --- Utility Functions --- */

    static bool saveGame(const std::string& filename, const Tournament& tournament);

    static bool loadGame(const std::string& filename, Tournament& tournament);

private:
    static Tile parseTile(const std::string& token);

};

#endif