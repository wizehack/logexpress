#include <fstream>
#include "file.h"

expr::File::File(std::string file_path):
    path(file_path){}

expr::File::~File(){}

/**
 * @brief This returns true when the file is existed, returns false when the file is NOT existed
 */
bool expr::File::is_exist()
{
    std::ifstream file_stream(this->path.c_str());
    bool is_file_exist = false;

    if(file_stream.good())
    {
        is_file_exist = true;
    }

    file_stream.close();

    return is_file_exist;
}

/**
 * @brief This reads file_path input argument of expr::File class, and then returns string in the file
 */
std::string expr::File::get_contents()
{
    std::string contents;

    std::ifstream file_stream(this->path.c_str());    

    if(file_stream.good())
    {
        std::string str_part;
        while(! file_stream.eof() )
        {
            file_stream >> str_part;
            contents = contents + str_part;
            str_part.clear();
        }
    }

    return contents;
}


