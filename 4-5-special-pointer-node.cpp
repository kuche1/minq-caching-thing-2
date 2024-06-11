
void generate_pointer_from_node(const string & source, const string & destination){

    if(fs::is_directory(source)){
        generate_pointer_from_folder(source, destination);
    }else if(fs::is_regular_file(source)){
        generate_pointer_from_file(source, destination);
    }else{
        cerr << "`" << source << "` is neither a regular file nor a folder" << endl;
        exit(1);
    }

}

void generate_node_from_pointer(const string & source, const string & destination){

    if(fs::is_directory(source)){
        generate_folder_from_pointer(source, destination);
    }else if(fs::is_regular_file(source)){
        generate_file_from_pointer(source, destination);
    }else{
        cerr << "`" << source << "` is neither a regular file nor a folder" << endl;
        exit(1);
    }

}
