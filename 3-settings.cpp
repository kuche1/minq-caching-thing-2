
//////////
/////////////
//////////////// settings
/////////////
//////////

/////// processing-related

// compressed file size: 82M (/dev/urandom)
// the more you reduce the chunk size, the more time it takes
// each "key" will be of size CHUNK bytes
// TODO just CHUNK is a really bad name

// #define CHUNK 131072
// keys folder size 85M
// pointer file size 11K

// #define CHUNK 65536
// keys folder size 87M
// pointer file size 22K

// #define CHUNK 32768
// keys folder size 92M
// pointer file size 44K

// #define CHUNK 16384
// keys folder size 103M
// pointer file size 87K

#define CHUNK 8192
// keys folder size 123M
// pointer file size 174K

// #define CHUNK 4096
// keys folder size 165M
// pointer file size 347K

// #define CHUNK 2048
// keys folder size 329M
// pointer file size 693K

// #define CHUNK 1024
// keys folder size 658M
// pointer file size 1.4M

// #define CHUNK 512
// keys folder size 1.3G
// pointer file size 2.8M

// #define CHUNK 256
// keys folder size 2.7G
// pointer file size 5.5M

/////// path-related

string HASH_ENTRY_FOLDER_ROOT = home_dir() + "/.cache/minq-caching-thing-2/" + to_string(CHUNK);
// TODO `/var/tmp` is inappropriate

string HASH_ENTRY_NAME_DATA = "data";
