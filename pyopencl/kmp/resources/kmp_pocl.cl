__kernel void kmp_search(
    __global char* text,
    __global char* pattern,
    __global int* pi,
    const int text_len,
    const int pattern_len,
    const int pieces_num,
    __global int* matches)
{
    int i = get_global_id(0);
    int start = pieces_num * i;
    int index_in_piece = 0;
    int piece_len = text_len / pieces_num;
    int k = 0;
    while ((start+index_in_piece < text_len) && (index_in_piece < piece_len)){
        while ((k > 0) && (pattern[k] != text[start+index_in_piece])){
            k = pi[k-1];
        }

        if (pattern[k] == text[start+index_in_piece]) {
            k++;
        }

        if (k == pattern_len) {
            matches[start + index_in_piece - pattern_len + 1] = 1;
            k = pi[k-1];
        } else {
            matches[start + index_in_piece - pattern_len + 1] = 0;
        }

        index_in_piece++;
    }

    if (text_len-start <= piece_len) {
        int index = text_len - pattern_len + 1;
        while (index < text_len) {

            matches[index] = 0;
            index++;
        }
    }
}