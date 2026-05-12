#include "BoardParser.h"
#include <fstream>
#include <sstream>
#include <cstring>

Board* BoardParser::loadFromFile(const char* filename) {

    std::ifstream file(filename);
    if (!file.is_open()) return nullptr;

    char name[64]  = "";
    int  width     = 0;
    int  height    = 0;
    int  stepLimit = 0;

    int maxBlocks = 32, maxExits = 32, maxGates = 32;

    std::string line;

    // =========================
    // LEER HEADER (con o sin [META])
    // =========================
    while (std::getline(file, line)) {

        if (line.empty() || line[0] == '[') continue;

        if (line.find("NAME") != std::string::npos)
            sscanf(line.c_str(), "NAME = %63s", name);

        else if (line.find("WIDTH") != std::string::npos)
            sscanf(line.c_str(), "WIDTH = %d", &width);

        else if (line.find("HEIGHT") != std::string::npos)
            sscanf(line.c_str(), "HEIGHT = %d", &height);

        else if (line.find("STEP_LIMIT") != std::string::npos) {
            sscanf(line.c_str(), "STEP_LIMIT = %d", &stepLimit);
            break;
        }
    }

    if (width <= 0 || height <= 0) return nullptr;

    Board* board = new Board(name, width, height, stepLimit,
                             maxBlocks, maxExits, maxGates);

    // =========================
    // LEER SECCIONES
    // =========================
    while (std::getline(file, line)) {

        if (line.empty()) continue;

        // =====================
        // BLOCKS
        // =====================
        if (line == "[BLOCK]") {

            while (std::getline(file, line)) {

                if (line.empty()) break;
                if (line[0] == '[') {
                    file.seekg(-((int)line.size()) - 1,
                               std::ios_base::cur);
                    break;
                }

                int  id;
                char color;
                int  bw, bh, x, y;

                sscanf(line.c_str(),
                    "%d COLOR=%c WIDTH=%d HEIGHT=%d INIT_X=%d INIT_Y=%d",
                    &id, &color, &bw, &bh, &x, &y);

                int   geoSize = bw * bh;
                bool* geo     = new bool[geoSize];

                size_t pos = line.find("GEOMETRY=");
                if (pos != std::string::npos) {
                    std::stringstream ss(line.substr(pos + 9));
                    for (int i = 0; i < geoSize; i++) {
                        int v; ss >> v;
                        geo[i] = (v == 1);
                    }
                }

                board->addBlock(new Block(id, color, bw, bh, x, y, 0, geo));
                delete[] geo;
            }
        }

        // =====================
        // WALLS
        // =====================
        else if (line == "[WALL]") {

            for (int r = 0; r < height; r++) {

                if (!std::getline(file, line)) break;

                for (int c = 0;
                     c < width && c < (int)line.size();
                     c++) {
                    if (line[c] == '#')
                        board->grid[r][c].setAsWall();
                }
            }
        }

        // =====================
        // EXITS
        // =====================
        else if (line == "[EXIT]") {

            while (std::getline(file, line)) {

                if (line.empty()) break;
                if (line[0] == '[') {
                    file.seekg(-((int)line.size()) - 1,
                               std::ios_base::cur);
                    break;
                }

                char color, orientation;
                int  x, y, li, lf, step;

                sscanf(line.c_str(),
                    "COLOR=%c X=%d Y=%d ORIENTATION=%c LI=%d LF=%d STEP=%d",
                    &color, &x, &y, &orientation, &li, &lf, &step);

                board->addExit(Exit(color, x, y, orientation, li, lf, step));
            }
        }

        // =====================
        // GATES
        // Formato: X=<int> Y=<int> ORIENTATION=<H,V>
        //          LI=<int> CI=<char> CF=<char> STEP=<int>
        // =====================
        else if (line == "[GATE]") {

            while (std::getline(file, line)) {

                if (line.empty()) break;
                if (line[0] == '[') {
                    file.seekg(-((int)line.size()) - 1,
                               std::ios_base::cur);
                    break;
                }

                int  x, y, li, step;
                char orientation;
                char ci_char, cf_char;

                // Formato sin COLOR: X=.. Y=.. ORIENTATION=.. LI=.. CI=<char> CF=<char> STEP=..
                sscanf(line.c_str(),
                    "X=%d Y=%d ORIENTATION=%c LI=%d CI=%c CF=%c STEP=%d",
                    &x, &y, &orientation, &li,
                    &ci_char, &cf_char, &step);

                board->addGate(Gate(x, y, orientation, li,
                                   (int)ci_char, (int)cf_char, step));
            }
        }
    }

    return board;
}