
pair<uint8_t, array<uint64_t, 2>> piece_save(const string & data){

    uint8_t seed = 0;

    while(true){

        array<uint64_t, 2> hash = calc_hash(seed, data);

        if(hash_entry_exists(seed, hash)){
            if(hash_entry_content_differs(seed, hash, data)){
                seed += 1;
                ASSERT(seed > 0); // too many collisions, the easiest and probably the best fix would be: increase `seed` from uint8_t to uint16_t
                continue;
            }else{
                return {seed, hash};
            }
        }

        hash_entry_create(seed, hash, data);

        return {seed, hash};
    }
}

string piece_load(uint8_t seed, const array<uint64_t, 2> & hash){

    return hash_entry_data(seed, hash);

}
