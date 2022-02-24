#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace nk125 {
  class binary_file_handler {
    private:
      std::string notallowed = "*?<>|\n"; // Windows Default Disabled Chars

      long long m_chunk_pos = 0;

      std::string sanitize(std::string file_name) {
          int index = 0;
          std::string buffer = file_name;
          for (char c : buffer) {
              if (notallowed.find(c) != std::string::npos) {
                  buffer.erase(index, 1);
              }
              index++;
          }
          return buffer;
      }

      std::string read_error = "The file specified cannot be opened.";
      std::string write_error = read_error;
      long long m_size;
    // End Of Private

    public:
      void set_not_allowed_chars(std::string chars) {
          notallowed = chars;
      }

      std::string read_file(std::string file_path) {
        file_path = sanitize(file_path);
        std::ifstream in_file(file_path, std::ios::binary);
        std::string m_str_buff;
        char m_ch_buff;
        if (in_file.is_open()) {
          while (in_file >> std::noskipws >> m_ch_buff) {
            m_str_buff += m_ch_buff;
          }
          m_ch_buff = '\0';
          in_file.close();
          return m_str_buff;
        }
        else {
          throw std::runtime_error(read_error);
        }
      }

      std::string fast_read_file(std::string file_path) {
        // I recommend it when you have to quickly read mid-size files with 5+ MB (or super big files with GB's of size)
        // Instead you should use the safe method read_file
        // If you have a trick to copy char* to string without copying and having the same file allocated twice, please add a pull request
        file_path = sanitize(file_path);
        std::ifstream in_file(file_path, std::ios::binary);
        std::string m_str_buff;
        if (in_file.is_open()) {
          in_file.seekg(0, std::ios_base::end);
          long long sz = in_file.tellg();
          long long chpos = sz;
          std::vector<char> m_vch_buff;
          m_vch_buff.resize(sz);
          in_file.seekg(0, std::ios_base::beg);
          in_file.read(reinterpret_cast<char*>(m_vch_buff.data()), sz);
          in_file.close();
          m_str_buff.assign(m_vch_buff.begin(), m_vch_buff.end());
          return m_str_buff;
        }
        else {
          throw std::runtime_error(read_error);
        }
      }

      /*std::string chunk_read_file(std::string file_path, int chunk_size) {
        if (chunk_size < 1) {
          throw std::invalid_argument("The chunk size must be greater than 0.");
        }
        file_path = sanitize(file_path);
        std::ifstream in_file(file_path, std::ios::binary);
        if (in_file.is_open()) {
          long long pos, m_f_byte_sz = size_file(file_path);
          std::string m_buffer;
          while (m_chunk_pos != m_f_byte_sz) {
            char* m_ch_buff = new char[chunk_size];
            in_file.seekg(0, pos);
            m_chunk_pos = in_file.tellg() + chunk_size;
            in_file.read(m_ch_buff, chunk_size);
            in_file.close();
            m_buffer.assign(m_ch_buff, chunk_size);
            delete[] m_ch_buff;
            return m_buffer;
          }
        }
        else {
          throw std::runtime_error(read_error);
        }
      }*/

      long long size_file(std::string file_path) {
        file_path = sanitize(file_path);
        std::ifstream sz_file(file_path, std::ios::binary);
        if (sz_file.is_open()) {
          sz_file.seekg(0, std::ios_base::end);
          long long m_fsize = sz_file.tellg();
          sz_file.close();
          return m_fsize;
        }
        else {
          throw std::runtime_error(read_error);
        }
      }

      void write_file(std::string file_path, std::string content) {
        file_path = sanitize(file_path);
        std::ofstream out_file(file_path, std::ios::binary);
        if (out_file.is_open()) {
          out_file.write(content.c_str(), content.size());
          out_file.close();
          return;
        }
        else {
          throw std::runtime_error(write_error);
        }
        return;
      }

      void append_file(std::string file_path, std::string content) {
        file_path = sanitize(file_path);
        std::ofstream out_file(file_path, std::ios::binary | std::ios::app);
        if (out_file.is_open()) {
          out_file.write(content.c_str(), content.size());
          out_file.close();
          return;
        }
        else {
          throw std::runtime_error(write_error);
        }
        return;
      }

      void copy_file(std::string origin, std::string end) {
        std::string buffer = read_file(origin);
        write_file(end, buffer);
        return;
      }

      void fast_copy_file(std::string origin, std::string end) {
        std::string buffer = fast_read_file(origin);
        write_file(end, buffer);
        return;
      }
    // End of Public
  };
}
