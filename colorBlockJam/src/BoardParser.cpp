#include "BoardParser.h"

#include <fstream>
#include <sstream>
#include <cstring>

Board* BoardParser::loadFromFile(
    const char* filename
) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        return nullptr;
    }

    char name[64] = "";

    int width = 0;
    int height = 0;
    int stepLimit = 0;

    // capacidades iniciales
    int maxBlocks = 32;
    int maxExits = 32;
    int maxGates = 32;

    std::string line;

    // =========================
    // LEER HEADER
    // =========================

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        if (line.find("NAME") != std::string::npos) {

            sscanf(
                line.c_str(),
                "NAME = %s",
                name
            );
        }

        else if (line.find("WIDTH") != std::string::npos) {

            sscanf(
                line.c_str(),
                "WIDTH = %d",
                &width
            );
        }

        else if (line.find("HEIGHT") != std::string::npos) {

            sscanf(
                line.c_str(),
                "HEIGHT = %d",
                &height
            );
        }

        else if (line.find("STEP_LIMIT") != std::string::npos) {

            sscanf(
                line.c_str(),
                "STEP_LIMIT = %d",
                &stepLimit
            );

            break;
        }
    }

    Board* board = new Board(
        name,
        width,
        height,
        stepLimit,
        maxBlocks,
        maxExits,
        maxGates
    );

    // =========================
    // LEER SECCIONES
    // =========================

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        // =====================
        // BLOCKS
        // =====================

        if (line == "[BLOCK]") {

            while (std::getline(file, line)) {

                if (line.empty()) {
                    break;
                }

                if (line[0] == '[') {
                    file.seekg(-((int)line.size()) - 1,
                               std::ios_base::cur);
                    break;
                }

                int id;
                char color;
                int bw, bh;
                int x, y;

                sscanf(
                    line.c_str(),
                    "%d COLOR=%c WIDTH=%d HEIGHT=%d INIT_X=%d INIT_Y=%d",
                    &id,
                    &color,
                    &bw,
                    &bh,
                    &x,
                    &y
                );

                int geoSize = bw * bh;

                bool* geo = new bool[geoSize];

                // encontrar GEOMETRY=
                size_t pos = line.find("GEOMETRY=");

                if (pos != std::string::npos) {

                    std::stringstream ss(
                        line.substr(pos + 9)
                    );

                    for (int i = 0; i < geoSize; i++) {

                        int v;
                        ss >> v;

                        geo[i] = (v == 1);
                    }
                }

                Block* blk = new Block(
                    id,
                    color,
                    bw,
                    bh,
                    x,
                    y,
                    0,
                    geo
                );

                board->addBlock(blk);
            }
        }

        // =====================
        // WALLS
        // =====================

        else if (line == "[WALL]") {

            for (int r = 0; r < height; r++) {

                std::getline(file, line);

                for (int c = 0;
                     c < width && c < (int)line.size();
                     c++) {

                    if (line[c] == '#') {
                        board->grid[r][c]
                            .setAsWall();
                    }
                }
            }
        }

        // =====================
        // EXITS
        // =====================

        else if (line == "[EXIT]") {

            while (std::getline(file, line)) {

                if (line.empty()) {
                    break;
                }

                if (line[0] == '[') {
                    file.seekg(-((int)line.size()) - 1,
                               std::ios_base::cur);
                    break;
                }

                char color;
                int x, y;
                char orientation;
                int li, lf, step;

                sscanf(
                    line.c_str(),
                    "COLOR=%c X=%d Y=%d ORIENTATION=%c LI=%d LF=%d STEP=%d",
                    &color,
                    &x,
                    &y,
                    &orientation,
                    &li,
                    &lf,
                    &step
                );

                Exit ex(
                    color,
                    x,
                    y,
                    orientation,
                    li,
                    lf,
                    step
                );

                board->addExit(ex);
            }
        }
    }

    return board;
}                