#ifndef LASREADER_H
#define LASREADER_H

#include <memory>
#include <string>
#include <vector>
#include "headerstock.h"


// Forward declarations
struct Vertex;

/**
   @brief The LASReader class reads cloud point data from a binary LAS file
 */
class LASReader
{
public:
    LASReader(const std::string &path);

    void readHeaderStock(std::istream &stream);
    void readPointData(std::istream &stream);
    std::vector<Vertex> &getPointData();
    const HeaderStock &getHeaderStock();

private:
    template<typename T>
    std::istream &binaryRead(std::istream &stream, T &value);

private:
    std::unique_ptr<HeaderStock> mHeaderStock;
    std::vector<Vertex> mPointData;
};

template<typename T>
std::istream &LASReader::binaryRead(std::istream &stream, T &value)
{
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}


#endif // LASREADER_H
