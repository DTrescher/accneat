#include <iostream>
#include "accneat.h"
#include "main.h"
#include <fstream> // std::ifstream
#include <vector>

using namespace NEAT;
using namespace std;

//helper
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::vector<NEAT::Test> GetDataFromCSV(std::string filename) {
        std::vector<Step> result;
        std::ifstream csv(filename);
        
        if(!csv.is_open()) throw runtime_error("Could not open file");
        
        string line, val;
        while(getline(csv, line))
        {
                vector<string> data = split(line, ":");
            
                vector<string> in_s = split(data.at(0), ",");
                vector<real_t> in;
                std::transform( in_s.begin(), in_s.end(), in.begin(), stof);
            
                vector<string> out_s = split(data.at(1), ",");
                vector<real_t> out;
                std::transform( out_s.begin(), out_s.end(), out.begin(), stof);
            
                Step step(in, out, 1.0f); //extract weight if needed
                result.push_back(step); 
        }
        
        csv.close();

        return {result};
}

int main(int argc, char *argv[]) {
        
    if(!accneat(10, 5000, GeneticSearchType::COMPLEXIFY, "xor", DEFAULT_RNG_SEED, DEFAULT_MAX_GENS, true)) {
        cerr << "Something went wrong..." << endl;
    }

    return(0);
}
