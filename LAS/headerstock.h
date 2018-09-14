#ifndef HEADERSTOCK_H
#define HEADERSTOCK_H

struct HeaderStock
{
    char File_Signature[4];
    unsigned short File_Source_ID;
    unsigned short Global_Encoding;
    unsigned long Project_ID_GUID_data1;
    unsigned short Project_ID_GUID_data2;
    unsigned short Project_ID_GUID_data3;
    unsigned char Project_ID_GUID_data4[8];
    unsigned char Version_Major;
    unsigned char Version_Minor;
    char System_Identifier[32];
    char Generating_Software[32];
    unsigned short File_Creation_Day_of_Year;
    unsigned short File_Creation_Year;
    unsigned short Header_Size;
    unsigned long Offset_to_point_data;
    unsigned long Number_of_Variable_Length_Records;
    unsigned char Point_Data_Format_ID;
    unsigned short Point_Data_Record_Length;
    unsigned long Number_of_point_records;
    unsigned long Number_of_points_by_return[5];
    double X_scale_factor;
    double Y_scale_factor;
    double Z_scale_factor;
    double X_offset;
    double Y_offset;
    double Z_offset;
    double Max_X;
    double Min_X;
    double Max_Y;
    double Min_Y;
    double Max_Z;
    double Min_Z;
};

#endif // HEADERSTOCK_H
