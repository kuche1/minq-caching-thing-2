
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
