
//////////
/////////////
//////////////// specialised, level0
/////////////
//////////

static_assert(HASH == (string)"MurmurHash3_x64_128");

array<uint64_t, 2> calc_hash(uint8_t seed, const string & data){
    uint32_t seed_actual = seed; // save some bytes
    int len = static_cast<int>(data.size());
    return MurmurHash3_x64_128(data.c_str(), len, seed_actual);
}
