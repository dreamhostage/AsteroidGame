#include "Asteroid.h"

int main(int argc, char* argv[])
{
    int x = 0;
    int y = 0;
    int mapX = 0;
    int mapY = 0;
    int num_asteroids = 0;
    int num_ammo = 0;
    int godmode = 0;

    std::string foundCommand;
    std::string temp;
    std::string temp2;

    if (argc > 1) {
        for (int i = 0; i < argc; ++i) {
            if (i > 0) {
                foundCommand = argv[i];
                if (foundCommand.find("-window") != std::string::npos) {
                    temp.clear();
                    if (i + 1 < argc) {
                        temp = argv[i + 1];
                        int k = 0;
                        temp2.clear();
                        while (k < temp.size() && temp[k] != 'x')
                            temp2 += temp[k++];
                        if (temp[k] == 'x') {
                            x = atoi(&temp2[0]);
                            ++k;
                            temp2.clear();
                            while (k < temp.size()) {
                                temp2 += temp[k++];
                            }
                            y = atoi(&temp2[0]);
                        }
                    }
                }

                if (foundCommand.find("-map") != std::string::npos) {
                    temp.clear();
                    if (i + 1 < argc) {
                        temp = argv[i + 1];
                        int k = 0;
                        temp2.clear();
                        while (k < temp.size() && temp[k] != 'x')
                            temp2 += temp[k++];
                        if (temp[k] == 'x') {
                            mapX = atoi(&temp2[0]);
                            ++k;
                            temp2.clear();
                            while (k < temp.size()) {
                                temp2 += temp[k++];
                            }
                            mapY = atoi(&temp2[0]);
                        }
                    }
                }

                if (foundCommand.find("-num_asteroids") != std::string::npos) {
                    temp.clear();
                    if (i + 1 < argc) {
                        num_asteroids = atoi(argv[i + 1]);
                    }
                }
                if (foundCommand.find("-num_ammo") != std::string::npos) {
                    temp.clear();
                    if (i + 1 < argc) {
                        num_ammo = atoi(argv[i + 1]);
                    }
                }
                if (foundCommand.find("-godmode") != std::string::npos) {
                    temp.clear();
                    if (i + 1 < argc) {
                        godmode = atoi(argv[i + 1]);
                    }
                }
            }
        }
    }

    framework game(x, y, num_asteroids, num_ammo, godmode, mapX, mapY);
    game.run();

    return 0;
}
