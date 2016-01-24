#ifndef JSON_LOG_FILE_H_
#define JSON_LOG_FILE_H_

#include <string>

namespace expr {
    class File {

        public:
            File(std::string file_path);
            ~File();
            bool is_exist();
            std::string get_contents();

        private:
            File();

        private:
            std::string path;
    };
}

#endif /* JSON_LOG_FILE_H_ */
