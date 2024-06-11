
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

    }else if(flag_action == "info"){

        cout << "THIS IS A DEBUG FLAG, DO NOT USE IT" << endl;
        cout << "DATA_PER_PEICE: " << DATA_PER_PEICE << endl;
        exit(1);

    }else{
        cout << "Invalid flag `" << flag_action << "`; must be either `" << FLAG_ACTION_SAVE << "` or `" << FLAG_ACTION_LOAD << "`" << endl;
        exit(1);
    }

    return 0;
}
