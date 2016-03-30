__kernel void bmh_search(
    __global char* text,
    __global char* pattern,
    __global int* table,
    const int text_len,
    const int pattern_len,
    const int pieces_num,
    __global int* matches)
{
    int i = get_global_id(0);
    __private int piece_len = text_len / pieces_num;
    __private int skip = i*piece_len;
    if(skip < text_len){
        // start compare from right to left
        __private int right_end = min((i+1)*piece_len - 1, text_len - 1);
        __private bool matched;
        while ((skip <= right_end) && (skip < text_len - pattern_len + 1)){
            __private int k = pattern_len - 1;
            matched = false;
            while (text[skip + k] == pattern[k]){
                if (k == 0){
                    matches[skip] = 1;
                    matched = true;
                    break;
                }
                k--;
            }

            __private int shift = table[text[skip + pattern_len - 1] - 'A'];
            // put 0 where is no pattern
            if (k != 0 || !matched){
                __private int j = skip;
                while(j < skip+shift){
                    matches[j] = 0;
                    j++;
                }
            }

            skip = skip + shift;
        }
    }

    if (text_len-skip <= piece_len) {
        __private int index = text_len - pattern_len + 1;
        while (index < text_len) {
            matches[index] = 0;
            index++;
        }
    }
}
