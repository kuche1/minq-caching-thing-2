
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
    // { // simpler but less effecient way of reading
    //     ifstream file;
    //     file.open(path, ios::binary);
    //     ASSERT(file.is_open());

    //     stringstream buffer;
    //     buffer << file.rdbuf();

    //     return buffer.str();
    // }

    ifstream file;
    file.open(path, ios::binary);
    ASSERT(file.is_open());

    file.seekg(0, ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, ios::beg);

    string file_content(file_size, '\0');

    file.read(&file_content[0], file_size);

    return file_content;
}

void file_write(const string & path, const string & data){
    ofstream file;
    file.open(path, ios::binary);
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

string dirname(string path){
    fs::path path_as_path(path);
    return path_as_path.parent_path().string();
}

ofstream file_open_write_mkdirs(string path){

    ofstream file;

    file.open(path, ios::binary);

    if(!file.is_open()){
        
        string parent_folder = dirname(path);

        error_code ec;
        if(!fs::create_directories(parent_folder, ec)){
            ERR("Could not open file for writing `" << path << "` and could not create parent directory `" << parent_folder << "`: " << ec.message());
        }

        file.open(path, ios::binary);

        if(!file.is_open()){
            ERR("Created parent directory `" << parent_folder << "` but could not open file for writing `" << path << "`");
        }
    }

    return file;
}