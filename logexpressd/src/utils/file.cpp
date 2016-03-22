#include "file.h"

expr::File::File(std::string file_path, std::string mod):
    path(file_path),
    mode(mod)
{
    if(this->mode.compare("read") == 0)
    {
        this->input_stream.open(this->path.c_str(), std::ifstream::in);
    }
    else
    {
        this->output_stream.open(this->path.c_str(), std::ofstream::out | std::ofstream::app);
    }
}

expr::File::~File()
{
    if(this->input_stream.is_open())
    {
        this->input_stream.close();
    }

    if(this->output_stream.is_open())
    {
        this->output_stream.flush();
        this->output_stream.close();
    }
}

/**
 * @brief This returns true when the file is existed, returns false when the file is NOT existed
 */
bool expr::File::is_exist()
{
    bool is_file_exist = false;

    if(this->mode.compare("read") == 0)
    {
        if(this->input_stream.good())
        {
            is_file_exist = true;
        }
    }
    else
    {
        if(this->output_stream.good())
        {
            is_file_exist = true;
        }
    }

    return is_file_exist;
}

/**
 * @brief This reads file_path input argument of expr::File class, and then returns string in the file
 */
std::string expr::File::get_contents()
{
    std::string contents;

    if(this->input_stream.good())
    {
        std::string str_part;
        while(! this->input_stream.eof() )
        {
            this->input_stream >> str_part;
            contents = contents + str_part;
            str_part.clear();
        }
    }

    return contents;
}

void expr::File::write(std::string contents)
{    
    this->output_stream << contents << std::endl;
}

void expr::File::sync()
{
    if((this->mode.compare("write") == 0))
    {
        this->output_stream.flush();
    }
}

void expr::File::close()
{
    if((this->mode.compare("write") == 0))
    {
        this->output_stream.close();
    }
    else if(this->mode.compare("read") == 0)
    {
        this->input_stream.close();
    }
}

bool expr::File::is_open()
{
    if((this->mode.compare("write") == 0))
    {
        return this->output_stream.is_open();
    }
    else if(this->mode.compare("read") == 0)
    {
        return this->input_stream.is_open();
    }

    return false;
}

