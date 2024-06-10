
// TODO
//
// make it also work with directories

// TOD0
//
// make it not architecture specific (because of the endianness)
// search for TOD0-endianness

// BAD IDEAS
//
// perhaps we could re-calculate the hashes at runtime
// would take too much time

//////////
/////////////
//////////////// include, namespace
/////////////
//////////

// include: c
#include <dirent.h>

// include: c++
#include <iostream>
#include <array>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <filesystem>

// include: local
#include "mmh3/MurmurHash3.hpp"

// namespace
using namespace std;
namespace fs = std::filesystem;

//////////
/////////////
//////////////// generic
/////////////
//////////

#define ERR(...) { \
    cerr << "ERROR: "; \
    cerr << "file `" << __FILE__ << "` "; \
    cerr << "line " << __LINE__ << ": "; \
    cerr << __VA_ARGS__; \
    cerr << endl; \
    exit(1); \
}

#define UNREACHABLE() { \
    ERR("Unreachable code reached") \
}

#define ASSERT(condition) { \
    if(!(condition)){ \
        ERR("Assertion failed"); \
    } \
}

// TODO think if it makes sense for this to be `is_folder`, or `exists`
bool is_folder(const string & path){
    // https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c

    DIR * dir = opendir(path.c_str());

    if(dir){
        closedir(dir);
        return true;
    }

    if(ENOENT == errno){
        // directory doesn't exist
        return false;
    }

    // something else went wrong
    UNREACHABLE();
}

