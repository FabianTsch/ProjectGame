#include "init.h"

std::vector<int> init::loadm(std::string filename, size_t size_m){
    // Öffnen der Datei
    std::ifstream FileMap(filename);
    if (FileMap.fail()) std::cerr << "Fehler!!!";

    // Größe der Datie ermitteln
    FileMap.seekg(0, std::ios::end);
    size_t size = FileMap.tellg();
    FileMap.seekg(0, std::ios::beg);

    // Lesen der Datei
    char* puffer = new char[size];
    FileMap.read(puffer, size);
    FileMap.close();
    std::string temp = puffer;
    delete[] puffer;

    // Verarbeitung der Daten
    std::stringstream strstr;
    char noUse;
    int val;
    std::vector<int> map;

    for (std::string::iterator it = temp.begin(); it < temp.end(); ++it) {
        if (*it == '\n')
            *it = ',';
    }

    strstr << temp;
    for (size_t i = 0; i < size_m; i++) {
        strstr >> val;
        strstr >> noUse;
        map.push_back(val);
    }

    return map;
}

