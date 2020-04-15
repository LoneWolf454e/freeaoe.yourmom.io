#include <genie/script/ScnFile.h>
#include <filesystem>
#include <memory>
#include <string>

#include "core/Logger.h"
#include "mechanics/Map.h"
#include "mechanics/MapTile.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "resource/TerrainSprite.h"

static const char *gamePath = nullptr;

void testLoadTiles()
{
    DBG << "Testing map rendering speed";


    genie::CpxFile cpxFile;
    cpxFile.setFileName(std::string(gamePath) + "/Campaign/xcam3.cpx");
    cpxFile.load();

    genie::ScnFilePtr scenarioFile = cpxFile.getScnFile(0);

    Map map;
    map.create(scenarioFile->map);
    map.updateMapData();

    DBG << "Timing how long it takes to generate textures for all tiles";

    {
        TIME_THIS;
        for (int col = 0; col < map.columnCount(); col++) {
            for (int row = 0; row < map.rowCount(); row++) {
                MapTile &tile = map.getTileAt(col, row);
                TerrainPtr terrain = AssetManager::Inst()->getTerrain(tile.terrainId);
                terrain->texture(tile, nullptr);
            }
        }
    }
    DBG << "Cache size/rendered tiles" << AssetManager::Inst()->terrainCacheSize();

    DBG << "Timing fetching from cache (less than 10ms isn't printed)";

    {
        TIME_THIS;
        for (int col = 0; col < map.columnCount(); col++) {
            for (int row = 0; row < map.rowCount(); row++) {
                MapTile &tile = map.getTileAt(col, row);
                TerrainPtr terrain = AssetManager::Inst()->getTerrain(tile.terrainId);
                terrain->texture(tile, nullptr);
            }
        }
    }

}

int main(int argc, char *argv[])
{
    if (argc < 2)  {
        WARN << "Please pass path to game installation directory";
        return 1;
    }
    gamePath = argv[1];
//    std::string gamePath(argv[1]);
    std::string dataPath = std::string(gamePath) + "/Data/";
    try {
        if (!std::filesystem::exists(dataPath)) {
            throw std::runtime_error("Data path does not exist");
        }

        if (!LanguageManager::Inst()->initialize(gamePath)) {
            throw std::runtime_error("Failed to load language.dll");
        }

        if (!DataManager::Inst().initialize(dataPath)) {
            throw std::runtime_error("Failed to load game data");
        }

        if (!AssetManager::Inst()->initialize(dataPath, DataManager::Inst().gameVersion())) {
            throw std::runtime_error("Failed to load game assets");
        }
    } catch(const std::exception &e) {
        dataPath = "";
        WARN << "failed to load data:" << e.what();
    }
    DBG << "Successfully loaded data files";

    testLoadTiles();

    return 0;
}

