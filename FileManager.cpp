#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;


/* Class for working with binary files. */
template<class DataType> class FileManager
{
public:
    /* Finds offset to chunk specified by ID. */
    int FindOffset(const char* filename, int id, bool print_if_missing)
    {
        // open file handler
        ifstream reader(filename, ios::binary);
        if (!reader)
        {
            cout << "Couldn't open file '" << filename << "' for reading." << endl;
            return -1;
        }

        DataType holder;
        int offset = 0;
        bool found = false;
        // seek for wanted chunk
        do
        {
            reader.read(reinterpret_cast<char*>(&holder), sizeof(DataType));
            if (holder.ID == id)
            {
                found = true;
                break;
            }
            offset += sizeof(DataType);
        } while (!reader.eof());

        // print error message if requested
        if (found == false && print_if_missing)
        {
            cout << "No record of object ID=" << id;
            cout << " in file '" << filename << "'." << endl;
        }

        // close handler
        reader.close();

        // return offset if found, else -1
        return found ? offset : -1;
    }

    /* Appends data to end of file. */
    bool AppendToFile(const char* filename, DataType& data)
    {
        // verify that chunk isn't present in file
        int offset = FindOffset(filename, data.ID, false);
        if (offset != -1)
        {
            cout << "A record of object ID=" << data.ID << " already exists";
            cout << " in file '" << filename << "'." << endl;
            return false;
        }

        // open file handler
        ofstream writer(filename, ios::binary | ios::app);
        if (!writer)
        {
            cout << "Couldn't open file '" << filename << "' for writing." << endl;
            return false;
        }
        else
        {
            // append chunk
            writer.write(reinterpret_cast<char*>(&data), sizeof(DataType));

            // close handler
            writer.close();
        }

        return true;
    }

    /* Inserts data to chunk specified by ID. */
    bool InsertToFile(const char* filename, DataType& data, int id)
    {
        // seek chunk designated for overwrite
        int offset = FindOffset(filename, id, true);
        if (offset == -1)
            return false;

        // open file handler
        fstream writer(filename, ios::binary | ios::in | ios::out);
        if (!writer)
        {
            cout << "Couldn't open file '" << filename << "' for writing." << endl;
            return false;
        }
        else
        {
            // overwrite chunk
            writer.seekp(offset);
            writer.write(reinterpret_cast<char*>(&data), sizeof(DataType));

            // close handler
            writer.close();
        }

        return true;
    }

    /* Deletes chunk specified by ID from file. */
    bool DeleteFromFile(const char* filename, int id)
    {
        // seek chunk designated for removal
        int offset = FindOffset(filename, id, true);
        if (offset == -1)
            return false;

        // create temp file
        char temp_file[256] = {};
        strcat_s(temp_file, filename);
        strcat_s(temp_file, ".temp.bin");

        // open file handlers
        ifstream reader(filename, ios::binary);
        if (!reader)
        {
            cout << "Couldn't open file '" << filename << "' for reading." << endl;
            return false;
        }
        ofstream writer(temp_file, ios::binary);
        if (!writer)
        {
            cout << "Couldn't open file '" << temp_file << "' for writing." << endl;
            return false;
        }

        char buffer;
        // copy wanted contents
        for (int i = 0; i < offset; i++)
        {
            reader.read(&buffer, sizeof(char));
            writer.write(&buffer, sizeof(char));
        }

        // skip unwanted
        reader.ignore(sizeof(DataType));

        // copy rest of wanted contents
        while (!reader.eof())
        {
            reader.read(&buffer, sizeof(char));

            // check for avoiding extra byte written at end
            if (!reader.eof())
            {
                writer.write(&buffer, sizeof(char));
                offset += sizeof(DataType);
            }
        }

        // close handlers
        reader.close();
        writer.close();

        // try removing the original file and replace with temp
        if (std::remove(filename))
        {
            cout << "Couldn't rewrite file '" << filename << "'." << endl;
            std::remove(temp_file);
            return false;
        }
        else std::rename(temp_file, filename);

        return true;
    }


};

