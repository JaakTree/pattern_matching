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
    __private int piece_len = text_len / pieces_num;
    __private int start = piece_len*i;//max(piece_len*i - pattern_len + 1, 0);
    __private int index_in_piece = 0;
    __private int k = 0;
    /*
    for i in range(self.text_len):
            while k > 0 and pattern[k] != self.text[i]:
                k = pi[k-1]

            if pattern[k] == self.text[i]:
                k += 1

            if k == pat_len:
                index = i - pat_len + 1
                indexes.append(index)
                k = pi[k-1]
    */
    while ((start + index_in_piece < text_len) && (index_in_piece < piece_len + pattern_len - 1)){
        matches[start+index_in_piece] = 0;
        while ((k > 0) && (pattern[k] != text[start+index_in_piece])){
            k = pi[k-1];
        }

        if (pattern[k] == text[start+index_in_piece]) k++;

        if (k == pattern_len) {
            matches[start + index_in_piece - pattern_len + 1] = 1;
            k = pi[k-1];
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