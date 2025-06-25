#include "./Parser.hpp"

/* ────────────── LOCATION ────────────── */
void locationParser(std::ifstream &file, LocationParse &location)
{
    int depth = 1;
    std::string line;

    while (std::getline(file, line))
    {
        for (std::size_t idx = 0; idx < line.size(); ++idx)
        {
            if (line[idx] == '{') ++depth;
            if (line[idx] == '}') --depth;
        }
        if (depth == 0) break;

        std::vector<std::string> buffer = splitAndRemoveSpaces(line);
        if (buffer.empty()) continue;

        if (location.hasProperty(buffer[0]))
        {
            std::vector<std::string> vals(buffer.begin() + 1, buffer.end());
            location.reset(buffer[0], vals);
        }
    }
} 

/* ─────────────── SERVER ─────────────── */
void serverParser(std::ifstream &file, ServerParse &server)
{
    int depth = 1;
    std::string line;

    while (std::getline(file, line))
    {
        for (std::size_t idx = 0; idx < line.size(); ++idx)
        {
            if (line[idx] == '{') ++depth;
            if (line[idx] == '}') --depth;
        }
        if (depth == 0) break;

        std::vector<std::string> buffer = splitAndRemoveSpaces(line);
        if (buffer.empty()) continue;

        if (server.hasProperty(buffer[0]))
        {
            std::vector<std::string> vals(buffer.begin() + 1, buffer.end());
            server.reset(buffer[0], vals);
        }
        else if (buffer[0] == "location" && buffer.size() >= 2)
        {
            LocationParse location;

            std::vector<std::string> prefix;
            prefix.push_back(buffer[1]);
            location.reset("path_prefix", prefix);

            locationParser(file, location);
            --depth;
            server.addLocation(location);
        }
    }
}