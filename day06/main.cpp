#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "util.h"

std::vector<std::string> readInput(const char* filename) {
    std::ifstream input{filename};
    if (!input.is_open()) {
        std::cerr << "could not open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> result;
    std::string line;
    while(std::getline(input, line)) {
        result.push_back(line);
    }

    return result;
}

struct Orbit {
    std::string sourcePlanet;
    std::string orbitPlanet;
};

struct OrbitCounter {
    unsigned directOrbits{0};
    unsigned indirectOrbits{0};
};

Orbit stringToOrbit(const std::string& str) {
    auto split = util::split(str, ')');
    return Orbit{split[0], split[1]};
}

std::string findRoot(const std::vector<Orbit>& orbits, const std::set<std::string>& planets) {
    for (const auto& planet : planets) {
        auto planetIsOnOrbit = [planet](const Orbit& orbit) {
            return orbit.orbitPlanet == planet;
        };
        if (std::find_if(orbits.begin(), orbits.end(), planetIsOnOrbit) == orbits.end()) {
            return planet;
        }
    }

    return std::string{};
}

using OrbitsMap = std::unordered_map<std::string, std::vector<std::string>>;
using OrbitsCounters = std::unordered_map<std::string, OrbitCounter>;

void countOrbits(const std::string& root, const OrbitsMap& orbitsMap, OrbitsCounters& orbitsCounters) {
    auto& rootCounter = orbitsCounters[root];
    if (!orbitsMap.count(root))
        return;

    const auto& orbitsPlanets = orbitsMap.at(root);
    
    for (const auto& planet : orbitsPlanets) {
        if (rootCounter.directOrbits == 0 && rootCounter.indirectOrbits == 0) {
            orbitsCounters[planet].directOrbits = 1;
        } else {
            orbitsCounters[planet].directOrbits = 1;
            orbitsCounters[planet].indirectOrbits = rootCounter.indirectOrbits + 1;
        }



        countOrbits(planet, orbitsMap, orbitsCounters);
    }
}

bool orbitsPlanetsHaveSourcePlanet(const OrbitsMap& orbitsMap, const std::string& root, const std::string& source, std::vector<std::string>& path) {
    const auto& orbitPlanets = orbitsMap.at(root);

    if (root == "K")
        std::cout << "dd" << std::endl;

    for (const auto& orbitPlanet : orbitPlanets) {
        if (orbitPlanet == source) {
            path.push_back(root);
            return true;
        } else if (!orbitsMap.count(orbitPlanet)) {
            continue;
        } else if (orbitsPlanetsHaveSourcePlanet(orbitsMap, orbitPlanet, source, path)) {
            path.push_back(root);
            return true;
        }
    }

    return false;
}

std::vector<std::string> findPath(const OrbitsMap& orbitsMap, const std::string& root, const std::string& source) {
    std::vector<std::string> path;

    orbitsPlanetsHaveSourcePlanet(orbitsMap, root, source, path);

    return path;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto input = readInput(argv[1]);

    std::vector<Orbit> inputOrbits(input.size());
    std::transform(input.begin(), input.end(), inputOrbits.begin(), stringToOrbit);

    std::set<std::string> planets;
    auto copyPlanetToSet = [&planets](const Orbit& orbit) {
        planets.insert(orbit.orbitPlanet);
        planets.insert(orbit.sourcePlanet);
    };
    std::for_each(inputOrbits.begin(), inputOrbits.end(), copyPlanetToSet);

    auto root = findRoot(inputOrbits, planets);
    std::cout << root << std::endl;

    OrbitsMap orbitsMap;
    OrbitsCounters orbitsCounters;

    for (const auto& orbit : inputOrbits) {
        orbitsMap[orbit.sourcePlanet].push_back(orbit.orbitPlanet);
    }

    countOrbits(root, orbitsMap, orbitsCounters);

    unsigned result{0};
    for (const auto& [planet, counter] : orbitsCounters) {
        result += counter.directOrbits + counter.indirectOrbits;
    }

    std::cout << result << std::endl;

    auto pathToYOU = findPath(orbitsMap, "COM", "YOU");
    auto pathToSAN = findPath(orbitsMap, "COM", "SAN");

    std::cout << "===========================" << std::endl;

    std::string searchPlanet;

    for (const auto& planet : pathToYOU) {
        if (std::find(pathToSAN.begin(), pathToSAN.end(), planet) != pathToSAN.end()) {
            searchPlanet = planet;
            break;
        }
    }

    auto it1 = std::find(pathToSAN.begin(), pathToSAN.end(), searchPlanet);
    auto it2 = std::find(pathToYOU.begin(), pathToYOU.end(), searchPlanet);

    std::cout << std::distance(pathToSAN.begin(), it1) << std::endl;
    std::cout << std::distance(pathToYOU.begin(), it2) << std::endl;
    std::cout << std::distance(pathToSAN.begin(), it1) + std::distance(pathToYOU.begin(), it2) << std::endl;
    return 0;
}
