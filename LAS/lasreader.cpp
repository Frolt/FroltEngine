#include "lasreader.h"
#include "paths.h"
#include "a_math.h"
#include "vertex.h"
#include <iostream>
#include <fstream>
#include <QDebug>

LASReader::LASReader(const std::string &path)
{
    mHeaderStock = std::make_unique<HeaderStock>();
    std::ifstream inf(Path::mapdata + path, std::ios::binary);
    readHeaderStock(inf);
    readPointData(inf);
}

void LASReader::readHeaderStock(std::istream &stream)
{
    binaryRead(stream, mHeaderStock->File_Signature);
    binaryRead(stream, mHeaderStock->File_Source_ID);
    binaryRead(stream, mHeaderStock->Global_Encoding);
    binaryRead(stream, mHeaderStock->Project_ID_GUID_data1);
    binaryRead(stream, mHeaderStock->Project_ID_GUID_data2);
    binaryRead(stream, mHeaderStock->Project_ID_GUID_data3);
    binaryRead(stream, mHeaderStock->Project_ID_GUID_data4);
    binaryRead(stream, mHeaderStock->Version_Major);
    binaryRead(stream, mHeaderStock->Version_Minor);
    binaryRead(stream, mHeaderStock->System_Identifier);
    binaryRead(stream, mHeaderStock->Generating_Software);
    binaryRead(stream, mHeaderStock->File_Creation_Day_of_Year);
    binaryRead(stream, mHeaderStock->File_Creation_Year);
    binaryRead(stream, mHeaderStock->Header_Size);
    binaryRead(stream, mHeaderStock->Offset_to_point_data);
    binaryRead(stream, mHeaderStock->Number_of_Variable_Length_Records);
    binaryRead(stream, mHeaderStock->Point_Data_Format_ID);
    binaryRead(stream, mHeaderStock->Point_Data_Record_Length);
    binaryRead(stream, mHeaderStock->Number_of_point_records);
    binaryRead(stream, mHeaderStock->Number_of_points_by_return);
    binaryRead(stream, mHeaderStock->X_scale_factor);
    binaryRead(stream, mHeaderStock->Y_scale_factor);
    binaryRead(stream, mHeaderStock->Z_scale_factor);
    binaryRead(stream, mHeaderStock->X_offset);
    binaryRead(stream, mHeaderStock->Y_offset);
    binaryRead(stream, mHeaderStock->Z_offset);
    binaryRead(stream, mHeaderStock->Max_X);
    binaryRead(stream, mHeaderStock->Min_X);
    binaryRead(stream, mHeaderStock->Max_Y);
    binaryRead(stream, mHeaderStock->Min_Y);
    binaryRead(stream, mHeaderStock->Max_Z);
    binaryRead(stream, mHeaderStock->Min_Z);
}

void LASReader::readPointData(std::istream &stream)
{
    long x, y, z;
    float decimals = 100.0f;
    am::Vec3 pos;
    mPointData.reserve(mHeaderStock->Number_of_point_records);

    // Reads all points
    for (unsigned int i = 0; i < mHeaderStock->Number_of_point_records; ++i)
    {
        stream.seekg(mHeaderStock->Offset_to_point_data + mHeaderStock->Point_Data_Record_Length * i);
        binaryRead(stream, x);
        binaryRead(stream, y);
        binaryRead(stream, z);
        pos.x = (static_cast<float>(x) / decimals) - (static_cast<float>(mHeaderStock->Min_X));
        pos.z = (static_cast<float>(y) / decimals) - (static_cast<float>(mHeaderStock->Min_Y));
        pos.y = (static_cast<float>(z) / decimals) - (static_cast<float>(mHeaderStock->Min_Z));
        mPointData.emplace_back(pos);
    }
}

std::vector<Vertex> &LASReader::getPointData()
{
    return  mPointData;
}

const HeaderStock &LASReader::getHeaderStock()
{
    return *mHeaderStock;
}
