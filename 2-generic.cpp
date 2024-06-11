
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
