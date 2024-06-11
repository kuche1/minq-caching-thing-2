
//////////
/////////////
//////////////// tests
/////////////
//////////

// void test_basic_calc_hash(){

//     string key = "asd fgh";

//     uint8_t seed = 0;

//     array<uint64_t, 2> hash = calc_hash(seed, key);

//     ASSERT("00be89ecd5294e465b45858ea932d7b38e" == hash_entry_name(seed, hash));
// }

// void test_basic_save(){

//     string data = "asd fgh\nsdf ghj";

//     piece_save(data);

//     ASSERT(file_read("/var/tmp/minq-caching-thing-2/00628d68bbb1343678392c9da7f326a658/data") == data);
//     // this path should not be hardcoded
// }

// void test_save_load(){
//     string data = "asd fgh\nsdf ghj";

//     auto [seed, hash] = piece_save(data);

//     ASSERT(piece_load(seed, hash) == data);
// }

// void test_save_load_using_pointers(){
    
//     string file_source = "/tmp/test123";
//     string file_ptr = file_source + "-p";
//     string file_deref = file_ptr + "-d";
//     string contents = "adfc4wagvtsdyebzy5e\ntesay5eztfetg5esyg\nsefy5sru64s7y54se";

//     file_write(file_source, contents);
    
//     generate_pointer_from_file(file_source, file_ptr);
    
//     generate_file_from_pointer(file_ptr, file_deref);
    
//     ASSERT(file_read(file_source) == contents);
//     ASSERT(contents == file_read(file_deref));
// }

// void test_all(){
//     cout << "running tests..." << endl;
//     test_basic_calc_hash();
//     test_basic_save();
//     test_save_load();
//     test_save_load_using_pointers();
//     cout << "all tests completed!" << endl;
// }
