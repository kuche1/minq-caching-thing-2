
//////////
/////////////
//////////////// specialised, level3
/////////////
//////////

////// file

void generate_pointer_from_file(const string & path_source, const string & path_result){

    ifstream file_in;
    file_in.open(path_source, ios::binary);
    if(!file_in.is_open()){
        ERR("Could not open file for reading: " << path_source);
    }

    ofstream file_out = file_open_write_mkdirs(path_result);

    while(true){

        string buffer(DATA_PER_PEICE, '\0');
        file_in.read(&buffer[0], DATA_PER_PEICE);

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
    file_in.open(path_pointer, ios::binary);
    if(!file_in.is_open()){
        ERR("Could not open pointer file for reading: " << path_pointer);
    }

    ofstream file_out = file_open_write_mkdirs(path_result);

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

////// folder

void generate_pointer_from_folder(const string & source, const string & destination){

    fs::create_directories(destination);

    for(const auto & entry : fs::directory_iterator(source)){ // recursive_directory_iterator

        string entry_name = [&entry]{
            fs::path path = entry;
            fs::path base_name = path.filename();
            return base_name.string();
        }();

        string src = source + '/' + entry_name;
        string dst = destination + '/' + entry_name;

        if(entry.is_directory()){
            generate_pointer_from_folder(src, dst);
        }else if(entry.is_regular_file()){
            generate_pointer_from_file(src, dst);
        }else{
            UNREACHABLE();
        }

    }

}

void generate_folder_from_pointer(const string & source, const string & destination){

    fs::create_directories(destination);

    for(const auto & entry : fs::directory_iterator(source)){ // recursive_directory_iterator

        string entry_name = [&entry]{
            fs::path path = entry;
            fs::path base_name = path.filename();
            return base_name.string();
        }();

        string src = source + '/' + entry_name;
        string dst = destination + '/' + entry_name;

        if(entry.is_directory()){
            generate_folder_from_pointer(src, dst);
        }else if(entry.is_regular_file()){
            generate_file_from_pointer(src, dst);
        }else{
            UNREACHABLE();
        }

    }

}
