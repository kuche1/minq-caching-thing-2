
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

    return fs::exists(root);
}

string hash_entry_data(uint8_t seed, const array<uint64_t, 2> & hash){
    string root = hash_entry_root(seed, hash);
    string path = root + '/' + HASH_ENTRY_NAME_DATA;
    return file_read(path);
}

bool hash_entry_content_differs(uint8_t seed, const array<uint64_t, 2> & hash, const string & data){

    string root = hash_entry_root(seed, hash);

    ASSERT(fs::exists(root));

    string path_data = root + '/' + HASH_ENTRY_NAME_DATA;

    return file_read(path_data) != data;
}

void hash_entry_create(uint8_t seed, const array<uint64_t, 2> & hash, const string & data){

    string root = hash_entry_root(seed, hash);

    ASSERT(!fs::exists(root));

    fs::create_directories(root);

    string path_data = root + '/' + HASH_ENTRY_NAME_DATA;

    ofstream file_data;
    file_data.open(path_data, ios::binary);
    ASSERT(file_data.is_open());

    file_data << data;
}
