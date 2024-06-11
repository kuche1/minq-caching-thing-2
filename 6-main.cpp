
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

    // action

    void (*action_fnc)(const string &, const string &) = [&argc, &argv]{

        if(argc <= 0){
            cerr << "Insufficient command line arguments: you must specify `" << FLAG_ACTION_SAVE << "` or `" << FLAG_ACTION_LOAD << "`" << endl;
            exit(1);
        }

        string flag_action = argv[0];
        argc -= 1;
        argv += 1;

        if(flag_action == FLAG_ACTION_SAVE){

            return generate_pointer_from_node;

        }else if(flag_action == FLAG_ACTION_LOAD){

            return generate_node_from_pointer;

        }else if(flag_action == "info"){

            cerr << "THIS IS A DEBUG FLAG, DO NOT USE IT" << endl;
            cerr << "DATA_PER_PEICE: " << DATA_PER_PEICE << endl;
            exit(1);

        }else{

            cerr << "Invalid flag `" << flag_action << "`; must be either `" << FLAG_ACTION_SAVE << "` or `" << FLAG_ACTION_LOAD << "`" << endl;
            exit(1);

        }

    }();

    // source

    if(argc <= 0){
        cerr << "You need to specify the source file/folder" << endl;
        exit(1);
    }

    string source = argv[0];
    argc -= 1;
    argv += 1;

    // destination

    if(argc <= 0){
        cerr << "You need to specify the destination file/folder" << endl;
        exit(1);
    }

    string destination = argv[0];
    argc -= 1;
    argv += 1;

    // any additional args

    if(argc > 0){
        cerr << "Too many arguments supplied: " << argc << " more than what was expected" << endl;
        exit(1);
    }

    // execute

    action_fnc(source, destination);

    return 0;
}
