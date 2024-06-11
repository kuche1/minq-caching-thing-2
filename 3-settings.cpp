
//////////
/////////////
//////////////// settings
/////////////
//////////

/////// processing-related

// compressed file size: 82M (/dev/urandom)
// the more you reduce DATA_PER_PEICE, the more time it takes
// DATA_PER_PEICE is in bytes

// #define DATA_PER_PEICE 131072
// keys folder size 85M
// pointer file size 11K

// #define DATA_PER_PEICE 65536
// keys folder size 87M
// pointer file size 22K

// #define DATA_PER_PEICE 32768
// keys folder size 92M
// pointer file size 44K

// #define DATA_PER_PEICE 16384
// keys folder size 103M
// pointer file size 87K

#define DATA_PER_PEICE 8192
// keys folder size 123M
// pointer file size 174K

// #define DATA_PER_PEICE 4096
// keys folder size 165M
// pointer file size 347K

// #define DATA_PER_PEICE 2048
// keys folder size 329M
// pointer file size 693K

// #define DATA_PER_PEICE 1024
// keys folder size 658M
// pointer file size 1.4M

// #define DATA_PER_PEICE 512
// keys folder size 1.3G
// pointer file size 2.8M

// #define DATA_PER_PEICE 256
// keys folder size 2.7G
// pointer file size 5.5M

/////// path-related

string HASH_ENTRY_FOLDER_ROOT = home_dir() + "/.cache/minq-caching-thing-2/" + to_string(DATA_PER_PEICE);

string HASH_ENTRY_NAME_DATA = "data";