string file_read(const string & path){
    ifstream file;
    file.open(path);
    ASSERT(file.is_open());

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void file_write(const string & path, const string & data){
    ofstream file;
    file.open(path);
    ASSERT(file.is_open());

    file << data;
}

string home_dir(){

    char * home_dir = getenv("HOME");

    if(home_dir == nullptr){
        ERR("Could not determine home directory");
    }

    return home_dir;

    //// this doesnt work with `-static`
    // struct passwd * pw = getpwuid(getuid());
    // if (pw == nullptr) {
    //     throw runtime_error("Unable to determine home directory.");
    // }
    // return string(pw->pw_dir);
}

//////////
/////////////
//////////////// settings
/////////////
//////////

/////// processing-related

// compressed file size: 82M (/dev/urandom)
// the more you reduce the chunk size, the more time it takes
// each "key" will be of size CHUNK bytes
// TODO just CHUNK is a really bad name

// #define CHUNK 131072
// keys folder size 85M
// pointer file size 11K

// #define CHUNK 65536
// keys folder size 87M
// pointer file size 22K

// #define CHUNK 32768
// keys folder size 92M
// pointer file size 44K

// #define CHUNK 16384
// keys folder size 103M
// pointer file size 87K

#define CHUNK 8192
// keys folder size 123M
// pointer file size 174K

// #define CHUNK 4096
// keys folder size 165M
// pointer file size 347K

// #define CHUNK 2048
// keys folder size 329M
// pointer file size 693K

// #define CHUNK 1024
// keys folder size 658M
// pointer file size 1.4M

// #define CHUNK 512
// keys folder size 1.3G
// pointer file size 2.8M

// #define CHUNK 256
// keys folder size 2.7G
// pointer file size 5.5M

/////// path-related

string HASH_ENTRY_FOLDER_ROOT = home_dir() + "/.cache/minq-caching-thing-2/" + to_string(CHUNK);
// TODO `/var/tmp` is inappropriate

string HASH_ENTRY_NAME_DATA = "data";

//////////
/////////////
//////////////// specialised, level0
/////////////
//////////

array<uint64_t, 2> calc_hash(uint8_t seed, const string & data){
    uint32_t seed_actual = seed; // save some bytes
    return MurmurHash3_x64_128(data.c_str(), data.size(), seed_actual);
}

//////////
/////////////
//////////////// specialised, level1
/////////////
//////////

string hash_entry_name(uint8_t seed, const array<uint64_t, 2> & hash){
    ostringstream name;

    name << hex; // use hex format
    name << setfill('0'); // fill with 0s

    name << setw(sizeof(seed) * 2);
    name << static_cast<uint16_t>(seed); // this is fucking bullshit

    name << setw(sizeof(hash[0]) * 2);
    name << hash[0];

    name << setw(sizeof(hash[1]) * 2);
    name << hash[1];

    return name.str();
}

string hash_entry_root(uint8_t seed, const array<uint64_t, 2> & hash){

    ostringstream path;

    path << HASH_ENTRY_FOLDER_ROOT << '/' << hash_entry_name(seed, hash);

    return path.str();

}

bool hash_entry_exists(uint8_t seed, const array<uint64_t, 2> & hash){

    string root = hash_entry_root(seed, hash);

    // TODO add an assert that makes sure that a file with the
    // same name doesn't exist

    return is_folder(root);
}

string hash_entry_data(uint8_t seed, const array<uint64_t, 2> & hash){
    string root = hash_entry_root(seed, hash);
    string path = root + '/' + HASH_ENTRY_NAME_DATA;
    return file_read(path);
}

bool hash_entry_content_differs(uint8_t seed, const array<uint64_t, 2> & hash, const string & data){

    string root = hash_entry_root(seed, hash);

    ASSERT(is_folder(root));

    string path_data = root + '/' + HASH_ENTRY_NAME_DATA;

    return file_read(path_data) != data;
}

void hash_entry_create(uint8_t seed, const array<uint64_t, 2> & hash, const string & data){

    string root = hash_entry_root(seed, hash);

    ASSERT(!is_folder(root)); // TODO would be better if this is `exists` instead

    fs::create_directories(root);

    string path_data = root + '/' + HASH_ENTRY_NAME_DATA;

    ofstream file_data;
    file_data.open(path_data);
    ASSERT(file_data.is_open());

    file_data << data;
}

//////////
/////////////
//////////////// specialised, level2
/////////////
//////////

pair<uint8_t, array<uint64_t, 2>> piece_save(const string & data){

    uint8_t seed = 0;

    while(true){

        array<uint64_t, 2> hash = calc_hash(seed, data);

        if(hash_entry_exists(seed, hash)){
            if(hash_entry_content_differs(seed, hash, data)){
                seed += 1;
                ASSERT(seed > 0); // too many collisions, the easiest and probably the best fix would be: increase `seed` from uint8_t to uint16_t
                continue;
            }else{
                return {seed, hash};
            }
        }

        hash_entry_create(seed, hash, data);

        return {seed, hash};
    }
}

string piece_load(uint8_t seed, const array<uint64_t, 2> & hash){

    return hash_entry_data(seed, hash);

}

//////////
/////////////
//////////////// specialised, level3
/////////////
//////////

void generate_pointer_from_file(const string & path_source, const string & path_result){

    ifstream file_in;
    file_in.open(path_source);
    if(!file_in.is_open()){
        ERR("Could not open file for reading: " << path_source);
    }

    ofstream file_out;
    file_out.open(path_result);
    ASSERT(file_out.is_open());

    while(true){

        string buffer(CHUNK, '\0');
        file_in.read(&buffer[0], CHUNK);

        streamsize bytes_read = file_in.gcount();
        if(bytes_read <= 0){
            break;
        }

        buffer.resize(bytes_read);

        auto [seed, hash] = piece_save(buffer);
        string name = hash_entry_name(seed, hash);

        // TOD0-endianness
        file_out.write(reinterpret_cast<char*>(&seed), sizeof(seed));
        file_out.write(reinterpret_cast<char*>(&hash[0]), sizeof(hash[0]));
        file_out.write(reinterpret_cast<char*>(&hash[1]), sizeof(hash[1]));

    }

}

void generate_file_from_pointer(const string & path_pointer, const string & path_result){

    ifstream file_in;
    file_in.open(path_pointer);
    if(!file_in.is_open()){
        ERR("Could not open pointer file for reading: " << path_pointer);
    }

    ofstream file_out;
    file_out.open(path_result);
    ASSERT(file_out.is_open());

    while(true){

        uint8_t seed;
        array<uint64_t, 2> hash;

        // TOD0-endianness
        file_in.read(reinterpret_cast<char*>(&seed), sizeof(seed));
        file_in.read(reinterpret_cast<char*>(&hash[0]), sizeof(hash[0]));
        file_in.read(reinterpret_cast<char*>(&hash[1]), sizeof(hash[1]));

        // TODO we need to check ^^^ if the vars really were read, or if it's empty

        streamsize bytes_read = file_in.gcount();
        if(bytes_read <= 0){
            return;
        }

        string piece = piece_load(seed, hash);

        file_out << piece;

    }

}

//////////
/////////////
//////////////// tests
/////////////
//////////

void test_basic_calc_hash(){

    string key = "asd fgh";

    uint8_t seed = 0;

    array<uint64_t, 2> hash = calc_hash(seed, key);

    ASSERT("00be89ecd5294e465b45858ea932d7b38e" == hash_entry_name(seed, hash));
}

void test_basic_save(){

    string data = "asd fgh\nsdf ghj";

    piece_save(data);

    ASSERT(file_read("/var/tmp/minq-caching-thing-2/00628d68bbb1343678392c9da7f326a658/data") == data);
    // this path should not be hardcoded
}

void test_save_load(){
    string data = "asd fgh\nsdf ghj";

    auto [seed, hash] = piece_save(data);

    ASSERT(piece_load(seed, hash) == data);
}

void test_save_load_using_pointers(){
    
    string file_source = "/tmp/test123";
    string file_ptr = file_source + "-p";
    string file_deref = file_ptr + "-d";
    string contents = "adfc4wagvtsdyebzy5e\ntesay5eztfetg5esyg\nsefy5sru64s7y54se";

    file_write(file_source, contents);
    
    generate_pointer_from_file(file_source, file_ptr);
    
    generate_file_from_pointer(file_ptr, file_deref);
    
    ASSERT(file_read(file_source) == contents);
    ASSERT(contents == file_read(file_deref));
}

void test_all(){
    cout << "running tests..." << endl;
    test_basic_calc_hash();
    test_basic_save();
    test_save_load();
    test_save_load_using_pointers();
    cout << "all tests completed!" << endl;
}

//////////
/////////////
//////////////// main
/////////////
//////////

#define FLAG_ACTION_SAVE "save"
#define FLAG_ACTION_LOAD "load"

int main(int argc, char * * argv){

    argc -= 1;
    argv += 1;

    if(argc <= 0){
        cout << "Insufficient command line arguments: you must specify `" << FLAG_ACTION_SAVE << "` or `" << FLAG_ACTION_LOAD << "`" << endl;
        exit(1);
    }

    string flag_action = argv[0];
    argc -= 1;
    argv += 1;

    bool file0_fail = true;
    string file0;

    if(argc > 0){
        file0_fail = false;
        file0 = argv[0];
        argc -= 1;
        argv += 1;
    }

    bool file1_fail = true;
    string file1;

    if(argc > 0){
        file1_fail = false;
        file1 = argv[0];
        argc -= 1;
        argv += 1;
    }

    if(argc > 0){
        cout << "Too many arguments supplied" << endl;
        exit(1);
    }

    if(flag_action == FLAG_ACTION_SAVE){
        
        if(file0_fail){
            cout << "You need to specify the file that you want to save" << endl;
            exit(1);
        }

        if(file1_fail){
            cout << "You need to specify the new pointer file" << endl;
            exit(1);
        }

        generate_pointer_from_file(file0, file1);

    }else if(flag_action == FLAG_ACTION_LOAD){
        
        if(file0_fail){
            cout << "You need to specify the file that will be used to reconstruct the original data" << endl;
            exit(1);
        }

        if(file1_fail){
            cout << "You need to specify where the reconstructed data is going to be put" << endl;
            exit(1);
        }

        generate_file_from_pointer(file0, file1);

    }else{
        cout << "Invalid flag `" << flag_action << "`; must be either `" << FLAG_ACTION_SAVE << "` or `" << FLAG_ACTION_LOAD << "`" << endl;
        exit(1);
    }

    return 0;
}