#ifndef UUID_H
#define UUID_H

#include <random>
#include <sstream>
#include <iomanip>
#include <string>

class UUID
{
public:
    [[nodiscard]] static std::string GenerateUUID() 
    {
        // Static PRNG and distribution to avoid recreating every call
        static std::mt19937_64 gen(std::random_device{}());
        static std::uniform_int_distribution<uint64_t> dis;

        uint64_t part1 = dis(gen);
        uint64_t part2 = dis(gen);

        std::stringstream ss;
        ss  << std::hex 
            << std::setfill('0')
            << std::setw(16) << part1
            << std::setw(16) << part2;

        return ss.str();
    }
};

#endif // UUID_H
