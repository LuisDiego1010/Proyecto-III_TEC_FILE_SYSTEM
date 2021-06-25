//
// Created by isaac on 19/6/21.
//

#ifndef TEC_FILE_SYSTEM_DISKNODES_H
#define TEC_FILE_SYSTEM_DISKNODES_H

#include "Socket/Server.h"

int DiskSize{150};
int BlockSize{2048};

class DiskNodes {
public:
    Server Socket;
    std::string dir;
    int elements = 0;
    int parity = 0;

    /**
     * @brief Initialize the sockets, the string that indicate the dir and block counts.
     */
    void create();

    /**
     * @brief Write to a file the data and the metadata
     * Write the string to a n quantity of blocks. the data is a .txt and the metadata a .data.
     * @return errors code 0 is no erro and 1 is parity file. <0 error codes
     */
    int Write(std::string &, bool= true);


    /**
     *@brief Read the data in the disk
     * Read the metadata in the I-node, load, check parity and send all the data on the blocks of the file as a single string
     * @return Readed data or error code
     */
    std::string Read(std::string &);


    /**
     *@brief Start the working of the DISK to recieve data.
     */
    static void Start();

    /**
     *@brief Get the number of blocks.
     */
    void count_dir();

    /**
     *@brief Get the names od the saved files.
     * @return
     */
    std::string list_dir();

    /**
     *@brief aux function of the list_dir() function
     * @see list_dir
     * @return
     */
    static int filter(const struct dirent *);
};

#endif //TEC_FILE_SYSTEM_DISKNODES_H
