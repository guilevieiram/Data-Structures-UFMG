#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "buffer.h"

template <>
void Buffer<std::string>::print_content(){
    if(this->is_empty()){
        return;
    }
    BufferCell<std::string>* temp = this->front->next;
    std::string aux;
    while(temp != nullptr){
        aux = temp->item.content;
        std::cout << aux.substr(1,aux.size()-2) << std::endl;
        temp = temp->next;
    }
}

int main(int argc, char *argv[]){
    std::ifstream infile(argv[1]);
    if(!infile){
        std::cerr << "Error: Unable to open file!" << std::endl;
        return 0;
    }
    int num_serv;
    infile >> num_serv;

    Buffer<std::string> *servers = new Buffer<std::string>[num_serv];
    Buffer<std::string> hist;

    std::string txt;
    std::string delim = " ", token;
    size_t pos = 0 , tgt_serv;

    while(std::getline(infile,txt)){
        if(txt.size() == 0){
            continue;
        }
        // Get command
        pos = txt.find(delim);
        token = txt.substr(0,pos);
        txt.erase(0,pos + delim.length());
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
            Item<std::string> curr_item = servers[tgt_serv].pop_pos(serv_pos);
            servers[tgt_serv].push_front(curr_item);
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
            while(!servers[tgt_serv].is_empty()){
                Item<std::string> curr_item = servers[tgt_serv].pop_front();
                servers[dest_serv].push_back(curr_item);
            }
            servers[tgt_serv].clear();
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
            servers[tgt_serv].print_content();
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
                    continue;
                }
                hist.push_back(curr_item);
            }
        }
        if(token == "FLUSH"){
            // Executes command
            hist.print_content();
            for(int i = 0; i < num_serv; i++){
                servers[i].print_content();
            }
        }
    }
    infile.close();

}