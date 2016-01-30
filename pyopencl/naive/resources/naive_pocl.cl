__kernel void naive_search(
    __global char* string,
    __global char* pattern,
    const int string_len,
    const int pattern_len,
    __global int* matches)
{
    int i = get_global_id(0);
    if (i+pattern_len <= string_len) {
        int j = 0;
        while(j < pattern_len) {
             if (string[i+j] != pattern[j])
                  break;
             j++;
        }

        matches[i] = (j == pattern_len) ? 1 : 0;
    } else if (((i+pattern_len > string_len) || (i >= string_len-pattern_len+1)) && (i < string_len)) {
        matches[i] = 0;
    }
}