#ifndef JSON_LOG_FILE_H_
#define JSON_LOG_FILE_H_

#include <string>
#include <fstream>

namespace expr {
    class File {

        public:
            File(std::string file_path, std::string mode);
            ~File();
            bool is_exist();
            std::string get_contents();
            std::ofstream get_ofstream();
            void write(std::string contents);
            void sync();
            void close();
            bool is_open();

        private:
            File();

        private:
            std::string path;
            std::string mode;
            std::ifstream input_stream;
            std::ofstream output_stream;
    };
}

#endif /* JSON_LOG_FILE_H_ */
