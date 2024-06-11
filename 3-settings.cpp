
//////////
/////////////
//////////////// processing-related
/////////////
//////////

#define DATA_PER_PEICE (1024 * 64)
// in bytes
// the more you increase this, the faster the process gets and the more space that we save
// but the change of coming across a duplicate piece lowers, and the faster we are going to come across a collision

////
/////// test 2
////

// source file size: 2748217 (/dev/random)

// chunk: 65536 (1024 * 64)
// save time: 4.47 secs
// load time: 2.35 secs
// db size: 2839985
// ptr size: 721
// space loss: 0.0336541837853415 *100 %

////
/////// test 1
////

// test file size: 2.2G (/dev/urandom)

// chunk 262144 (1024 * 256)
// save time: 3.88 secs
// load time: 3.56 secs
// db size: 2.2G
// pointer size: 153K
// total space loss: 0.0000663237138228 *100 %

// chunk 131072 (1024 * 128)
// save time: 2.19 secs
// load time: 3.43 secs
// db size: 2,2G
// pointer size: 297K
// total space loss: 0.0001287460327148 *100 %

// chunk 65536 (1024 * 64)
// save time: 4.93 secs
// load time: 2.85 secs
// db size: 2,2G
// pointer size: 581K
// total space loss: 0.0002518567171963 *100 %

// chunk 8192 (1024 * 8)
// save time: 26.40 secs
// load time: 10.21 secs
// db size: 2,7G
// pointer size: 4,5M
// total space loss: 0.2292702414772727 *100 %

////
/////// test 0
////

// compressed file size: 82M (/dev/urandom)

// #define DATA_PER_PEICE 131072
// keys folder size 85M
// pointer file size 11K
// space loss: 0.0367163681402438 *100 %

// #define DATA_PER_PEICE 65536
// keys folder size 87M
// pointer file size 22K

// #define DATA_PER_PEICE 32768
// keys folder size 92M
// pointer file size 44K

// #define DATA_PER_PEICE 16384
// keys folder size 103M
// pointer file size 87K

// #define DATA_PER_PEICE 8192
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

//////////
/////////////
//////////////// path-related
/////////////
//////////

string HASH_ENTRY_FOLDER_ROOT = home_dir() + "/.cache/minq-caching-thing-2/" + to_string(DATA_PER_PEICE);

string HASH_ENTRY_NAME_DATA = "data";
