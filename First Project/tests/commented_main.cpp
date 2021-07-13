#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "buffer.h"

int main(int argc, char *argv[]){
    std::ifstream infile(argv[1]);
    if(!infile){
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 0;
    }
    unsigned int num_serv;
    infile >> num_serv;

    Buffer<std::string> *servers = new Buffer<std::string>[num_serv];
    Buffer<std::string> hist;

    std::string txt;
    std::string delim = " ", token;
    unsigned int tgt_serv;
    unsigned int pos = 0;
    std::cout << "NUMBER OF SERVERS:" << num_serv << std::endl;
    while(std::getline(infile,txt)){
        if(txt.size() == 0){
            continue;
        }
        // Get command
        pos = txt.find(delim);
        token = txt.substr(0,pos);
        txt.erase(0,pos + delim.length());
        std::cout << "COMMAND:" << token << std::endl;
        // Handle command
        if(token == "INFO"){
            // Gets parameters for specific command
            pos = txt.find(delim);
            token = txt.substr(0,pos);
            txt.erase(0,pos + delim.length());
            tgt_serv = atoi(token.c_str());
            // Checks validity
            if((tgt_serv >= num_serv) || (tgt_serv < 0)){
                continue;
            }
            // Executes command
            servers[tgt_serv].push_back(txt);
            std::cout << "INSERT " << txt << " IN SERVER: " << tgt_serv << std::endl; 
            std::cout << "SERVER: " << tgt_serv << " -> ";
            servers[tgt_serv].print_commented();
        }
        if(token == "WARN"){
            // Gets parameters for specific command
            size_t serv_pos;
            pos = txt.find(delim);
            token = txt.substr(0,pos);
            txt.erase(0,pos + delim.length());
            tgt_serv = atoi(token.c_str());
            serv_pos = atoi(txt.c_str());
            // Checks validity
            if((tgt_serv >= num_serv) || (tgt_serv < 0)){
                continue;
            }
            else if((serv_pos >= servers[tgt_serv].get_size()) || (serv_pos < 0)){
                continue;
            }
            // Executes command
            servers[tgt_serv].print_commented();
            Item<std::string> curr_item = servers[tgt_serv].pop_pos(serv_pos);
            std::cout << "WARN" << curr_item.content << " FROM SERVER: " << serv_pos << std::endl;
            std::cout << "SERVER: " << tgt_serv << " -> ";
            servers[tgt_serv].push_front(curr_item);
            servers[tgt_serv].print_commented();
        }
        if(token == "TRAN"){
            // Gets parameters for specific command
            size_t dest_serv;
            pos = txt.find(delim);
            token = txt.substr(0,pos);
            txt.erase(0,pos + delim.length());
            tgt_serv = atoi(token.c_str());
            dest_serv = atoi(txt.c_str());
            // Checks validity
            if((tgt_serv >= num_serv) || (tgt_serv < 0) || (dest_serv >= num_serv) || (dest_serv < 0)){
                continue;
            }
            // Executes command
            std::cout << "ORIGINAL SERVER " << tgt_serv << ": ";
            servers[tgt_serv].print_commented();
            std::cout << "ORIGINAL SERVER " << dest_serv << ": ";
            servers[dest_serv].print_commented();
            while(!servers[tgt_serv].is_empty()){
                Item<std::string> curr_item = servers[tgt_serv].pop_front();
                servers[dest_serv].push_back(curr_item);
            }
            servers[tgt_serv].clear();
            std::cout << "SERVER: " << dest_serv << " -> ";
            servers[dest_serv].print_commented();
        }
        if(token == "ERRO"){
            // Gets parameters for specific command
            tgt_serv = atoi(txt.c_str());
           // Checks validity
            if((tgt_serv >= num_serv) || (tgt_serv < 0)){
                continue;
            }
            // Executes command
            std::cout << token << " " << txt << std::endl;
            std::cout << "PRINTING ALL CONTENT FROM SERVER: " << tgt_serv << std::endl;
            servers[tgt_serv].print();
            servers[tgt_serv].clear();
        }
        if(token == "SEND"){
            // Executes command
            Item<std::string> curr_item;
            for(int i = 0; i < num_serv; i++){
                try{
                    curr_item = servers[i].pop_front();
                }
                catch(Buffer<std::string>::EmptyBufferError e){
                    std::cout << e.message << std::endl;
                    continue;
                }
                hist.push_back(curr_item);
            }
        }
        if(token == "FLUSH"){
            // Executes command
            hist.print();
            for(int i = 0; i < num_serv; i++){
                servers[i].print();
            }
        }
        std::cout << "HIST:"<< std::endl;
        hist.print_commented();
        std::cout << "SERVERS:"<< std::endl;
        for(int i = 0; i < num_serv; i++){
            servers[i].print_commented();
        }
        std::cout << std::endl;
    }
    infile.close();
    delete[] servers;
}